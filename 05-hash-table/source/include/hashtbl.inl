#include "hashtbl.h"

namespace ac {
    /// Constructor
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	HashTbl<KeyType,DataType,KeyHash,KeyEqual>::HashTbl( size_type sz )
        : m_size{2}, m_count{0}, m_max_load_factor{1.0}
	{ 
        m_data_table.resize(find_next_prime(sz)); 
        m_size = m_data_table.size();
    }

    /// Copy constructor
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	HashTbl<KeyType,DataType,KeyHash,KeyEqual>::HashTbl( const HashTbl& source ) : 
    HashTbl(source.m_size) //Default constructor
	{   
        // For each index of vector
        for(auto j = 0; j < source.m_data_table.size(); j++) {
            // For each node of that index
            for(auto i = source.m_data_table[j].begin(); i != source.m_data_table[j].end(); i++) {
                insert(i->m_key, i->m_data);
            }
        }
	}

    /// Initializer constructor
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	HashTbl<KeyType,DataType,KeyHash,KeyEqual>::HashTbl( const std::initializer_list<entry_type>& ilist ) :
    HashTbl(ilist.size()) //Default constructor
	{   
        // For each element of the list
        for(auto i = ilist.begin(); i != ilist.end(); i++) 
            insert(i->m_key, i->m_data);
	}

    /// Assignment operator.
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	HashTbl<KeyType,DataType,KeyHash,KeyEqual>&
    HashTbl<KeyType,DataType,KeyHash,KeyEqual>::operator=( const HashTbl& clone )
    {
        clear();
        //Change the size
        m_data_table.resize(clone.size());
        m_size = m_data_table.size();

        // For each index of vector
        for(auto j = 0; j < clone.m_data_table.size(); j++) {
            // For each item of that index
            for(auto i = clone.m_data_table[j].begin(); i != clone.m_data_table[j].end(); i++) {
                insert(i->m_key, i->m_data);
            }
        }
        return *this;
    }

    /// Assignment initializer list.
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	HashTbl<KeyType,DataType,KeyHash,KeyEqual>&
    HashTbl<KeyType,DataType,KeyHash,KeyEqual>::operator=( const std::initializer_list< entry_type >& ilist )
    {
        clear();
        //Change the size
        m_data_table.resize(ilist.size());
        m_size = m_data_table.size();
        // For each element of the list
        for(auto i = ilist.begin(); i != ilist.end(); i++) 
            insert(i->m_key, i->m_data);
        return *this;
    }


	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	HashTbl<KeyType,DataType,KeyHash,KeyEqual>::~HashTbl( )
	{
        // Clear each list
        clear();
        // Deallocate vector memory
        m_data_table.clear();
	}

	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	bool HashTbl<KeyType,DataType,KeyHash,KeyEqual>::insert( const KeyType & key_, const DataType & new_data_ )
    {
        // Search for address end based on key_
        KeyHash hashFunc;
        KeyEqual equalFunc;
        entry_type new_entry { key_, new_data_};
        auto end{ hashFunc(key_)% m_size};

        try{
            at(key_) = new_data_;
            return false;
        }
        catch(const std::out_of_range& e){
            m_data_table[end].push_front(new_entry);
            m_count++;
            if(m_count / m_size > m_max_load_factor) rehash();
            return true;
        }     
    }
	
    //! Clears the data table.
    template <typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
    void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::clear()
    { 
        // For each list at each index, clear that list
        for(auto i = 0; i < m_data_table.size(); i++)
            m_data_table[i].clear();
        m_count = 0;
    }

    //! Tests whether the table is empty.
    /*!
     * \return true is table is empty, false otherwise.
     */
    template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::empty() const
    { return m_count == 0; }

    //----------------------------------------------------------------------------------------
    //! Retrieves data from the table.
    /*! Retrieves a data item from the table, based on the key associated with the data.
     *  If the data cannot be found, false is returned; otherwise, true is returned instead.
     *  \param key_ Data key to search for in the table.
     *  \param data_item_ Data record to be filled in when data item is found.
     *  \return true if the data item is found; false, otherwise.
     */
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::retrieve( const KeyType & key_, DataType & data_item_ ) const
    {   
        KeyHash hashFunc;
        KeyEqual equalFunc;
        auto end{ hashFunc(key_)% m_size};

        for(auto i = m_data_table[end].begin(); i != m_data_table[end].end(); i++) {
            if(equalFunc(i->m_key, key_)) {
                data_item_ = i->m_data;
                return true;
            }
        }
        return false;
    }

