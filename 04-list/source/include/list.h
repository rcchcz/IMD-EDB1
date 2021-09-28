#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>  // cout, endl
using std::cout;
using std::endl;

#include <iterator>  // bidirectional_iterator_tag
#include <cassert>   // assert()
#include <algorithm> // copy
using std::copy;
#include <cstddef>   // std::M
#include <type_traits>

namespace sc { // linear sequence. Better name: sequence container (same as STL).
    /*!
     * A class representing a biderectional iterator defined over a linked list.
     *
     * \note
     * This iterator only works for traversing elements inside the same list.
     *
     * This class is incomplete and it is provided "as is".
     *
     * \date May, 2nd 2017.
     * \author Selan R. dos Santos
     */

    template < typename T >
    class list
    {
        private:
        //=== the data node.
        struct Node
        {
            T data; // Tipo de informação a ser armazenada no container.
            Node * next;
            Node * prev;

            Node( const T &d=T{} , Node * n=nullptr, Node * p=nullptr )
                : data {d}, next{n}, prev{p}
            { /* empty */ }
        };


        //=== The iterator classes.
        public:

        class const_iterator : public std::bidirectional_iterator_tag 
        {
            //=== Some aliases to help writing a clearer code.
            public:
                using value_type        = T;         //!< The type of the value stored in the list.
                using pointer           = T *;       //!< Pointer to the value.
                using reference         = T &;       //!< reference to the value.
                using const_reference   = const T &; //!< const reference to the value.
                using difference_type   = std::ptrdiff_t;
                using iterator_category = std::bidirectional_iterator_tag;

            private:
                Node * m_ptr; //!< The raw pointer.

            public:
                const_iterator( Node * ptr = nullptr ): m_ptr{ptr}{ };
                ~const_iterator() = default;
                const_iterator( const const_iterator & ) = default;
                const_iterator& operator=( const const_iterator & ) = default;
                reference  operator*() { return m_ptr->data; }
                const_reference  operator*() const { return m_ptr->data; }
                const_iterator operator++() { m_ptr = m_ptr->next; return const_iterator{m_ptr->prev};  }
                const_iterator operator++(int)  { m_ptr = m_ptr->next; return const_iterator{m_ptr->prev};  }
                const_iterator operator--() { m_ptr = m_ptr->prev; return const_iterator{m_ptr}; }
                const_iterator operator--(int) { m_ptr = m_ptr->prev; return const_iterator{m_ptr->next};  }
                bool operator==( const const_iterator & rhs ) const { return m_ptr == rhs.m_ptr; }
                bool operator!=( const const_iterator & rhs ) const { return !(m_ptr == rhs.m_ptr); }

                //=== Other methods that you might want to implement.
                /// it += 3; // Go forth 3 positions within the container. 
                const_iterator operator+=( difference_type step) { 
                    for(difference_type i = 0; i < step; i++)
                        this++;
                    return const_iterator{m_ptr}; 
                }
                /// it -= 3; // Go back 3 positions within the container. 
                const_iterator operator-=(  difference_type step ) { 
                    for(difference_type i = 0; i < step; i++)
                        this--;
                    return const_iterator{m_ptr};                 
                }
                /// it->method()
                pointer operator->( void ) const { return this; }
                /// it1 - it2
                difference_type operator-( const const_iterator & rhs ) const { return std::distance(m_ptr, rhs.mm_ptr); }

                // We need friendship so the list<T> class may access the m_ptr field.
                friend class list<T>;

                friend std::ostream & operator<< ( std::ostream & os_, const const_iterator & s_ )
                {
                    os_ << "[@"<< s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
                    return os_;
                }
        };


        class iterator : public std::bidirectional_iterator_tag 
        {
            //=== Some aliases to help writing a clearer code.
            public:
                using value_type        = T; //!< The type of the value stored in the list.
                using pointer           = T *; //!< Pointer to the value.
                using reference         = T &; //!< reference to the value.
                using const_reference   = const T &; //!< const reference to the value.
                using difference_type   = std::ptrdiff_t;
                using iterator_category = std::bidirectional_iterator_tag;

            private:
                Node * m_ptr; //!< The raw pointer.

