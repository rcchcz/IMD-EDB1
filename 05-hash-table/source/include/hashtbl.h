// @author: Selan
//
#ifndef _HASHTBL_H_
#define _HASHTBL_H_

#include <iostream>     // cout, endl, ostream
#include <forward_list> // forward_list
#include <algorithm>    // copy, find_if, for_each
#include <cmath>        // sqrt
#include <iterator>     // std::begin(), std::end()
#include <initializer_list>
#include <memory> // std::unique_ptr
#include <utility> // std::pair
#include <vector>

namespace ac // Associative container
{
	template<class KeyType, class DataType>
	struct HashEntry {
        KeyType m_key;   //! Data key
        DataType m_data; //! The data

        // Regular constructor.
        HashEntry( KeyType kt_, DataType dt_ ) : m_key{kt_} , m_data{dt_}
        {/*Empty*/}

        friend std::ostream & operator<<( std::ostream & os_, const HashEntry & he_ ) {
            // os_ << "{" << he_.m_key << "," << he_.m_data << "}";
            os_ << he_.m_data;
            return os_;
        }
    };

	template< class KeyType,
		      class DataType,
		      class KeyHash = std::hash< KeyType >,
		      class KeyEqual = std::equal_to< KeyType > >
	class HashTbl {
        public:
            // Aliases
            using entry_type = HashEntry<KeyType,DataType>;
            using list_type = std::forward_list< entry_type >;
            using size_type = std::size_t;
            
            /**
             * @brief Default constructor
             */
            explicit HashTbl( size_type table_sz_ = DEFAULT_SIZE );
            
            /**
             * @brief Copy constructor.
             */
            HashTbl( const HashTbl& );
            
            /**
             * @brief Constructor with initializer list.
             */
            HashTbl( const std::initializer_list< entry_type > & );
            
            /**
             * @brief Assignment  operator.
             */
            HashTbl& operator=( const HashTbl& );
            
            /**
             * @brief Assignment operator with initializer list.
             */
            HashTbl& operator=( const std::initializer_list< entry_type > & );
            
            /**
             * @brief Destroy the Hash Tbl object.
             */
            virtual ~HashTbl();
            
            /**
             * @brief Insert into the table an information associated with a key.
             * If the key already exists in the table, the method overwrites the table data with the data passed to the function.
             * @return True, if the insertion was performed successfully;
             * @return False, if overwritten; i.e. it is not the first insert.
             */
            bool insert( const KeyType &, const DataType &  );
            
            /**
             * @brief Get the data associated with a key.
             * 
             * @return true if the data exist, false, other wise.
             */
            bool retrieve( const KeyType &, DataType & ) const;
            
            /**
             * @brief  Given a Key, remove an element.
             * 
             * @return true successfully removed.
             * @return false the element don't exist.
             */
            bool erase( const KeyType & );
            
            /**
             * @brief Clear only the the colisions lists, maintaining the vector.
             */
            void clear();
            
            /**
             * @brief Check if the table is empty.
             * @return True if it is empty; false otherwise.
             */
            bool empty() const;
            
            /**
             * @brief Return the number of elements on the table.
             */
            inline size_type size() const { return m_count; };
            
            /**
             * @brief Return reference to data associate with the Key.
             * 
             * @return DataType&  if exists return the reference, else creates it.
             */
            DataType& at( const KeyType& );
            
            /**
             * @brief Return reference to data associate with the Key.
             * 
             * @return DataType& if exists return the reference, else throw an error.
             */
            DataType& operator[]( const KeyType& );

            /**
             * @brief Given a Key, counts the number of elements with the same adress.
             * 
             * @return size_type Number of elements.
             */
            size_type count( const KeyType& ) const;

            /**
             * @brief Return the load factor value.
             */
            float max_load_factor() const { return m_max_load_factor; };
            
            /**
             * @brief Modify the load factor value.
             */
            void max_load_factor(float mlf) { m_max_load_factor = mlf;};

            friend std::ostream & operator<<( std::ostream & os_, const HashTbl & ht_ ) {
                // TODO
                return os_;
            }

        private:
            /**
             * @brief Check if a number is prime.
             * @param n Number to be checked.
             * @return True if it is prime; false otherwise.
             */
            static bool is_prime(size_type n); 
            
            /**
             * @brief Looks for the first prime greater than or equal to the given number.
             * @param n_ reference number to search for the prime.
             * @return size_type corresponding to the first prime >= n_.
             */
            static size_type find_next_prime( size_type n_); 
            void rehash( void );

        private:
            size_type m_size;  //!< Table size.
            size_type m_count; //!< Number of elements in the table.
            float m_max_load_factor; //!< Load factor.
            static const short DEFAULT_SIZE = 10;
            std::vector<std::forward_list<entry_type>> m_data_table; 
    };

} // MyHashTable
#include "hashtbl.inl"
#endif
