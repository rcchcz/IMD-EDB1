#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <exception>    // std::out_of_range
#include <iostream>     // std::cout, std::endl
#include <memory>       // std::unique_ptr
#include <iterator>     // std::advance, std::begin(), std::end(), std::ostream_iterator
#include <algorithm>    // std::copy, std::equal, std::fill
#include <initializer_list> // std::initializer_list
#include <cassert>      // assert()
#include <limits>       // std::numeric_limits<T>
#include <cstddef>      // std::size_t

/// Sequence container namespace.
namespace sc {
    /// Implements tha infrastrcture to support a bidirectional iterator.
    template < class T >
    class MyForwardIterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
        public:
            typedef MyForwardIterator self_type;   //!< Alias to iterator.
            // Below we have the iterator_traits common interface
            typedef std::ptrdiff_t difference_type; //!< Difference type used to calculated distance between iterators.
            typedef T value_type;           //!< Value type the iterator points to.
            typedef T* pointer;             //!< Pointer to the value type.
            typedef T& reference;           //!< Reference to the value type.
            typedef const T& const_reference;           //!< Reference to the value type.
            typedef std::bidirectional_iterator_tag iterator_category; //!< Iterator category.

            /**
             * @brief Construct a new My Iterator object
             * 
             * @param ptr Pointer
             */
            MyForwardIterator(pointer ptr =nullptr): m_ptr(ptr){ };

            /**
             * @brief  Copy constructor.
             * @param other MyForwardIterator to be copied.
             */
            MyForwardIterator( const MyForwardIterator& other )
            : m_ptr{ other.m_ptr }
            { }

            /**
             * @brief Destroy the My Forward Iterator object
             * 
             */
            ~MyForwardIterator( ) = default;
   
            /**
             * @brief A copy assignment operator
             * 
             * @return MyForwardIterator& Parameter to copy
             */
            MyForwardIterator& operator=( const MyForwardIterator& ) = default;

            /**
             * @brief Overload pre-increment operator.
             * @return MyForwardIterator.
             */
            MyForwardIterator& operator++() { 
                m_ptr++;
                return *this;
            }
            
            /**
             * @brief Overload post-increment operator.
             * @return MyForwardIterator.
             */
            MyForwardIterator operator++(int) {
                // Save original.
                MyForwardIterator aux = *this;
                // Increment.
                m_ptr++;
                return aux;
            }
            /**
             * @brief Overload pre-decrement operator.
             * 
             * @return MyForwardIterator. 
             */
            MyForwardIterator& operator--() { 
                m_ptr--;
                return *this;
            }
            /**
             * @brief Overload post-decrement operator.
             * 
             * @return MyForwardIterator. 
             */
            MyForwardIterator operator--(int) {
                // Save original.
                MyForwardIterator aux = *this;
                // Increment.
                m_ptr--;
                return aux;
            }

            /**
             * @brief Overload post-increment operator.
             * Handle the case n + it.
             * @param n Increments to be made in the iterator.
             * @param it Iterator to be incremented.
             * @return MyForwardIterator.
             */
            friend MyForwardIterator operator+(difference_type n, MyForwardIterator it) {
                MyForwardIterator aux;
                aux.m_ptr = it.m_ptr + n;
                return aux;
            }

            /**
             * @brief Overload post-increment operator.
             * Handle the case it + n.
             * @param n Increments to be made in the iterator.
             * @param it Iterator to be incremented.
             * @return MyForwardIterator.
             */
            friend MyForwardIterator  operator+(MyForwardIterator it, difference_type n) {
                MyForwardIterator aux;
                aux.m_ptr = it.m_ptr + n;
                return aux;
            }

        
            /**
             * @brief Overload post-decrement operator.
             * Handle the case it - n.
             * @param n Increments to be made in the iterator.
             * @param it Iterator to be incremented.
             * @return MyForwardIterator.
             */
            friend MyForwardIterator operator-(MyForwardIterator it, difference_type n) {
                MyForwardIterator aux;
                aux.m_ptr = it.m_ptr - n;
                return aux;
            }
            