            public:
                iterator( Node * ptr = nullptr ): m_ptr{ptr}{ };
                ~iterator() = default;
                iterator( const iterator & ) = default;
                iterator& operator=( const iterator & ) = default;
                reference  operator*() { return m_ptr->data; }
                const_reference  operator*() const { return m_ptr->data; }
                iterator operator++() { m_ptr = m_ptr->next; return iterator{m_ptr}; }
                iterator operator++(int) { m_ptr = m_ptr->next; return iterator{m_ptr->prev};  }
                iterator operator--() { m_ptr = m_ptr->prev; return iterator{m_ptr}; }
                iterator operator--(int) { m_ptr = m_ptr->prev; return iterator{m_ptr->next};  }
                bool operator==( const iterator & rhs ) const { return m_ptr == rhs.m_ptr; }
                bool operator!=( const iterator & rhs ) const { return !(m_ptr == rhs.m_ptr); }

                //=== Other methods that you might want to implement.
                /// it += 3; // Go forth  3 positions within the container. 
                iterator operator+=( difference_type step) { 
                    for(difference_type i = 0; i < step; i++)
                        this++;
                    return iterator{m_ptr};
                }

                /// it -= 3; // Go back 3 positions within the container. 
                iterator operator-=(  difference_type step ){
                    for(difference_type i = 0; i < step; i++)
                        this--;
                    return iterator{m_ptr};
                }

                /// it->method()
                pointer operator->( void ) const { /* TODO */ return nullptr; }

                /// it1 - it2
                difference_type operator-( const iterator & rhs ) const { return std::distance(m_ptr, rhs.mm_ptr); }

                // We need friendship so the list<T> class may access the m_ptr field.
                friend class list<T>;

                friend std::ostream & operator<< ( std::ostream & os_, const iterator & s_ )
                {
                    os_ << "[@"<< s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
                    return os_;
                }
        };


        //=== Private members.
        private:
            size_t m_len;    // comprimento da lista.
            Node * m_head;   // Head node.
            Node * m_tail;   // Tail node.

        public:
        //=== Public interface

        //=== [I] Special members
        
        /**
         * @brief Regular constructor.
         */
        list():
            m_len{0}
        { 
            m_head = new Node();
            m_tail = new Node();

            // Head and tail.
            m_head->next = m_tail;
            m_tail->prev = m_head;
        }
        

        /**
         * @brief Constructor (size).
         *
         *  Head & tail nodes.
         *     +---+    +---+
         *     |   |--->|   |--+
         *     | H |    | T |  |
         *  +--|   |<---|   |  |
         *  |  +---+    +---+  |
         *  |                  |
         * ===                ===
         *  =                  =
         */
        explicit list( size_t count) : list()
        {
           // count default-inserted instances of T.
           for(size_t i = 0; i < count; i++) 
               push_back(T{});  
        }

        /**
         * @brief Construct a new list given a range [first, last).
         */
        template< typename InputIt >
        list( InputIt first, InputIt last ) : list() { 
            // Insert elements.
            for(auto it = first; it != last; it++) 
              push_back(*it);
        }

        /**
         * @brief Copy constructor.
         */
        list( const list & clone_ ) : list() {
            Node* n = clone_.m_head->next;
            while (n->next != nullptr) {
                push_back(n->data);
                n = n->next;
            }
        }

        /**
         * @brief Constructor from initialize list.
         */
        list( std::initializer_list<T> ilist_ ) : list()
        {
            // Insert elements.
           for(auto it = ilist_.begin(); it != ilist_.end(); it++) 
              push_back(*it);
        }

        /**
         * @brief Destructor.
         */
        ~list() { 
            clear();       // Delete nodes between head and tail.
            delete m_head; // Delete the head.
            delete m_tail; // Delete the tail. 
        }

        /**
         * @brief Assignment operator.
         */
        list & operator=( const list & rhs ) { 
            if(!empty()) { clear(); } // First, we need to clear if it's not empty.
            // Copy content.
            Node* n = rhs.m_head->next;             
            while (n->next != nullptr) {
                push_back(n->data);
                n = n->next;
            }
            return *this;
        }
        
        /**
         * @brief Assignment operator.
         */
        list & operator=( std::initializer_list<T> ilist_ ) {
            if(!empty()) {clear(); } // First, we need to clear if it's not empty.
            // Copy content.
            for(auto it = ilist_.begin(); it != ilist_.end(); it++) 
                push_back(*it);
            return *this;
        }

        //=== [II] ITERATORS
        iterator begin() { return iterator{m_head->next}; }
        const_iterator cbegin() const  { return const_iterator{m_head->next}; }
        iterator end() { return iterator{m_tail}; }
        const_iterator cend() const  { return const_iterator{m_tail}; }

        //=== [III] Capacity/Status
        bool empty ( void ) const { return m_len == 0;}
        size_t size(void) const { return m_len; }
        
        //=== [IV] Modifiers
        /**
         * @brief Remove all elements from the container. 
         * All the memory associated with the list is be released.
         */
        void clear()  { erase(begin(), end()); }

