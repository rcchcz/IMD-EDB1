#include<iostream>
#include<list>
#include <iterator>


#include "include/tm/test_manager.h"
#include "../include/list.h"

#define which_lib sc 
// #define which_lib std
// ============================================================================
// TESTING list AS A CONTAINER OF INTEGERS
// ============================================================================
//
template < typename T>
std::ostream & operator<<( std::ostream &os, const which_lib::list<T> & L )
{
    os << "[ ";
    auto it{ L.cbegin() };
    while ( it != L.cend() )
        os << *it++ << " ";
    os << "]";
    return os;
}

int main( void )
{
    //=== TESTING BASIC OPERATIONS METHODS
    TestManager tm{ "Basic Operations Test Suite"};
   
    {
        BEGIN_TEST(tm,"DefaultConstructor", "default constructor");

        which_lib::list<int> list;

        EXPECT_EQ( list.size(), 0);
        EXPECT_TRUE( list.empty() );
    }
    
    {
        BEGIN_TEST(tm, "ConstructorSize", "Constructor size");

        which_lib::list<int> list(10);

        EXPECT_EQ(list.size(), 10);
        EXPECT_FALSE(list.empty());
    }


    {
        BEGIN_TEST(tm,"ListContructor", "initializer list constructor.");

        which_lib::list<int> list{ 1, 2, 3, 4, 5 };
        EXPECT_EQ( list.size(), 5 );
        EXPECT_FALSE( list.empty() );


        int i { 0 };
        for( auto it = list.cbegin() ; it != list.cend() ; ++i )
            EXPECT_EQ( i+1, *it++ );
    }   

    {
        BEGIN_TEST(tm,"RangeConstructor", "checking constructors with a range of values");
        // Range = the entire list.
        which_lib::list<int> list{ 1, 2, 3, 4, 5 };
        which_lib::list<int> list2( list.begin(), list.end() );

        EXPECT_EQ( list2.size(), 5 );
        EXPECT_FALSE( list.empty() );

        // recover elements to test
        auto i{1};
        for( auto e : list2)
            EXPECT_EQ( e, i++ );

        // Copy only part of the original range.
        which_lib::list<int> list3( std::next( list.begin(), 1 ), std::next( list.begin(), 3 ) );
        EXPECT_EQ( list3.size(), 2 );
        EXPECT_FALSE( list3.empty() );

        auto it2 = std::next( list.begin(), 1 );
        for (auto it = list3.begin() ; it != list3.end() ; ++it, ++it2 )
            EXPECT_EQ( *it, *it2 );
    }

    {
        BEGIN_TEST(tm, "CopyConstructor","constructor copy values of another list.");
        // Range = the entire list.
        which_lib::list<int> list{ 1, 2, 3, 4, 5 };
        which_lib::list<int> list2( list );

        EXPECT_EQ( list2.size(), 5 );
        EXPECT_FALSE( list2.empty() );

        // recover elements to test.

        auto i{1};
        for( auto e : list2 )
            EXPECT_EQ( e, i++ );

        // Changing seq (the original)...
        auto it = std::next( list.begin(), 2 );
        *it = 10;
        // ... should not alter the copy.
        i = 1;
        for( auto e : list2 )
            EXPECT_EQ( e, i++ );
    }
   
#ifdef MOVE_SYNTAX_IMPLEMENTED

    // {
    //     BEGIN_TEST(tm, "Molistonstructor", "move the elements from another");
    //     // Range = the entire list.
    //     which_lib::list<int> list{ 1, 2, 3, 4, 5 };
    //     which_lib::list<int> list2( std::move( list ) );

    //     EXPECT_EQ( list2.size(), 5 );
    //     // EXPECT_FALSE( list2.empty() );

    //     // CHeck whether the copy worked.
    //     for( auto i{0u} ; i < list2.size() ; ++i )
    //         EXPECT_EQ( i+1, list2[i] );
    // }
#endif

 
    {
        BEGIN_TEST(tm, "AssignOperator", "ASSIGN OPERATOR");
        // Range = the entire list.
        which_lib::list<int> list{ 1, 2, 3, 4, 5 };
        which_lib::list<int> list2;

        list2 = list;
        EXPECT_EQ( list2.size(), 5 );
        EXPECT_FALSE( list2.empty() );

        // recover elements to test.
        auto i{1};
        for( auto e : list2 )
            EXPECT_EQ ( e,i++ );;
    }

#ifdef MOVE_SYNTAX_IMPLEMENTED  
    // // {
    // //     BEGIN_TEST(tm, "MoveAssignOperator", "MoveAssignOperator");
    // //     // Range = the entire list.
    // //     which_lib::list<int> list{ 1, 2, 3, 4, 5 };
    // //     which_lib::list<int> list2;

    // //     list2 = std::move( list );
    // //     EXPECT_EQ( list2.size(), 5 );
    // //     EXPECT_FALSE( list2.empty() );
    // //     EXPECT_EQ( list.size(), 0 );
    // //     EXPECT_EQ( list.capacity(), 0 );
    // //     EXPECT_TRUE( list.empty() );

    // //     // CHeck whether the copy worked.
    // //     for( auto i{0u} ; i < list2.size() ; ++i )
    // //         EXPECT_EQ( i+1, list2[i] );
    // // }
#endif


    {
        BEGIN_TEST(tm, "ListInitializerAssign","initializer list assignment");
        // Range = the entire list.
        which_lib::list<int> list = { 1, 2, 3, 4, 5 };

        EXPECT_EQ( list.size(), 5 );
        EXPECT_FALSE( list.empty() );

        // recover elements to test.
        auto i{1};
        for( auto e : list )
            EXPECT_EQ ( e, i++ );
    }


    {
        BEGIN_TEST(tm, "Clear", "clear");
        // Range = the entire list.
        which_lib::list<int> list = { 1, 2, 3, 4, 5 };

        EXPECT_EQ( list.size(), 5 );
        EXPECT_FALSE( list.empty() );

        list.clear();

        EXPECT_EQ( list.size(), 0 );
        EXPECT_TRUE( list.empty() );
    }

    {
        BEGIN_TEST(tm, "PushFront","PushFront");
        // #1 From an empty list.
        which_lib::list<int> list;

        EXPECT_TRUE( list.empty() );
        for ( auto i{0} ; i < 5 ; ++i )
        {
            list.push_front( i+1 );
            EXPECT_EQ( list.size(),  (size_t)i+1 );
        }
        EXPECT_FALSE( list.empty() );

        auto i{5};
        for ( const auto & e: list )
            EXPECT_EQ( e , i-- );


        // REmove all elements.
        list.clear();
        EXPECT_TRUE(list.empty()  );
        for ( auto i{0u} ; i < 5 ; ++i )
        {
            list.push_front( i+1 );
            EXPECT_EQ( list.size(),  i+1 );
        }
        EXPECT_FALSE( list.empty() );

        i = 5;
        for ( const auto & e: list )
        {
            EXPECT_EQ( e , i-- );
        }

    }


    {
        BEGIN_TEST(tm, "PushBack", "PushBack");
        // #1 From an empty list.
        which_lib::list<int> list;

        EXPECT_TRUE( list.empty() );
        for ( auto i{0} ; i < 5 ; ++i )
        {
            list.push_back( i+1 );
            EXPECT_EQ( list.size(),  (size_t)i+1 );
        }
        EXPECT_FALSE( list.empty() );

        auto i{0};
        for ( const auto & e: list )
            EXPECT_EQ( e , ++i );

        // REmove all elements.
        list.clear();
        EXPECT_TRUE( list.empty()  );
        for ( auto i{0} ; i < 5 ; ++i )
        {
            list.push_back( i+1 );
            EXPECT_EQ( list.size(),  (size_t)i+1 );
        }
        EXPECT_FALSE( list.empty() );

        i=0;
        for ( const auto & e: list )
            EXPECT_EQ( e , ++i );
    }

    {
        BEGIN_TEST(tm, "PopBack", "PopBack");
        // #1 From an empty list.
        which_lib::list<int> list{ 1, 2, 3, 4, 5 };

        while( not list.empty() )
        {
            list.pop_back();
            // Checke whether we have the same list except for the last.
            auto i {0};
            for ( const auto & e: list )
                EXPECT_EQ( e , ++i );
        }
    }

    {
        BEGIN_TEST(tm, "PopFront", "PopFront");
        // #1 From an empty list.
        which_lib::list<int> list{ 1, 2, 3, 4, 5 };

        auto start{1};
        while( not list.empty() )
        {
            list.pop_front();
            // Checke whether we have the same list except for the last.
            auto i {start};
            for ( const auto & e: list )
                EXPECT_EQ( e, ++i );
            start++;
        }
    }


    {
        BEGIN_TEST(tm, "Front", "front");
        // #1 From an empty list.
        which_lib::list<int> list{ 1, 2, 3, 4, 5 };

        auto i{0};
        while( not list.empty() )
        {
            auto current_size = list.size();
            EXPECT_EQ( list.front(), ++i );
            EXPECT_EQ( current_size, list.size() );
            list.pop_front();
        }
    }

    {
        BEGIN_TEST(tm, "FrontConst","FrontConst");
        // #1 From an empty list.
        const which_lib::list<int> list{ 1, 2, 3, 4, 5 };
        EXPECT_EQ( list.front(), 1 );

        const which_lib::list<char> list2{ 'a', 'e', 'i', 'o', 'u' };
        EXPECT_EQ( list2.front(), 'a' );
    }


    {
        BEGIN_TEST(tm, "Back","Back");
        // #1 From an empty list.
        which_lib::list<int> list{ 1, 2, 3, 4, 5 };

        auto i{5};
        while( not list.empty() )
        {
            auto current_size = list.size();
            EXPECT_EQ( list.back(), i-- );
            EXPECT_EQ( current_size, list.size() );
            list.pop_back();
        }
    }


    {
        BEGIN_TEST(tm, "BackConst","BackConst");
        // #1 From an empty list.
        const which_lib::list<int> list{ 1, 2, 3, 4, 5 };
        EXPECT_EQ( list.back(), 5 );

        const which_lib::list<char> list2{ 'a', 'e', 'i', 'o', 'u' };
        EXPECT_EQ( list2.back(), 'u' );
    }



    // {
    //     BEGIN_TEST(tm, "AssignCountValue","AssignCountValue");
    //     // #1 From an empty list.
    //     which_lib::list<long> list{ 1, 2, 3, 4, 5 };

    //     EXPECT_EQ( list.size(), 5 );

    //     // Test assign with a count smaller than the original list size.
    //     long value{-4};
    //     list.assign( 3, value );
    //     EXPECT_EQ( list.size(), 3 );
    //     // Capacity should be the same.
    //     // EXPECT_EQ( list.capacity(), original_cap );
    //     // Verify the elements.
    //     for ( auto i{0u} ; i < list.size() ; ++i )
    //         EXPECT_EQ( value, list[i] );

    //     // Test assign with a count GREATER than the original list size.
    //     long new_value{42};
    //     list.assign( 10, new_value );
    //     EXPECT_EQ( list.size(), 10 );
    //     EXPECT_GE( list.capacity(), original_cap );
    //     // Verify the elements.
    //     for ( auto i{0u} ; i < list.size() ; ++i )
    //         EXPECT_EQ( new_value, list[i] );
    // }


    {
        BEGIN_TEST(tm, "OperatorEqual","OperatorEqual");
        // #1 From an empty list.
        which_lib::list<int> list { 1, 2, 3, 4, 5 };
        which_lib::list<int> list2 { 1, 2, 3, 4, 5 };
        which_lib::list<int> list3 { 1, 2, 8, 4, 5 };
        which_lib::list<int> list4 { 8, 4, 5 };

        EXPECT_EQ( list , list2 );
        EXPECT_TRUE( not ( list == list3 ) );
        EXPECT_TRUE( not ( list == list4 ) );
    }


    {
        BEGIN_TEST(tm, "OperatorDifferent","OperatorDifferent");
        // #1 From an empty list.
        which_lib::list<int> list { 1, 2, 3, 4, 5 };
        which_lib::list<int> list2 { 1, 2, 3, 4, 5 };
        which_lib::list<int> list3 { 1, 2, 8, 4, 5 };
        which_lib::list<int> list4 { 8, 4, 5 };

        EXPECT_TRUE( not( list != list2 ) );
        EXPECT_NE( list, list3 );
        EXPECT_NE( list,list4 );
    }
   

    {
        BEGIN_TEST(tm, "InsertSingleValueAtPosition","InsertSingleValueAtPosition");
        // #1 From an empty list.
        which_lib::list<int> list { 1, 2, 4, 5, 6 };

        // Insert at front
        list.insert( list.begin(), 0 );
        EXPECT_EQ( list , ( which_lib::list<int>{ 0, 1, 2, 4, 5, 6 } ) );

        // Insert in the middle
        list.insert( std::next(list.begin(),3), 3 );
        EXPECT_EQ( list , ( which_lib::list<int>{ 0, 1, 2, 3, 4, 5, 6 } ) );

        // Insert at the end
        list.insert( list.end(), 7 );
        EXPECT_EQ( list , ( which_lib::list<int>{ 0, 1, 2, 3, 4, 5, 6, 7 } ) );

    }


    {
        BEGIN_TEST(tm, "InsertRange","InsertRange");
        // Aux arrays.
        which_lib::list<int> list1 { 1, 2, 3, 4, 5 };
        which_lib::list<int> list2 { 1, 2, 3, 4, 5 };
        which_lib::list<int> source { 6, 7, 8, 9, 10 };

        // Inset at the beginning.
        list1.insert( list1.begin(), source.begin(), source.end() );

        EXPECT_EQ( list1 , ( which_lib::list<int>{ 6, 7, 8, 9, 10, 1, 2, 3, 4, 5 } ) );

        // In the middle
        list1 = list2;
        list1.insert( std::next( list1.begin(), 2 ), source.begin(), source.end() );

        EXPECT_EQ( list1 , ( which_lib::list<int>{ 1, 2, 6, 7, 8, 9, 10, 3, 4, 5 } ) );

        // At the end
        list1 = list2;
        list1.insert( list1.end(), source.begin(), source.end() );
        EXPECT_EQ( list1 , ( which_lib::list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ) );

        // // Outside
        // list1 = list2;
        // list1.insert( std::next( list1.end(), 2 ) , source.begin(), source.end() );
        // EXPECT_EQ( list1 , ( which_lib::list<int>{ 1, 2, 3, 4, 5 } ) );

    }


    {
        BEGIN_TEST(tm, "InsertInitializarList","InsertInitializarList");
        // Aux arrays.
        which_lib::list<int> list1 { 1, 2, 3, 4, 5 };
        which_lib::list<int> list2 { 1, 2, 3, 4, 5 };
        which_lib::list<int> source { 6, 7, 8, 9, 10 };

        // Inset at the beginning.
        list1.insert( list1.begin(), { 6, 7, 8, 9, 10 } );
        EXPECT_EQ( list1 , ( which_lib::list<int>{ 6, 7, 8, 9, 10, 1, 2, 3, 4, 5 } ) );

        // In the middle
        list1 = list2;
        list1.insert( std::next( list1.begin(), 2 ), { 6, 7, 8, 9, 10 } );
        EXPECT_EQ( list1 , ( which_lib::list<int>{ 1, 2, 6, 7, 8, 9, 10, 3, 4, 5 } ) );

        // At the end
        list1 = list2;
        list1.insert( list1.end(), { 6, 7, 8, 9, 10 } );
        EXPECT_EQ( list1 , ( which_lib::list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ) );

        // // Outside
        // list1 = list2;
        // list1.insert( std::next( list1.end(), 2 ) , { 6, 7, 8, 9, 10 } );
        // EXPECT_EQ( list1 , ( which_lib::list<int>{ 1, 2, 3, 4, 5 } ) );
    }

 
    // // {
    // //     BEGIN_TEST(tm, "AssignCountValue2","AssignCountValue2");
    // //     // Initial list.
    // //     which_lib::list<char> list { 'a', 'b', 'c', 'd', 'e' };

    // //     // assigning count values to which_lib::list, with count < size().
    // //     list.assign( 3, 'x' );
    // //     which_lib::list<char> list2 { 'x', 'x', 'x' };
    // //     //ASSERT_EQ( list , ( which_lib::list<char>{ 'x', 'x', 'x' } ) );
    // //     EXPECT_EQ( list , list2 );
    // //     EXPECT_EQ( list.size() , 3 );
    // //     EXPECT_EQ( list.capacity() , 5 );

    // //     // assigning count values to which_lib::list, with count , size().
    // //     list = { 'a', 'b', 'c', 'd', 'e' };
    // //     list.assign( 5, 'y' );
    // //     EXPECT_EQ( list , ( which_lib::list<char>{ 'y','y','y','y','y' } ) );
    // //     EXPECT_EQ( list.size() , 5 );
    // //     EXPECT_EQ( list.capacity() , 5 );

    // //     // assigning count values to which_lib::list, with count > size().
    // //     list = { 'a', 'b', 'c', 'd', 'e' };
    // //     list.assign( 8, 'z' );
    // //     EXPECT_EQ( list , ( which_lib::list<char>{ 'z','z','z','z','z','z','z','z' } ) );
    // //     EXPECT_EQ( list.size() , 8 );
    // //     EXPECT_EQ( list.capacity() , 8 );
    // // }


    {
        BEGIN_TEST(tm, "EraseRange","EraseRange");
        // Initial list.
        which_lib::list<int> list { 1, 2, 3, 4, 5 };

        // removing a segment from the beginning.
        auto past_last = list.erase( list.begin(), std::next(list.begin(),3) );
        EXPECT_EQ( list.begin() , past_last );
        EXPECT_EQ( list , ( which_lib::list<int>{ 4, 5 } ) );
        EXPECT_EQ( list.size() , 2 );

        // removing at the middle.
        list = { 1, 2, 3, 4, 5 };
        past_last = list.erase( std::next(list.begin(),1), std::next(list.begin(),4) );
        EXPECT_EQ( std::next(list.begin(),1) , past_last );
        EXPECT_EQ( list , ( which_lib::list<int>{ 1, 5 } ) );
        EXPECT_EQ( list.size() , 2 );

        // removing a segment that reached the end.
        list = { 1, 2, 3, 4, 5 };
        past_last = list.erase( std::next(list.begin(),2), list.end() );
        EXPECT_EQ( list.end() , past_last );

        EXPECT_EQ( list , ( which_lib::list<int>{ 1, 2 } ) );
        EXPECT_EQ( list.size() , 2 );
        // removing the entire list.
        list = { 1, 2, 3, 4, 5 };
        past_last = list.erase( list.begin(), list.end() );
        EXPECT_EQ( list.end() , past_last );
        EXPECT_TRUE( list.empty() );
    }


    {
        BEGIN_TEST(tm, "ErasePos","ErasePos");
        // Initial list.
        which_lib::list<int> list { 1, 2, 3, 4, 5 };

        // removing a single element.
        list = { 1, 2, 3, 4, 5 };
        auto past_last = list.erase( list.begin() );
        EXPECT_EQ( list , ( which_lib::list<int>{ 2, 3, 4, 5 } ) );
        EXPECT_EQ( list.begin() , past_last );
        EXPECT_EQ( list.size() , 4 );

        // removing a single element in the middle.
        list = { 1, 2, 3, 4, 5 };
past_last = list.erase( std::next(list.begin(),2) );
        EXPECT_EQ( list , ( which_lib::list<int>{ 1, 2, 4, 5 } ) );

        std::cout << " \n";
        EXPECT_EQ( std::next(list.begin(),2) , past_last );
        EXPECT_EQ( list.size() , 4 );

        // removing a single element at the end.
        list = { 1, 2, 3, 4, 5 };
        past_last = list.erase( std::next(list.begin(),list.size()-1 ) );
        EXPECT_EQ( list , ( which_lib::list<int>{ 1, 2, 3, 4 } ) );
        EXPECT_EQ( list.end() , past_last );
        EXPECT_EQ( list.size() , 4 );
    }

    {
        BEGIN_TEST(tm, "Reverse","Checking the reverse methos");
        // Regular case odd list length 
        which_lib::list<int> list { 1, 2, 3, 4, 5 };
        list.reverse();
        EXPECT_EQ( list , ( which_lib::list<int>{ 5, 4, 3, 2, 1 } ) );
        // Regular case even list length
        which_lib::list<int> list2 { 1, 2, 3, 4, 5, 6 };
        list2.reverse();
        EXPECT_EQ( list2 , ( which_lib::list<int>{ 6, 5, 4, 3, 2, 1 } ) );
        // Single element case
        which_lib::list<int> list3 { 1 };
        list3.reverse();
        EXPECT_EQ( list3 , ( which_lib::list<int>{ 1 } ) );
        // Empty list case
        which_lib::list<int> list4;
        list4.reverse();
        EXPECT_TRUE( list4.empty() );
    }

    tm.summary();


    //=== TESTING ITERATOR METHODS
    TestManager tm2{ "Iterator Test Suite"};

    {
        BEGIN_TEST(tm2, "begin","list.begin()");

        which_lib::list<int> list { 1, 2, 4, 5, 6 };
        which_lib::list<int>::iterator it = list.begin();
        EXPECT_EQ( 1, *it );

        auto list2 = list;
        it = list2.begin();
        EXPECT_EQ( 1, *it );

        auto list3 = list;
        it = list3.begin();
        EXPECT_EQ( 1, *it );

        // which_lib::list<int> vec4 =  { 1, 2, 4, 5, 6 };
        which_lib::list<int> list4 = { 10, 11, 12, 13, 14 };
        it = list4.begin();
        EXPECT_EQ( 10, *it );
    }

    {
        BEGIN_TEST(tm2, "cbegin","list.cbegin()");

        which_lib::list<int> list { 1, 2, 4, 5, 6 };
        which_lib::list<int>::const_iterator cit = list.cbegin();
        EXPECT_EQ( 1, *cit );

        auto list2 = list;
        cit = list2.cbegin();
        EXPECT_EQ( 1, *cit );

        auto list3 = list;
        cit = list3.cbegin();
        EXPECT_EQ( 1, *cit );

        which_lib::list<int> list4 = { 10, 11, 12, 13, 14 };
        cit = list4.cbegin();
        EXPECT_EQ( 10, *cit );
    }

    {
        BEGIN_TEST(tm2, "end","list.end()");

        which_lib::list<int> list { 1, 2, 4, 5, 6 };
        which_lib::list<int>::iterator it = std::next( list.begin(), 5 );
        EXPECT_EQ( it, list.end() );

        auto list2 = list;
        it = std::next( list2.begin(), 5 );
        EXPECT_EQ( it, list2.end() );

        auto list3 = list;
        it = std::next( list3.begin(), 5 );
        EXPECT_EQ( it, list3.end() );

        // which_lib::list<int> vec4 =  { 1, 2, 4, 5, 6 };
        which_lib::list<int> list4 = { 10, 11, 12, 13, 14 };
        it = std::next( list4.begin(), 5 );
        EXPECT_EQ( it, list4.end() );
    }

    {
        BEGIN_TEST(tm2, "cend","list.cend()");

        which_lib::list<int> list { 1, 2, 3, 4, 5 };
        which_lib::list<int>::const_iterator it = std::next(list.cbegin(), 5 );
        EXPECT_EQ( it, list.cend() );

        auto list2 = list;
        it = std::next( list2.cbegin(), 5 );
        EXPECT_EQ( it, list2.cend() );

        auto list3 = list;
        it = std::next( list3.cbegin(), 5 );
        EXPECT_EQ( it, list3.cend() );

        which_lib::list<int> list4 = { 10, 11, 12, 13, 14 };
        it = std::next( list4.cbegin(), 5 );
        EXPECT_EQ( it, list4.cend() );
    }

    {
        BEGIN_TEST(tm2, "operator++()","Preincrement, ++it");

        which_lib::list<int> list { 1, 2, 3, 4, 5 };
        int expected[]{1, 2, 3, 4, 5};

        auto it = list.begin();
        for ( const auto & e : expected )
        {
            EXPECT_EQ( *it, e );
            ++it;
        }
    }
    
    {
        BEGIN_TEST(tm2, "operator++(int)","Postincrement, it++");

        which_lib::list<int> list { 1, 2, 3, 4, 5 };
        int expected[]{1, 2, 3, 4, 5};

        auto it = list.begin();
        for ( const auto & e : expected )
        {
            EXPECT_EQ( *it, e );
            it++;
        }
    }

    {
        BEGIN_TEST(tm2, "operator--()","Preincrement, --it");

        which_lib::list<int> list { 1, 2, 3, 4, 5 };
        int expected[]{5, 4, 3, 2, 1};

        auto it = list.end();
        for ( const auto & e : expected )
        {
            --it;
            EXPECT_EQ( *it, e );
        }
    }
    
    {
        BEGIN_TEST(tm2, "operator--(int)","Postincrement, it--");

        which_lib::list<int> list { 1, 2, 3, 4, 5 };
        int expected[]{5, 4, 3, 2, 1};

        auto it = list.end();
        for ( const auto & e : expected )
        {
            it--;
            EXPECT_EQ( *it, e );
        }
    }

    {
        BEGIN_TEST(tm2, "operator*()"," x = *it1");

        which_lib::list<int> list { 1, 2, 3, 4, 5, 6 };

        auto it = list.begin();
        int i{1};
        while( it != list.end() )
            EXPECT_EQ( *it++ , i++ );
    }

    std::cout << std::endl;
    
    tm2.summary();

    //=== TESTING UTILITY METHODS
    
    TestManager tm3{ "Utility Operations Test Suite"};

    {
        BEGIN_TEST(tm3, "Merge 1","merging two interwoven regular sorted lists.");
        which_lib::list<int> list_a{ 0, 1, 3, 5, 7, 9 };        // List A
        which_lib::list<int> list_b{ 2, 4, 6, 8 };              // List B
        which_lib::list<int> list_r{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // List Result

        list_a.merge( list_b ); // Merger B into A.
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        EXPECT_TRUE( list_b.empty() ); // List B must be empty (all nodes moved to A).
    }
   
    {
        BEGIN_TEST(tm3, "Merge 2","merging two sequential regular sorted lists.");
        which_lib::list<int> list_a{ 0, 1, 2, 3, 4, 5 };        // List A
        which_lib::list<int> list_b{ 6, 7, 8, 9 };              // List B
        which_lib::list<int> list_r{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // List Result

        list_a.merge( list_b ); // Merger B into A.
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        EXPECT_TRUE( list_b.empty() ); // List B must be empty (all nodes moved to A).
    }
    {
        BEGIN_TEST(tm3, "Merge 3","merging two sequential (inverse) regular sorted lists.");
        which_lib::list<int> list_a{ 4, 5, 6, 7, 8, 9 };        // List A
        which_lib::list<int> list_b{ 0, 1, 2, 3 };              // List B
        which_lib::list<int> list_r{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // List Result

        list_a.merge( list_b ); // Merger B into A.
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        EXPECT_TRUE( list_b.empty() ); // List B must be empty (all nodes moved to A).
    }
    {
        BEGIN_TEST(tm3, "Merge 4","merging an empty list into a sorted list.");
        which_lib::list<int> list_a;        // List A
        which_lib::list<int> list_b{ 0, 1, 2, 3 };              // List B
        which_lib::list<int> list_r{ 0, 1, 2, 3 }; // List Result

        list_a.merge( list_b ); // Merger B into A.
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        EXPECT_TRUE( list_b.empty() ); // List B must be empty (all nodes moved to A).
    }
    {
        BEGIN_TEST(tm3, "Merge 5","merging a sorted list into an empty list.");
        which_lib::list<int> list_a;        // List A
        which_lib::list<int> list_b{ 0, 1, 2, 3 };              // List B
        which_lib::list<int> list_r{ 0, 1, 2, 3 }; // List Result

        list_a.merge( list_b ); // Merger B into A.
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        EXPECT_TRUE( list_b.empty() ); // List B must be empty (all nodes moved to A).
    }
    {
        BEGIN_TEST(tm3, "Merge 6","merging sorted list with same value.");
        which_lib::list<int> list_a{ 1, 1, 1 };        // List A
        which_lib::list<int> list_b{ 1, 1, 1, 1 };              // List B
        which_lib::list<int> list_r{ 1, 1, 1, 1, 1, 1, 1 }; // List Result

        list_a.merge( list_b ); // Merger B into A.
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        EXPECT_TRUE( list_b.empty() ); // List B must be empty (all nodes moved to A).
    }

    {
        BEGIN_TEST(tm3, "Splice 1","splicing at the beginning.");
        which_lib::list<int> list_a{ 1, 2, 3, 4, 5 };              // List B
        which_lib::list<int> list_b{ 10, 20, 30 };        // List A
        which_lib::list<int> list_r{ 10, 20, 30, 1, 2, 3, 4, 5 }; // List Result

        auto where{ list_a.cbegin() }; // where do we splice into?
        list_a.splice( where, list_b ); // Merger B into A.
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        EXPECT_TRUE( list_b.empty() ); // List B must be empty (all nodes moved to A).
    }
    
    {
        BEGIN_TEST(tm3, "Splice 2","splicing at the end.");
        which_lib::list<int> list_a{ 1, 2, 3, 4, 5 };              // List B
        which_lib::list<int> list_b{ 10, 20, 30 };        // List A
        which_lib::list<int> list_r{ 1, 2, 3, 4, 5, 10, 20, 30 }; // List Result

        auto where{ list_a.cend() }; // where do we splice into?
        list_a.splice( where, list_b ); // Merger B into A.
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        EXPECT_TRUE( list_b.empty() ); // List B must be empty (all nodes moved to A).
    }
    {
        BEGIN_TEST(tm3, "Splice 3", "splicing at the middle.");
        which_lib::list<int> list_a{ 1, 2, 3, 4, 5 };              // List B
        which_lib::list<int> list_b{ 10, 20, 30 };        // List A
        which_lib::list<int> list_r{ 1, 2, 10, 20, 30, 3, 4, 5 }; // List Result

        auto where{ list_a.cbegin() }; // where do we splice into?
        std::advance( where, 2 ); // Jump 2 nodes.
        list_a.splice( where, list_b ); // Merger B into A.
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        EXPECT_TRUE( list_b.empty() ); // List B must be empty (all nodes moved to A).
    }
    {
        BEGIN_TEST(tm3, "Splice 4", "splicing an empty list into another list.");
        which_lib::list<int> list_a{ 1, 2, 3, 4, 5 };              // List B
        which_lib::list<int> list_b;        // List A
        which_lib::list<int> list_r{ 1, 2, 3, 4, 5 }; // List Result

        auto where{ list_a.cbegin() }; // where do we splice into?
        std::advance( where, 2 ); // Jump 2 nodes.
        list_a.splice( where, list_b ); // Merger B into A.
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        EXPECT_TRUE( list_b.empty() ); // List B must be empty (all nodes moved to A).
    }
    {
        BEGIN_TEST(tm3, "Splice 5", "splicing an empty list into another list.");
        which_lib::list<int> list_a{ 1, 2, 3, 4 };              // List B
        which_lib::list<int> list_a_backup{ 1, 2, 3, 4 };              // List B
        which_lib::list<int> list_r[] {
            { 10, 20, 1, 2, 3, 4 },
            { 1, 10, 20, 2, 3, 4 },
            { 1, 2, 10, 20, 3, 4 },
            { 1, 2, 3, 10, 20, 4 },
            { 1, 2, 3, 4, 10, 20 }
        }; // List Result

        size_t i{0};
        size_t how_many_times{ list_a.size() };
        while ( i < how_many_times )
        {
            which_lib::list<int> list_b{ 10, 20 };  // List B
            list_a = list_a_backup;                 // restore original list
            auto where{ list_a.cbegin() };          // where do we splice into?
            std::advance( where, i );               // Adavance splice position accordingly.
            list_a.splice( where, list_b );         // splice B into A.
            // std::cout << ">>> i = " << i << ", List A = " << list_a << '\n';
            EXPECT_EQ( list_r[i], list_a );       // List A must be equal to list Result.
            EXPECT_TRUE( list_b.empty() );          // List B must be empty (all nodes moved to A).
            ++i;
        }
    }
 
    {
        BEGIN_TEST(tm3, "Reverse 1", "reverse a regular list.");
        which_lib::list<int> list_a{ 1, 2, 3, 4, 5 };              // List B
        which_lib::list<int> list_r{ 5, 4, 3, 2, 1 }; // List Result

        list_a.reverse();
        auto add_first{ list_a.begin() };
        auto add_last{ std::prev( list_a.end() ) };
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        // Make sure no new node has been created.
        *add_first = 50; // Iterators must remain valid.
        *add_last = 10;
        which_lib::list<int> list_r2{ 50, 4, 3, 2, 10 }; // List Result
        EXPECT_EQ( list_r2, list_a ); // List A must be equal to list Result.
    }
    {
        BEGIN_TEST(tm3, "Reverse 2", "reversing a single element list.");
        which_lib::list<int> list_a{ 1 };              // List B
        which_lib::list<int> list_r{ 1 }; // List Result

        list_a.reverse();
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
    }
    {
        BEGIN_TEST(tm3, "Reverse 3", "reversing an empty list.");
        which_lib::list<int> list_a{ 1 };              // List B
        which_lib::list<int> list_r{ 1 }; // List Result

        list_a.reverse();
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
    }


    {
        BEGIN_TEST(tm3, "Unique 1", "unique on a regular list.");
        which_lib::list<int> list_a{ 1, 2, 2, 3, 3, 2, 1, 1, 2 };              // List B
        which_lib::list<int> list_r{ 1, 2, 3, 2, 1, 2 }; // List Result

        list_a.unique();
        auto add_first{ list_a.begin() };
        auto add_last{ std::prev( list_a.end() ) };
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        // Make sure no new node has been created.
        *add_first = 10; // Iterators must remain valid.
        *add_last = 20;
        which_lib::list<int> list_r2{ 10, 2, 3, 2, 1, 20 }; // List Result
        EXPECT_EQ( list_r2, list_a ); // List A must be equal to list Result.
    }

    {
        BEGIN_TEST(tm3, "Unique 2", "all equal to a single value.");
        which_lib::list<int> list_a{ 1, 1, 1, 1, 1 };              // List B
        which_lib::list<int> list_r{ 1 }; // List Result

        list_a.unique();
        auto add_first{ list_a.begin() };
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        // Make sure no new node has been created.
        *add_first = 10; // Iterators must remain valid.
        which_lib::list<int> list_r2{ 10}; // List Result
        EXPECT_EQ( list_r2, list_a ); // List A must be equal to list Result.
    }
    {
        BEGIN_TEST(tm3, "Unique 3", "list have already only unique elements.");
        which_lib::list<int> list_a{ 1, 2, 3, 4, 5 };              // List B
        which_lib::list<int> list_r{ 1, 2, 3, 4, 5 }; // List Result

        list_a.unique();
        auto add_first{ list_a.begin() };
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        // Make sure no new node has been created.
        *add_first = 10; // Iterators must remain valid.
        which_lib::list<int> list_r2{ 10, 2, 3, 4, 5}; // List Result
        EXPECT_EQ( list_r2, list_a ); // List A must be equal to list Result.
    }
    {
        BEGIN_TEST(tm3, "Unique 4", "unique on an empty list.");
        which_lib::list<int> list_a{ };              // List B
        which_lib::list<int> list_r{ }; // List Result

        list_a.unique();
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
    }
    {
        BEGIN_TEST(tm3, "Sort 1", "sorting a regular list.");
        which_lib::list<int> list_a{ 4, 2, 1, 5, 3 };              // List B
        which_lib::list<int> list_r{ 1, 2, 3, 4, 5 }; // List Result{}
        list_a.sort();

        auto add_first{ list_a.begin() };
        auto add_last{ std::prev( list_a.end() ) };
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        // Make sure no new node has been created.
        *add_first = 10; // Iterators must remain valid.
        *add_last = 50;
        which_lib::list<int> list_r2{ 10, 2, 3, 4, 50 }; // List Result
        EXPECT_EQ( list_r2, list_a ); // List A must be equal to list Result.
    }
  
    {
        BEGIN_TEST(tm3, "Sort 2", "sorting an already sorted list.");
        which_lib::list<int> list_a{ 1, 2, 3, 4, 5 };              // List B
        which_lib::list<int> list_r{ 1, 2, 3, 4, 5 }; // List Result

        list_a.sort();
        auto add_first{ list_a.begin() };
        auto add_last{ std::prev( list_a.end() ) };
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
        // Make sure no new node has been created.
        *add_first = 10; // Iterators must remain valid.
        *add_last = 50;
        which_lib::list<int> list_r2{ 10, 2, 3, 4, 50 }; // List Result
        EXPECT_EQ( list_r2, list_a ); // List A must be equal to list Result.
    }
    
    {
        BEGIN_TEST(tm3, "Sort 3", "sorting an empty list.");
        which_lib::list<int> list_a{  };              // List B
        which_lib::list<int> list_r{  }; // List Result

        list_a.sort();
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
    }
 
    {
        BEGIN_TEST(tm3, "Sort 4", "testing stability of the sorting algorithm.");
        struct Card{
            int value; std::string face;
            // Default comparator for Card type.
            inline bool operator<( const Card &a ) const
            { return value < a.value; }
            inline bool operator==( const Card &a ) const
            { return value == a.value; }
            inline bool operator!=( const Card &a ) const
            { return !(value == a.value); }
        };
        which_lib::list<Card> list_a{
            { 10, "clubs"},
            { 4, "hearts" },
            { 8, "diamond" },
            { 10, "spades" },
            { 4, "clubs" },
            { 7, "spades" },
            { 8, "clubs" }
        };
        which_lib::list<Card> list_r{
            { 4, "hearts" },
            { 4, "clubs" },
            { 7, "spades" },
            { 8, "diamond" },
            { 8, "clubs" },
            { 10, "clubs"},
            { 10, "spades" },
        };

        auto add_first{ list_a.begin() };
        auto add_last{ std::prev( list_a.end() ) };
        list_a.sort();
    
        EXPECT_EQ( list_r, list_a ); // List A must be equal to list Result.
     
        // Make sure no new node has been created.
        *add_first = {100, "CLUBS"}; // Iterators must remain valid.
        *add_last = {80, "CLUBS"};
        which_lib::list<Card> list_r2{
            { 4, "hearts" },
            { 4, "clubs" },
            { 7, "spades" },
            { 8, "diamond" },
            { 80, "CLUBS" },
            { 100, "CLUBS"},
            { 10, "spades" },
        };
        EXPECT_EQ( list_r2, list_a ); // List A must be equal to list Result.
    }
 
    std::cout << std::endl;
    tm3.summary();

    return 0;
}
    