            /**
             * @brief Calculate difference between two iterators.
             * @param Other Second iterator to calculate the difference.
             * @return difference_type equal to the difference between iterators.
             */
            difference_type operator-(MyForwardIterator other) { return m_ptr - other.m_ptr; }
            
            /**
             * @brief Return a reference to the object located at the position pointedby the iterator
             * 
             * @return reference to m_ptr
             */
            reference operator*()const{ return *m_ptr; }

            /**
             * @brief Check if two iterators are equal.
             * Overload '==' operator.
             * @param other Iterator to be compared.
             * @return true if the two iterators are equal; false otherwise.
             */
            bool operator==( const MyForwardIterator& other ) const  { return m_ptr == other.m_ptr; }

            /**
             * @brief Check if two iterators are different.
             * Overload '!=' operator.
             * @param other Iterator to be compared.
             * @return true if the two iterators are different; false otherwise.
             */
            bool operator!=( const MyForwardIterator& other) const { return !(*this == other ); }


        private:
            pointer m_ptr; //!< The raw pointer.
    };

    /// This class implements the ADT list with dynamic array.
    /*!
     * sc::vector is a sequence container that encapsulates dynamic size arrays.
     *
     * The elements are stored contiguously, which means that elements can
     * be accessed not only through iterators, but also using offsets to
     * regular pointers to elements.
     * This means that a pointer to an element of a vector may be passed to
     * any function that expects a pointer to an element of an array.
     *
     * \tparam T The type of the elements.
     */
    template < typename T >
    class vector
    {
        //=== Aliases
        public:
            using size_type = unsigned long; //!< The size type.
            using value_type = T;            //!< The value type.
            using pointer = value_type*;     //!< Pointer to a value stored in the container.
            using reference = value_type&;   //!< Reference to a value stored in the container.
            using const_reference = const value_type&; //!< Const reference to a value stored in the container.

            using iterator = MyForwardIterator< value_type >; //!< The iterator, instantiated from a template class.
            using const_iterator = MyForwardIterator< const value_type >; //!< The const_iterator, instantiated from a template class.

        public:
            //=== [I] SPECIAL MEMBERS (6 OF THEM)

            /**
             * @brief Constructs the vector with count default-inserted instances of T.
             * @param new_cap A size_type indicating vector capacity; 0 by default. 
             */
            explicit vector( size_type new_cap = 0 ) 
            : m_end{ 0 },
              m_capacity{ new_cap },
              m_storage{ new T[ m_capacity ] }
            {
                std::fill( m_storage, m_storage + m_capacity, T{} );
            };


            /**
             * @brief  Copy constructor.
             * Constructs the list with the deep copy of the contents of other.
             * @param other List from where the content will be copied.
             */
            vector( const vector& other )
            : m_end{ other.m_end },
              m_capacity{ other.m_capacity },
              m_storage{ new T[ m_capacity ] }
            {
                // Copy all elements from other into the vector storage area.
                std::copy( other.cbegin(), other.cend(), this->begin() );
            };


            /**
             * @brief Constructor from an initializer list.
             * @param il An initializer list.
             */
            vector( std::initializer_list<T> il ) 
            :  m_end { il.size() }, 
               m_capacity{ il.size() },
               m_storage{ new T[ m_capacity ] }
            {
                // Copy all elements from the initializer list into the vector storage area.
                std::copy( il.begin(), il.end(), m_storage );

            };
            

            /**
             * @brief Destroy the vector object
             * 
             */
            virtual ~vector( ) { delete [] m_storage; };

            
            /**
             * @brief  Constructs the list with the contents of the range [first, last)
             * 
             * @tparam first and last, respectively
             */
            template < typename InputItr >
            vector( InputItr first, InputItr last)
              : m_end{(size_type)(last-first)}, 
                m_capacity{(size_type)(last-first)},
                m_storage{ new T [ m_capacity ]}
            { 
                std::copy( first, last,m_storage);
            };


            /**
             @brief Copy assignment operator. Replaces the contents with a copy of the contents of other
             * 
             * @param other Vector that will be copied
             * @return Implicit pointer along with the names of the functions,
             * see more about 'this' : https://en.cppreference.com/w/cpp/language/this
             */
            vector & operator=( const vector & other ){
                if (this != &other){
                    if (m_capacity < other.m_end ){ //Is necessary do realloc memory ?
                        reserve(other.m_end);
                    }
                    std::copy( other.m_storage, other.m_storage + other.m_end,  m_storage );
                }
               m_end = other.m_end;
               return *this;
            }


            //=== [II] ITERATORS

            /**
             * @brief Return an iterator pointing to the first item in the vector.
             * @return An iterator pointing to the first item in the vector.
             */
            iterator begin( void ) { return iterator( &m_storage[0] ); }


            /**
             * @brief Returns an iterator pointing to the end mark in the vector
             * @return Iterator pointing to the end mark in the vector
             */
            iterator end( void ) { return iterator(&m_storage[m_capacity]); }


            /**
             * @brief Returns a constant iterator pointing to the first item in the vector.
             * @return A constant iterator pointing to the first item in the vector.
             */
            const_iterator cbegin( void ) const { return const_iterator( &m_storage[0] ); }
            /**
             * @brief Returns a constant iterator pointing to the end markin the vector
             * @return Iterator pointing to the end markin the vector
             */
            const_iterator cend( void ) const { return const_iterator( &m_storage[m_capacity]); }

            // [III] Capacity
            /**
             * @brief Return vector logic size
             * @return logic size
             */
            size_type size( void ) const { return m_end; }

            /**
             * @brief Return vector capacity.
             * @return size_type Vector capacity.
             */
            size_type capacity( void ) const { return m_capacity; }

            /**
             * @brief Check if the vector is empty.
             * @return True if the vector contains no elements; false otherwise.
             */
            bool empty( void ) const { return m_end == 0; }

            // [IV] Modifiers
            /**
             * @brief 
             * 
             */
            void clear( void ){ m_end = 0; }

            void push_front( const_reference );

            /**
             * @brief Insert element to the end of the vector.
             * @param value Element to be inserted.
             */
            void push_back( const_reference value ) {
                // Check if it is full; relocation needed.
                if( full() ) 
                    reserve(2 * (m_end + 1));
                    
                // Insertation.
                m_storage[ m_end++ ] = value;
            }
            /**
             * @brief Remove logically the last element.
             * 
             */
            void pop_back( void ) {
                if (empty())
                    throw std::length_error ("[vector::pop_back()]: Not possible remove element from empty vector.");
                m_end--; //Logical removal
            }

            void pop_front( void );

            /**
             * @brief Insert value into the vector before the position given by the iterator pos_.
             * @param pos_ Iterator before which value will be inserted.
             * @param value Element to be inserted into the vector.
             * @return Iterator to the position of the inserted item.
             * @throws std::length_error if vector is empty and the insertion is not in the first position; or insertion is not continuous.
             */
            iterator insert( iterator pos_ , const_reference value_ ) {     
                /*           
                // Empty vector.
                if ( empty() && pos_ != begin() + 1)
                    throw std::length_error ("[vector::insert()]: empty vector; only insertion in the first position allowed.");

                // Empty space between m_end and pos; out of range.
                if( pos_ - begin() > m_end + 1)
                    throw std::length_error ("[vector::insert()]: out of range; insertion must be sequential, no empty spaces are allowed between m_end and pos_.");
                */
                // Empty vector but insertion is in first position.
                if ( empty() && pos_ == begin() + 1) {
                    m_storage[ m_end++ ] = value_;
                    return m_storage;
                }
                
                // Not enough space; reallocation needed.
                if( full() ) 
                    reserve( 2 * (m_capacity + 1) );
                
                // Insertation.
                ++m_end;
                //for(size_t i = 0; m_end - 1 - i > index; i++ ) m_storage[m_end - 1 - i] = m_storage[m_end - i - 2]; 
                for(int i = m_end - 1; i >= pos_- begin() - 1; i-- )
                    m_storage[i + 1] = m_storage[i];
                *(pos_ -1) = value_;
                return (pos_-1);
            }

            /**
             * @brief Insert value into the vector before the position given by the iterator pos_.
             * @param pos_ Constante reference before which value will be inserted.
             * @param value Constante reference to the element to be inserted into the vector.
             * @return Iterator to the position of the inserted item.
             * @throws std::length_error if vector is empty and the insertion is not in the first position; or insertion is not continuous.
             */
            iterator insert( const_iterator pos_ , const_reference value_ ) {
                // Empty vector.
                //if ( empty() && pos_ != begin() + 1)
                   //throw std::length_error ("[vector::insert()]: empty vector; only insertion in the first position allowed.");

                // Empty vector but insertion is in first position.
                if ( empty() && pos_ == begin() + 1) {
                    m_storage[ m_end++ ] = value_;
                    return m_storage[0];
                }

                // Empty space between m_end and pos; out of range.
                //if( pos_ - begin() > end()- begin() + 1)
                    //throw std::length_error ("[vector::insert()]: out of range; insertion must be sequential, no empty spaces are allowed between m_end and pos_.");
                
                size_type index = pos_ - begin() - 1;

                // Not enough space; reallocation needed.
                if( full() ) 
                    reserve( 2 * (m_capacity + 1) );

                // Insertation.                    
                ++m_end;
                //for(size_t i = 0; m_end - 1 - i > index; i++ ) m_storage[m_end - 1 - i] = m_storage[m_end - i - 2]; 
                for(int i = m_end - 1; i >= pos_- begin() - 1; i-- )
                    m_storage[i + 1] = m_storage[i];
                m_storage[index] = value_;
                return m_storage[index];
            }
            
            /**
             * @brief  Insert elements from the range [first_; last_) before pos_.
             * @param pos_ Iterator before which value will be inserted.
             * @param firsr_ Iterator to the beginning of the range.
             * @param last_ Iterator to one position past the last element of the range.
             * @return Iterator to the position of the inserted item.
             * @throws std::length_error if vector is empty and the insertion is not in the first position.
             */
            template < typename InputItr >
            iterator insert( iterator pos_ , InputItr first_, InputItr last_ ) {
                // Empty vector.
                //if ( empty() && pos_ != begin() + 1)
                    //throw std::length_error ("[vector::insert()]: empty vector; only insertion in the first position allowed.");

                // Empty space between m_end and pos; out of range.
                //if( pos_ - begin()> end()- begin() + 1)
                    //throw std::length_error ("[vector::insert()]: out of range; insertion must be sequential, no empty spaces are allowed between m_end and pos_.");
                
                size_type size = last_ - first_ + 1;

                // Empty vector but insertion is in first position.
                if ( empty() && pos_ == begin() + 1) {
                    // Increase capacity.
                    if( size < m_capacity ) m_capacity += size;
                    m_end = size - 1;
                    std::copy( first_, last_, begin());

                    return m_storage;
                }

                int index = first_ - begin();
                
                // Not enough space; reallocation needed.
                if(m_end + size > m_capacity)
                    reserve( 2 * (m_end + size) );
                
                // Insertation.
                m_end += size;    
                //for(int i = 0; m_end - 1 - i > m_end - range_size ; i++ ) m_storage[m_end - 1 - i] = m_storage[m_end - 1 - i - range_size]; 
                for(int i = m_end-1; i >= pos_- begin()-1; i-- )
                    m_storage[i + size] = m_storage[i];
                std::copy( first_, last_, pos_ - 1);
                return m_storage +index;

            }

            /**
             * @brief Insert elements from the range [first_; last_) before pos_.
             * @param pos_ Constante reference before which value will be inserted.
             * @param firsr_ Iterator to the beginning of the range.
             * @param last_ Iterator to one position past the last element of the range.
             * @return Iterator to the position of the inserted item.
             * @throws std::length_error if vector is empty and the insertion is not in the first position.
             */
            template < typename InputItr >
            iterator insert( const_iterator pos_ , InputItr first_, InputItr last_ ) {
                // Empty vector.
                if ( empty() && pos_ != begin() + 1)
                    throw std::length_error ("[vector::insert()]: empty vector; only insertion in the first position allowed.");

                // Empty space between m_end and pos; out of range.
                if( pos_ - begin()> end()- begin() + 1)
                    throw std::length_error ("[vector::insert()]: out of range; insertion must be sequential, no empty spaces are allowed between m_end and pos_.");
                
                size_type size = last_ - first_ + 1;

                // Empty vector but insertion is in first position.
                if( empty() && pos_ == begin() + 1) {
                    // Increase capacity.
                    if( size < m_capacity ) m_capacity += size;
                    m_end = size - 1;
                    std::copy( first_, last_, begin());

                    return m_storage[0];
                }

                int index = first_ - begin();
                
                // Not enough space; reallocation needed.
                if(m_end + size > m_capacity)
                    reserve( 2 * (m_end + size) );
                
                // Insertation.
                m_end += size;
                //for(int i = 0; m_end - 1 - i > m_end - range_size ; i++ ) m_storage[m_end - 1 - i] = m_storage[m_end - 1 - i - range_size]; 
                for(int i = m_end-1; i >=pos_- begin()-1; i-- )
                    m_storage[i + size] = m_storage[i];
                std::copy( first_, last_, pos_ - 1 );
                return m_storage[index];
            }

            /**
             * @brief Inserts elements from the initializer list @param ilist before @param pos_
             * @param pos_ Position after that last element inserted
             * @param ilist_ List that will be inserted
             * @return iterator The position of first inserted element
             */
            iterator insert( iterator pos_, const std::initializer_list< value_type >& ilist_ ){
                //if (empty() && pos_ != begin() + 1)
                    //throw std::length_error ("[vector::insert()]: empty vector.");
                //else if( pos_ - begin()> end()- begin() + 1)
                    //throw std::length_error ("[vector::insert()]: empty space between m_end and pos_; filling must be continuous.");
                /*else*/ if (ilist_.size() + size() > m_capacity){
                    reserve(2*(ilist_.size() + size()));
                }
                //Move the elements, starting at pos_, ilist.size() foward positions
                for(int i = m_end-1; i >=pos_- begin()-1; i-- )
                    m_storage[i+ilist_.size()] = m_storage[i]; 
                //Insert the new elements
                for(int b=0; b < ilist_.size();b++)
                    std::copy(ilist_.begin(), ilist_.end(), pos_+b);
                //Update the logical size    
                m_end += ilist_.size();

                return pos_ - ilist_.size();
            }

            /**
             * @brief Inserts elements from the initializer list @param ilist before @param pos_
             * @param pos_ Position after that last element inserted
             * @param ilist_ List that will be inserted
             * @return iterator The position of first inserted element
             */
            iterator insert( const_iterator pos_, const std::initializer_list< value_type >& ilist_ ){
                /*
                if (empty() && pos_ != begin() + 1)
                    //throw std::length_error ("[vector::insert()]: empty vector.");
                //else if(pos_ - begin()> end()- begin() + 1)
                    //throw std::length_error ("[vector::insert()]: empty space between m_end and pos_; filling must be continuous.");
                
                else*/ if (ilist_.size() + size() > m_capacity){
                    reserve(2*(ilist_.size() + size()));
                }
                //Move the elements, starting at pos_, ilist.size() foward positions
                for(int i = m_end-1; i >=pos_- begin()-1; i-- )
                    m_storage[i+ilist_.size()] = m_storage[i]; 
                //Insert the new elements
                for(int b=0; b < ilist_.size();b++)
                    std::copy(ilist_.begin(), ilist_.end(), pos_+b);
                //Update the logical size    
                m_end += ilist_.size();

                return pos_- ilist_.size();
            }
            /**
             * @brief Increase the storage capacity of the array if the input
             * value is bigger thant actual capacity.
             * 
             * @param new_cap New capacity.
             */
            void reserve( size_type new_cap ){
                if(m_capacity < new_cap){ 
                    T* newArr = new T[new_cap]; 
                    //Copy the old array to the new one.
                    std::copy(m_storage, m_storage + m_end, newArr); 
                    delete[] m_storage;
                    m_storage = newArr;
                    m_capacity = new_cap;
                }
                return;
            }

            /**
             * @brief Removal of unused capacity.
             * Removal of unused capacity by reducing m_capacity to m_end.
             */
            void shrink_to_fit( void ) { m_capacity = m_end; }
            /**
             * @brief Assing with value.
             * The new contents are @param parameter-count_ elements, each initialized to a copy of @param parameter-value_.
             * 
             * @param count_  New vector size
             * @param value_  Filled value
             */
            void assign( size_type count_, const_reference value_ ){
                reserve(count_);
                m_end = count_;
                std::fill (begin(),end(),value_);
            }
            /**
             * @brief Replaces  the  contents  of the list with the elements from the initializer list ilist
             * 
             * @param ilist
             */
            void assign( const std::initializer_list<T>& ilist ){
                reserve(ilist.size());
                m_end = ilist.size();
                std::copy (begin(),end(),ilist.begin());
            }
            /**
             * @brief  Replaces the contents of the list withcopies of the elements in the range [first; last)
             * 
             * @param first 
             * @param last 
             */
            template < typename InputItr >
            void assign( InputItr first, InputItr last ){
                reserve(last-first);
                m_end = last-first;
                std::copy(begin(),end(),first);
            }

            /**
             * @brief Removes the range [first, last) from the vector.
             * @param first Iterator to the first element to be removed.
             * @param last Iterator to one position past the last element of the range.
             * @return Iterator to the element that follows the range before the call.
             * @throws std::length_error if vector is empty.
             */
            iterator erase( iterator first, iterator last ) {
                // Empty vector.
                if ( empty() )
                    throw std::length_error ("[vector::erase()]: empty vector.");

                size_t range_size = last - first - 1;
                size_t index = first - begin();
                
                for( size_t i = 0; i + index < m_end - range_size; i++ )
                    m_storage[index + i] = m_storage[index + i + range_size];  

                m_end -= range_size;

                return &m_storage[index];
            }

            /**
             * @brief Removes the range [first, last) from the vector.
             * @param first Constant reference to the first element to be removed.
             * @param last Constant reference to one position past the last element of the range.
             * @return Iterator to the element that follows the range before the call.
             * @throws std::length_error if vector is empty.
             */
            iterator erase( const_iterator first, const_iterator last ) {
                // Empty vector.
                if ( empty() )
                    throw std::length_error ("[vector::erase()]: empty vector.");

                size_t range_size = last - first - 1;
                size_t index = first - begin();
                
                for( size_t i = 0; i + index < m_end - range_size; i++ )
                    m_storage[index + i] = m_storage[index + i + range_size];  

                m_end -= range_size;

                return m_storage[index];
            }

            /**
             * @brief Removes the element at position pos.
             * @param pos Constant reference to the element to be removed.
             * @return Iterator to the element that follows pos before the call.
             * @throws std::length_error if vector is empty.
             */
            iterator erase( const_iterator pos ) {
                // Empty vector.
                if ( empty() )
                    throw std::length_error ("[vector::erase()]: empty vector.");

                size_t index = pos - begin();
                for (size_t i = 0; i + index < size - 1; i++ ) m_storage[index + i] = m_storage[index + i + 1]; 

                --m_end;

                return m_storage[index]; 
            }

            /**
             * @brief Removes the element at position pos.
             * @param pos Iterator to the element to be removed.
             * @return Iterator to the element that follows pos before the call.
             * @throws std::length_error if vector is empty.
             */
            iterator erase( iterator pos ) {
                // Empty vector.
                if ( empty() )
                    throw std::length_error ("[vector::erase()]: empty vector.");

                size_t index = pos - begin();
                for (size_t i = 0; i + index < m_end - 1; i++ ) m_storage[index + i] = m_storage[index + i + 1]; 

                --m_end;

                return &m_storage[index]; 
            }

            // [V] Element access

            /**
             * @brief Return the element at the end of the vector.
             * @return Constant reference to the element at the end of the vector.
             * @throws std::length_error if empty().
             */
            const_reference back( void ) const {
                // Check if the vector is empty.
                if ( empty() )
                    throw std::length_error ("[vector::back()]: empty vector.");
                
                return m_storage[m_end - 1];
            }

            /**
             * @brief Returns the object at the beginning of the list
             * 
             * @return const_reference object at the beginning of the list.
             */
            const_reference front( void ) const  { return m_storage[0]; };
            /**
             * @brief Returns the object at the beginning of the list
             * 
             * @return reference object at the beginning of the list.
             */
            reference front( void ){ return m_storage[0] ;};

            /**
             * @brief Return the element at the end of the vector.
             * @return Reference to the element at the end of the vector.
             * @throws std::length_error if empty().
             */
            reference back( void ) {
                // Check if the vector is empty.
                if ( empty() )
                    throw std::length_error ("[vector::back()]: empty vector.");
                
                return m_storage[m_end - 1];
            }


            /**
             * @brief Returns the object at the index pos in the array,with no bounds-checking.
             * 
             * @param pos Readed position
             * @return Value in pos
             */
            const_reference operator[]( size_type pos ) const { return m_storage[ pos ]; }

            /**
             * @brief Returns the object at the indexposin the array, withbounds-checking.
             * 
             * @param pos Readed position
             * @return Value in pos
             */
            reference operator[]( size_type pos ) { 
                if ( pos >= m_capacity)
                    throw std::out_of_range("[array::operator[]()]: Attempt to read out of vector range");
                return m_storage[ pos ];
            }

            /**
             * @brief Return the element at a specific position within the vector.
             * @return Constant reference the element at a specific position within the vector.
             * @throws std::length_error if empty(); std::out_of_range if pos >= m_capacity.
             */
            const_reference at( size_type pos ) const {
                // Check if the position passed is within the range of the vector.
                if ( pos >= m_capacity )
                    throw std::out_of_range("[vector::at()]: attempt to access position outside vector.");

                return m_storage[pos];
            }

            
            /**
             * @brief Return the element address at a specific position within the array.
             * @return Reference to the element at a specific position within the vector.
             */
            reference at( size_type pos ) {
                // Check if the position passed is within the range of the vector.
                if ( pos >= m_capacity )
                    throw std::out_of_range("[vector::at()]: attempt to access position outside vector.");

                return m_storage[pos];
            }


            pointer data( void );
            const_reference data( void ) const;

            // [VII] Friend functions.
            friend std::ostream & operator<<( std::ostream & os_, const vector<T> & v_ )
            {
                // O que eu quero imprimir???
                os_ << "{ ";
                for( auto i{0u} ; i < v_.m_capacity ; ++i )
                {
                    if ( i == v_.m_end ) os_ << "| ";
                    os_ << v_.m_storage[ i ] << " ";
                }
                os_ << "}, m_end=" << v_.m_end << ", m_capacity=" << v_.m_capacity;

                return os_;
            }
            friend void swap( vector<T> & first_, vector<T> & second_ )
            {
                // enable ADL
                using std::swap;

                // Swap each member of the class.
                swap( first_.m_end,      second_.m_end      );
                swap( first_.m_capacity, second_.m_capacity );
                swap( first_.m_storage,  second_.m_storage  );
            }

        private:
            bool full( void ) const{ return m_end == m_capacity; };
            size_type m_end;                //!< The list's current size (or index past-last valid element).
            size_type m_capacity;           //!< The list's storage capacity.
            // std::unique_ptr<T[]> m_storage; //!< The list's data storage area.
            T *m_storage;                   //!< The list's data storage area.
    };

    // [VI] Operators
    /**
     * @brief  Checks  if the contents of two vectorsare equal.
     * 
     * @param lhs vector
     * @param rhs ohter vector
     * @return true they are equal
     * @return false they are not equal
     */
    template <typename T>
    bool operator==( const vector<T> & lhs, const vector<T>& rhs){
        if(lhs.size() != rhs.size()) return false;
        for(auto a= 0;a <lhs.size();a++ ){
            if(lhs[a] != rhs[a]) return false;
        }
        return true;
    }

    /**
     * @brief  Checks  if the contents of two vectorsare equal.
     * @param lhs Vector.
     * @param rhs Ohter vector.
     * @return True if the two vectors are different; false otherwise.
     */
    template <typename T>
    bool operator!=( const vector<T> & lhs, const vector<T>& rhs) { return !( lhs == rhs ); }
    
} // namespace sc.
#endif