        /**
         * @brief Return the object at the beginning of the list.
         */
        T front( void ) { return m_head->next->data; }

        /**
         * @brief Return constant reference to the object at the beginning of the list.
         */
        T front( void ) const { return m_head->next->data; }

        /**
         * @brief Return the object at the end of the list.
         */
        T back( void ) {  return m_tail->prev->data; }

        /**
         * @brief Return constant reference to the object at the end of the list.
         */
        T back( void ) const { return m_tail->prev->data; }

        /**
         * @brief Add an element to the front of the list.
         * @param value_ Element that will be added.
         */
        void push_front( const T & value_ ) { insert(begin(), value_); }

        /**
         * @brief Add an element to the end of the list.
         * @param value_ Element that will be added.
         */
        void push_back( const T & value_ ) { insert(end(), value_); }

        /**
         * @brief Remove the object at the front of the list.
         */
        void pop_front( ) { erase(begin()); }

        /**
         * @brief Remove the object at the end of the list.
         */
        void pop_back( ) { erase(m_tail->prev); }

        //=== [IV-a] MODIFIERS W/ ITERATORS
        /**
         * @brief Replace the contents of the list with copies of the elements in the range [first; last).
         */
        template < class InItr >
        void assign( InItr first_, InItr last_ )
        { 
            clear();
            while (first_ != last_) {
                push_back(*first_);
                first_++;
            }
        }

        /**
         * @brief Replaces the contents of the list with the elements from the initializer list ilist_.
         */
        void assign( std::initializer_list<T> ilist_ )
        { 
            clear();
            for(auto it = ilist_.begin(); it != ilist_.end(); it++) 
                push_back(*it);
        }

        /**
         * @brief Insert an element before pos_.
         * @param pos_ Position immediately after insertion position.
         * @return Iterator to the position of the inserted item.
         */
        iterator insert(iterator pos_, const T & value_ ) { 
            Node *n = new Node{ value_};
            n->prev = pos_.m_ptr->prev;
            n->next = pos_.m_ptr;
            pos_.m_ptr->prev->next = n;
            pos_.m_ptr->prev = n;
            m_len++;
            return iterator{n}; 
            
        }

        /**
         * @brief Insert elements from the range [first; last) before pos_.
         * @param pos_ Position immediately after insertion position.
         * @return Iterator to the last inserted element.
         */
        template < typename InItr >
        iterator insert( iterator pos_, InItr first_, InItr last_ ) { 
            while (first_ != last_) {
                insert(pos_,*first_);
                first_++;
            }
            return pos_;
         }
        
        /**
         * @brief Insert elements from the initializer list ilist_ before cpos_.
         * @param cpos_ Position immediately after insertion position.
         * @return Iterator to the last inserted element.
         */
        iterator insert( iterator cpos_, std::initializer_list<T> ilist_ ) { 
            for(auto it = ilist_.begin(); it != ilist_.end(); it++) 
                insert(cpos_, *it);
            return cpos_; 
        }

        /**
         * @brief Remove the element at position it_.
         * @param it_ Iterator to the element to be removed.
         * @return Iterator to the element that follows it_ before the call.
         */
        iterator erase( iterator it_ ) {
            Node * temp = it_.m_ptr->next;
            it_.m_ptr->prev->next = it_.m_ptr->next;
            it_.m_ptr->next->prev = it_.m_ptr->prev;
            delete it_.m_ptr;
            m_len--;
            return iterator{temp}; 
            
        }

        /**
         * @brief Remove elements in the range [first; last).
         * @param start Iterator to start of range.
         * @param end Iterator to the element immediately after the last element in the removed range.
         * @return Iterator to the element that follows range before the call.
         */
        iterator erase( iterator start, iterator end )
        {
            while(start != end) { start = erase(start); } 
            return end; 
        }

        const_iterator find( const T & value_ ) const
        { /* TODO */ return const_iterator{}; }

        iterator find( const T & value_ )
        { /* TODO */ return iterator{}; }