    /// Rehash
    template <typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
    void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::rehash( void )
    {
        HashTbl<KeyType, DataType, KeyHash, KeyEqual> Temp_Table(2*m_size);
        Temp_Table.m_max_load_factor = m_max_load_factor;
        // For each index of vector
        for(auto j = 0; j < m_size; j++) {
            // For each item of that index
            for(auto i = m_data_table[j].begin(); i != m_data_table[j].end(); i++) {
                Temp_Table.insert(i->m_key, i->m_data);
            }
        }
        m_size = Temp_Table.m_size;
        m_data_table = Temp_Table.m_data_table;
    }

	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    bool HashTbl< KeyType, DataType, KeyHash, KeyEqual >::erase( const KeyType & key_ )
    {
        // Search for address end based on key_
        KeyHash hashFunc;
        KeyEqual equalFunc;
        auto end{ hashFunc(key_)% m_size};
        
        // If finds the element with the same key, delete using erase_after
        auto it2  = m_data_table[end].before_begin();
        for(auto it = m_data_table[end].begin(); it != m_data_table[end].end(); it++) {
            if(equalFunc(it->m_key, key_)) {
                m_data_table[end].erase_after(it2);
                m_count--;
                return true;
            }
            it2++;
        }
        return false;
    }


    /// Find the next prime >= n_
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    std::size_t HashTbl<KeyType,DataType,KeyHash,KeyEqual>::find_next_prime( size_type  n_ )
    {
        // Base case
        if (n_ <= 1)
            return 2;
    
        size_type prime = n_;
    
        // Loop until is_prime return true
        while (true) {     
            if(is_prime(prime) == true)
                return prime;
            prime++;
        }
    }

    //This functions find the end based on a key independent if this key exist or not
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    typename HashTbl< KeyType, DataType, KeyHash, KeyEqual >::size_type
    HashTbl< KeyType, DataType, KeyHash, KeyEqual >::count( const KeyType & key_ ) const
    {
        // Search for address end based on key_
        KeyHash hashFunc;
        auto end{ hashFunc(key_)% m_size};

        size_type count = 0;
        for(auto it = m_data_table[end].begin(); it != m_data_table[end].end(); it++) {count ++;}
        return count;           
    }

	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    DataType& HashTbl<KeyType, DataType, KeyHash, KeyEqual>::at( const KeyType & key_ )
    {
        // Search for address end based on key_
        KeyHash hashFunc;
        KeyEqual equalFunc;
        auto end{ hashFunc(key_)% m_size};

        // Loop trouhg the linked list at position end
        // Use KeyEqual to search the key
        for(auto i = m_data_table[end].begin(); i != m_data_table[end].end(); i++) {
            if (equalFunc(i->m_key, key_)) {
                return i->m_data; // If key_ is found, return reference to the data associated with it
            }
        }

        // If key_ is not found, throw std::out_of_range
        throw std::out_of_range( "Key not found." );
    }

	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    DataType& HashTbl<KeyType, DataType, KeyHash, KeyEqual>::operator[]( const KeyType & key_ )
    {
        // Search for address end based on key_
        KeyHash hashFunc;
        KeyEqual equalFunc;
        auto end{ hashFunc(key_)% m_size};

        // Loop trouhg the linked list at position end
        // Use KeyEqual to search the key
        for(auto i = m_data_table[end].begin(); i != m_data_table[end].end(); i++) {
            if (equalFunc(i->m_key, key_)) {
                return i->m_data; // If key_ is found, return reference to the data associated with it
            }
        }
        
        // If key_ is not found, perform insert and return the reference for the data just inserted into the table.
        (m_data_table[end]).push_front( entry_type{ key_, DataType{}});
        m_count++;
        return (m_data_table[end]).begin()->m_data;
    }

    template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    bool HashTbl<KeyType,DataType,KeyHash,KeyEqual>::is_prime(std::size_t n) { 
        // Corner cases
        if(n <= 3) return true;
    
        // This is checked so that we can skip middle five numbers in below loop
        if(n%2 == 0 || n%3 == 0) return false;
    
        for(int i=5; i*i<=n; i=i+6)
            if(n%i == 0 || n%(i+2) == 0)
                return false;
    
        return true;
    }
   
} // Namespace ac.