        //=== [V] UTILITY METHODS
        /**
         * @brief Merge the two lists into one.
         * The lists should be sorted in ascending order.
         * @param other List containing the elements that will be transferred to this.
         */
        void merge( list & other ) { 
            Node * t_aux = m_head->next;
            Node * o_aux = other.m_head->next;
            Node * temp = o_aux; 
            while(t_aux != nullptr && o_aux->next != nullptr) {   
                if(o_aux->data < t_aux->data) { 
                    // Node becomes recognized by the list.
                    temp = o_aux;
                    o_aux = o_aux->next;
                    temp->next = t_aux;
                    t_aux->prev->next = temp;
                    temp->prev = t_aux->prev;
                    t_aux->prev = temp;
                    m_len++;
                    other.m_len--;
                } else if(t_aux->next == nullptr && o_aux->next != nullptr) { 
                    // This is over, but other may still contain elements.
                    // In this case, all remaining elements of other are greater than the last element of this.
                    // Insert all remaining elements of other at the end of this.
                    temp = o_aux;
                    o_aux = o_aux->next;
                    temp->next = t_aux;
                    t_aux->prev->next = temp;
                    temp->prev = t_aux->prev;
                    t_aux->prev = temp;
                    m_len++;
                    other.m_len--;
                } else {t_aux = t_aux->next; }
            }
            
            // Adjust head and tail.
            other.m_head->next = other.m_tail;
            other.m_tail->prev = other.m_head;
        }

        /**
         * @brief Transfer all elements from other into *this.
         * The elements are inserted before the element pointed to by pos.
         * @param pos Position immediately after insertion position.
         * @param other List containing the elements that will be transferred to this.
         */
        void splice( const_iterator pos, list & other ) {
            m_len += other.size();
            // Next of the node before pos recognizes the first node of other.
            pos.m_ptr->prev->next = other.m_head->next; 
            // Next of first node of other points to before pos.
            other.m_head->next->prev = pos.m_ptr->prev; 
            //Last element of other points to pos
            other.m_tail->prev->next = pos.m_ptr; 
            //Prev of pos points to last element of other
            pos.m_ptr->prev = other.m_tail->prev; 

            // Reassign head and tail and reize.
            other.m_len = 0;
            other.m_head->next = other.m_tail;
            other.m_tail->prev = other.m_head;     
        }

        /**
         * @brief Reverse the list.
         * Change the next and prev of each node until it gets at the end.
         */
        void reverse( void ) { 
            Node * aux;
            Node * changer = m_head;
            do
            {
                // Swap prev and next pointers of each node.
                // i. e., for a node N, N->prev becomes N->next and N->next becomes N->prev.
                aux = changer->next; 
                std::swap(changer->next, changer->prev);
                changer = aux;
            } while (changer != nullptr);
            // Finally, we swap the names.
            std::swap(m_head,m_tail); 
        }
        
        /**
         * @brief Erase duplicates values
         * This method only removes consecutive duplicate elements 
         */
        void unique( void ) { 
            iterator first = begin();
            iterator last = end();
            
            if (begin() == end())
                return;

            iterator next = first;
            //This while pass checking if the actual value is repeated
            while (++next != last){
                if (*first == *next){
                   erase(next);
                }else
                    first = next;
                next = first;
            }
            return;
        }
        
        /**
         * @brief Sort list, using merge sort.
         * 
         */
        void sort( void ) { 
            // Empty or only one element.
            if(size() <= 1) { return; }

            // Half divider.
            iterator it_aux = begin();
            size_t half_size = size()/2;
            for(size_t i = 0; i < half_size; i++)
                it_aux++;
            list<T> list_aux;
            // Define the end of the new list.
            list_aux.m_tail->prev = m_tail->prev;
            m_tail->prev->next =  list_aux.m_tail;
            // Define the begin of the new list.
            m_tail->prev = it_aux.m_ptr->prev;
            it_aux.m_ptr->prev->next = m_tail;
            it_aux.m_ptr->prev = nullptr;
            // Define the end of the main list.
            list_aux.m_head->next = it_aux.m_ptr;
            it_aux.m_ptr->prev = list_aux.m_head;
            //Adjust the new size;
            list_aux.m_len = size() - half_size;
            m_len = half_size; 
            
            // Recursive calls until reaching the base case.
            sort();
            list_aux.sort();
            // Merge. 
            merge(list_aux);  

        }
        
    };

    //=== [VI] OPETARORS
    /**
     * @brief Equality operators.
     * @return bool True if l1_ and l2_ are equal; false otherwise.
     */
    template < typename T >
    inline bool operator==( const sc::list<T> & l1_, const sc::list<T> & l2_ )
    {
        if(l1_.size() != l2_.size()) return false;
        auto it1 = l1_.cbegin();
        auto it2 = l2_.cbegin();
        while(it1 != l1_.cend()) {
            if(*it1 != *it2) return false;
            it1++;
            it2++;
        }
        return true;
    }

    /**
     * @brief Difference operators.
     * @return bool True if l1_ and l2_ are different; false otherwise.
     */
    template < typename T >
    inline bool operator!=( const sc::list<T> & l1_, const sc::list<T> & l2_ ) { return !(l1_ == l2_); }
}
#endif

