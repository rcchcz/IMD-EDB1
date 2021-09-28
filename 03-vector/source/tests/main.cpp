#include<iostream>
#include<vector>

#include "include/tm/test_manager.h"
#include "../include/vector.h"

#define which_lib sc
// To run tests with the STL's vector, uncomment the line below.
// #define which_lib std

// ============================================================================
// TESTING VECTOR AS A CONTAINER OF INTEGERS
// ============================================================================

int main( void )
{
    TestManager tm{ "Testing a vector of integer"};

    {
        BEGIN_TEST(tm,"DefaultConstructor", "vector<int> vec;");

        std::vector<int> vec;

        EXPECT_EQ( vec.size(), 0);
        EXPECT_EQ( vec.capacity(), 0);
        EXPECT_TRUE( vec.empty() );
    }
    
    {
        BEGIN_TEST(tm,"ConstructorSize", "vec(size)");

        which_lib::vector<int> vec(10);

        EXPECT_EQ( vec.size(), 10);
        EXPECT_EQ( vec.capacity(), 10);
        EXPECT_FALSE( vec.empty() );
    }
    
    {
        BEGIN_TEST(tm,"ListContructor", "vector<int> vec{1, 2, 3}");

        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };

        EXPECT_EQ( vec.size(), 5 );
        EXPECT_FALSE( vec.empty() );

        for( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( (int)i+1, vec[i] );
    }   

    {
        BEGIN_TEST(tm,"RangeConstructor", "vector<int> vec{ first, last }");
        // Range = the entire vector.
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
        
        which_lib::vector<int> vec2{ vec.begin(), vec.end() };

        EXPECT_EQ( vec2.size(), 5 );
        EXPECT_FALSE( vec.empty() );

        for( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( (int)i+1, vec[i] );

        // Range is part of the vector.
        which_lib::vector<int> vec3( std::next( vec.begin(), 1 ), std::next( vec.begin(), 3 ) );
        auto offset{1};
        // which_lib::vector<int> vec3( vec.begin() + offset , vec.begin() + 3 );
        EXPECT_EQ( vec3.size(), 2 );
        EXPECT_FALSE( vec3.empty() );

        for( auto i{0u} ; i < vec3.size() ; ++i )
            EXPECT_EQ( vec[i+offset], vec3[i] );
    }
   
    {
        BEGIN_TEST(tm, "CopyConstructor","vector<int> vec_clone{ vec }");
        // Range = the entire vector.
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2{ vec };

        EXPECT_EQ( vec2.size(), 5 );
        EXPECT_EQ( vec2.capacity(), 5 );
        EXPECT_FALSE( vec2.empty() );

        // CHeck whether the copy worked.
        for( auto i{0u} ; i < vec2.size() ; ++i )
            EXPECT_EQ( (int)i+1, vec2[i] );

        // Change the original vector and check whether that also changes the second vec.
        // Of course, this should not happen.
        vec[2] = 10;
        for( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( (int)i+1, vec2[i] );
    }
 
    // {
    // BEGIN_TEST(tm, "MoveConstructor", "move the elements from another");
    // // Range = the entire vector.
    // which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
    // which_lib::vector<int> vec2( std::move( vec ) );

    // EXPECT_EQ( vec2.size(), 5 );
    // // EXPECT_FALSE( vec2.empty() );

    // // CHeck whether the copy worked.
    // for( auto i{0u} ; i < vec2.size() ; ++i )
    // EXPECT_EQ( (int)i+1, vec2[i] );
    // }


    {
        BEGIN_TEST(tm, "AssignOperator", "vec1 = vec2");
        // Range = the entire vector.
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2;

        vec2 = vec;
        EXPECT_EQ( vec2.size(), 5 );
        EXPECT_EQ( vec2.capacity(), 5 );
        EXPECT_FALSE( vec2.empty() );

        // CHeck whether the copy worked.
        for( auto i{0u} ; i < vec2.size() ; ++i )
            EXPECT_EQ( (int) i+1, vec2[i] );
    }


        // {
        // BEGIN_TEST(tm, "MoveAssignOperator", "Move Assign Operator");
        // // Range = the entire vector.
        // which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
        // which_lib::vector<int> vec2;

        // vec2 = std::move( vec );
        // EXPECT_EQ( vec2.size(), 5 );
        // EXPECT_FALSE( vec2.empty() );
        // EXPECT_EQ( vec.size(), 0 );
        // EXPECT_EQ( vec.capacity(), 0 );
        // EXPECT_TRUE( vec.empty() );

        // // CHeck whether the copy worked.
        // for( auto i{0u} ; i < vec2.size() ; ++i )
        // EXPECT_EQ( (int)i+1, vec2[i] );
        // }


    {
        BEGIN_TEST(tm, "ListInitializerAssign", "vector<int> vec = { 1, 2, 3 }");
        // Range = the entire vector.
        which_lib::vector<int> vec = { 1, 2, 3, 4, 5 };

        EXPECT_EQ( vec.size(), 5 );
        EXPECT_EQ( vec.capacity(), 5 );
        EXPECT_FALSE( vec.empty() );

        // CHeck whether the copy worked.
        for( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( (int)i+1, vec[i] );
    }

    {
        BEGIN_TEST(tm, "Size", "vec.size()");

        which_lib::vector<int> vec = { 1, 2, 3, 4, 5 };
        EXPECT_EQ( vec.size(), 5 );
        EXPECT_EQ( vec.capacity(), 5 );
        vec.clear();
        EXPECT_EQ( vec.size(), 0 );
        EXPECT_EQ( vec.capacity(), 5 );

        size_t final_len{7}; // The final length of array.
        which_lib::vector<int> vec2;
        EXPECT_EQ( vec2.size(), 0 );
        for( auto i{0u} ; i < final_len ; ++i )
        {
            vec2.push_back(i);
            EXPECT_EQ( vec2.size(), i+1 );
        }

        which_lib::vector<int> vec3(vec2);
        EXPECT_EQ( vec3.size(), final_len );

        vec3.pop_back();
        vec3.pop_back();
        EXPECT_EQ( vec3.size(), final_len-2 );
        vec3.pop_back();
        vec3.pop_back();
        vec3.pop_back();
        vec3.pop_back();
        vec3.pop_back();
        EXPECT_EQ( vec3.size(), 0 );
    }


    {
        BEGIN_TEST(tm, "Clear", "vec.clear()");
        // Range = the entire vector.
        which_lib::vector<int> vec = { 1, 2, 3, 4, 5 };

        EXPECT_EQ( vec.size(), 5 );
        EXPECT_EQ( vec.capacity(), 5 );
        EXPECT_FALSE( vec.empty() );

        vec.clear();

        EXPECT_EQ( vec.size(), 0 );
        EXPECT_EQ( vec.capacity(), 5 );
        EXPECT_TRUE( vec.empty() );
    }

    {
        BEGIN_TEST(tm, "PushBack", "vec.push_back(value)");
        // #1 From an empty vector.
        which_lib::vector<int> vec;

        EXPECT_TRUE( vec.empty() );
        for ( auto i{0} ; i < 5 ; ++i )
        {
            vec.push_back( i+1 );
            EXPECT_EQ( (int)vec.size(),  i+1 );
        }
        EXPECT_FALSE( vec.empty() );

        for( auto i{4u} ; i >= vec.size() ; --i )
            EXPECT_EQ( (int)i+1, vec[i] );

        // Remove all elements.
        vec.clear();
        EXPECT_TRUE( vec.empty()  );
        // Insert again.
        for ( auto i{0u} ; i < 5 ; ++i )
        {
            vec.push_back( i+1 );
            EXPECT_EQ( vec.size(),  i+1 );
        }
        EXPECT_FALSE( vec.empty() );

        for( auto i{4u} ; i >= vec.size() ; --i )
            EXPECT_EQ( (int)i+1, vec[i] );
    }

    {
        BEGIN_TEST(tm, "PopBack", "vec.pop_back()");
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };

        while( not vec.empty() )
        {
            vec.pop_back();
            // Check whether we have the same list except for the last.
            for( auto i{0u} ; i < vec.size() ; ++i )
                EXPECT_EQ( (int)i+1, vec[i] );
        }
    }


    {
        BEGIN_TEST(tm, "Front", "reference front() version: vec.front() = x");
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };

        auto i{0};
        while( not vec.empty() )
        {
            auto current_size = vec.size();
            EXPECT_EQ( vec.front(), ++i );
            vec.front() = 100;
            EXPECT_EQ( current_size, vec.size() );
            EXPECT_EQ( vec[0], 100 );

            vec.erase( vec.begin() );
        }
    }

    {
        BEGIN_TEST(tm, "FrontConst","const front() version: x = vec.front()");

        const which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
        EXPECT_EQ( vec.front(), 1 );

        const which_lib::vector<char> vec2{ 'a', 'e', 'i', 'o', 'u' };
        EXPECT_EQ( vec2.front(), 'a' );
    }


    {
        BEGIN_TEST(tm, "Back","reference back() version: vec.back() = x");
        // #1 From an empty vector.
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };

        auto i{5};
        while( not vec.empty() )
        {
            auto current_size = vec.size();
            EXPECT_EQ( vec.back(), i-- );
            vec.back() = 100;
            EXPECT_EQ( current_size, vec.size() );
            EXPECT_EQ( vec[vec.size()-1], 100 );
            vec.pop_back();
        }
    }


    {
        BEGIN_TEST(tm, "BackConst","const back() version: x = vec.back()");
        // #1 From an empty vector.
        const which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
        EXPECT_EQ( vec.back(), 5 );

        const which_lib::vector<char> vec2{ 'a', 'e', 'i', 'o', 'u' };
        EXPECT_EQ( vec2.back(), 'u' );
    }


    {
        BEGIN_TEST(tm, "AssignCountValue","Assign count value: vec.assign(3, value)");
        // #1 From an empty vector.
        which_lib::vector<long> vec{ 1, 2, 3, 4, 5 };

        EXPECT_EQ( vec.size(), 5 );
        auto original_cap = vec.capacity();

        // Test assign with a count smaller than the original vec size.
        long value{-4};
        vec.assign( 3, value ); // 3 < 5 
        EXPECT_EQ( vec.size(), 3 );
        // Capacity should be the same, because we do not need to allocate new memory..
        EXPECT_EQ( vec.capacity(), original_cap );
        // Verify the elements.
        for ( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( value, vec[i] );

        // Test assign with a count GREATER than the original vec size.
        value = 42;
        vec.assign( 10, value ); // 10 > 5
        EXPECT_EQ( vec.size(), 10 );
        EXPECT_GE( vec.capacity(), original_cap );
        // Verify the elements.
        for ( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( value, vec[i] );
    }




    {
        BEGIN_TEST(tm, "OperatorBracketsRHS","Operator Brackets RHS: x = vec[i]");
        const which_lib::vector<int> vec { 1, 2, 3, 4, 5 };
        const which_lib::vector<int> vec2 { 1, 2, 3, 4, 5 };

        for ( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( vec[i], vec2[i]);
    }


    {
        BEGIN_TEST(tm, "OperatorBracketsLHS","Operator Brackets LHS: vec[i] = x");
        which_lib::vector<int> vec { 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2 { 10, 20, 30, 40, 50 };

        for ( auto i{0u} ; i < vec.size() ; ++i )
            vec[i] = vec2[i];
        for ( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( vec[i], vec2[i]);
    }


    {
        BEGIN_TEST(tm, "AtRHS","at() as RHS: x = vec.at(i);");
        const which_lib::vector<int> vec { 1, 2, 3, 4, 5 };
        const which_lib::vector<int> vec2 { 1, 2, 3, 4, 5 };

        for ( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( vec.at(i), vec2.at(i));

        // Testing exception throwing.
        bool worked{false};
        try { vec.at( 40 ); }
        catch( std::out_of_range & e )
        { worked = true; }

        EXPECT_TRUE( worked );
    }


   {
        BEGIN_TEST(tm, "AtLHS","at() as a LHS: vec.at(i) = x;");
        which_lib::vector<int> vec { 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2 { 10, 20, 30, 40, 50 };

        for ( auto i{0u} ; i < vec.size() ; ++i )
            vec.at(i) = vec2.at(i);
        for ( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( vec.at(i), vec2.at(i) );

        // Testing exception throwing.
        bool worked{false};
        try { vec.at( vec.size() ) = 100; }
        catch( std::out_of_range & e )
        { worked = true; }

        EXPECT_TRUE( worked );
    }

    {
        BEGIN_TEST(tm, "Reserve","reserve()");
        which_lib::vector<int> vec { 1, 2, 3, 4, 5 };

        EXPECT_EQ( vec.capacity(), 5u );
        vec.reserve(10);
        EXPECT_EQ( vec.capacity(), 10u );
        vec.reserve(3); // Nothing happens here.
        EXPECT_EQ( vec.capacity(), 10u );

        auto i{0};
        for( const auto & e : vec )
        {
            EXPECT_EQ( e, ++i );
        }

    }

    {
        BEGIN_TEST(tm, "Capacity","capacity()");

        which_lib::vector<int> vec { 1, 2, 3, 4, 5 };
        EXPECT_EQ( vec.capacity(), 5u );

        which_lib::vector<int> vec2{ vec };
        EXPECT_EQ( vec2.capacity(), 5u );

        which_lib::vector<int> vec3;
        EXPECT_EQ( vec3.capacity(), 0u );

        vec3 = vec2;
        EXPECT_EQ( vec2.capacity(), 5u );

        which_lib::vector<int> vec4 = { 1, 2, 3 };
        EXPECT_EQ( vec4.capacity(), 3u );

        which_lib::vector<int> vec5( 100 );
        EXPECT_EQ( vec5.capacity(), 100u );
    }

    {
        BEGIN_TEST(tm, "ShrinkToFit","shrink_to_fit()");
        // #1 From an empty vector.
        which_lib::vector<int> vec { 1, 2, 3, 4, 5 };

        // Original cap is 5
        EXPECT_EQ( vec.capacity(), 5u );
        // Remove 2 elements.
        vec.pop_back();
        vec.pop_back();
        // Capacity should be still the same.
        EXPECT_EQ( vec.capacity(), 5u );
        vec.shrink_to_fit();
        // Now, capacity should be smaller.
        EXPECT_EQ( vec.capacity(), 3 );
        // Did we keep the original values?
        auto i{0};
        for( const auto & e : vec )
            EXPECT_EQ( e , ++i );
    }


    {
        BEGIN_TEST(tm, "OperatorEqual","vec1 == vec2");
        // #1 From an empty vector.
        which_lib::vector<int> vec { 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2 { 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec3 { 1, 2, 8, 4, 5 };
        which_lib::vector<int> vec4 { 8, 4, 5 };

        EXPECT_EQ( vec , vec2 );
        EXPECT_TRUE( not ( vec == vec3 ) );
        EXPECT_TRUE( not ( vec == vec4 ) );
    }


    {
        BEGIN_TEST(tm, "OperatorDifferent","vec1 != =vec2");
        // #1 From an empty vector.
        which_lib::vector<int> vec { 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2 { 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec3 { 1, 2, 8, 4, 5 };
        which_lib::vector<int> vec4 { 8, 4, 5 };

        EXPECT_TRUE( not( vec != vec2 ) );
        EXPECT_NE( vec, vec3 );
        EXPECT_NE( vec,vec4 );
    }


    {
        BEGIN_TEST(tm, "InsertSingleValueAtPosition","vec.insert(pos, value)");
        // #1 From an empty vector.
        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        // Insert at front
        vec.insert( vec.begin(), 0 );
        EXPECT_EQ( vec , ( which_lib::vector<int>{ 0, 1, 2, 4, 5, 6 } ) );
       
        // Insert in the middle
        vec.insert( vec.begin()+3, 3 );
        EXPECT_EQ( vec , ( which_lib::vector<int>{ 0, 1, 2, 3, 4, 5, 6 } ) );
        // Insert at the end
        vec.insert( vec.end(), 7 );
        EXPECT_EQ( vec , ( which_lib::vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7 } ) );
    }

 

    {
        BEGIN_TEST(tm, "InsertRange","vec.insert( pos, first, last)");
        // Aux arrays.
        which_lib::vector<int> vec1 { 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2 { 1, 2, 3, 4, 5 };
        which_lib::vector<int> source { 6, 7, 8, 9, 10 };

        // Inset at the begining.
        vec1.insert( vec1.begin(), source.begin(), source.end() );
        EXPECT_EQ( vec1 , ( which_lib::vector<int>{ 6, 7, 8, 9, 10, 1, 2, 3, 4, 5 } ) );

        // In the middle
        vec1 = vec2;
        vec1.insert( std::next( vec1.begin(), 2 ), source.begin(), source.end() );
        EXPECT_EQ( vec1 , ( which_lib::vector<int>{ 1, 2, 6, 7, 8, 9, 10, 3, 4, 5 } ) );

        // At the end
        vec1 = vec2;
        vec1.insert( vec1.end(), source.begin(), source.end() );
        EXPECT_EQ( vec1 , ( which_lib::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ) );
    }


    {
        BEGIN_TEST(tm, "InsertInitializarList","vec.insert(pos, {1, 2, 3, 4 })");
        // Aux arrays.
        which_lib::vector<int> vec1 { 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2 { 1, 2, 3, 4, 5 };
        which_lib::vector<int> source { 6, 7, 8, 9, 10 };

        // Inset at the begining.
        vec1.insert( vec1.begin(), { 6, 7, 8, 9, 10 } );
        EXPECT_EQ( vec1 , ( which_lib::vector<int>{ 6, 7, 8, 9, 10, 1, 2, 3, 4, 5 } ) );

        // In the middle
        vec1 = vec2;
        vec1.insert( std::next( vec1.begin(), 2 ), { 6, 7, 8, 9, 10 } );
        EXPECT_EQ( vec1 , ( which_lib::vector<int>{ 1, 2, 6, 7, 8, 9, 10, 3, 4, 5 } ) );

        //At the end
        vec1 = vec2;
        vec1.insert( vec1.end(), { 6, 7, 8, 9, 10 } );
        EXPECT_EQ( vec1 , ( which_lib::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ) );
    }

    
    {
        BEGIN_TEST(tm, "AssignCountValue2","vec.assign( count, value)");
        // Initial vector.
        which_lib::vector<char> vec { 'a', 'b', 'c', 'd', 'e' };

        // assigning count values to which_lib::vector, with count < size().
        which_lib::vector<char> vec2 { 'x', 'x', 'x' };
        vec.assign( 3, 'x' );
        EXPECT_EQ( vec , vec2 );
        EXPECT_EQ( vec.size() , 3 );
        EXPECT_EQ( vec.capacity() , 5 );

        // assigning count values to which_lib::vector, with count , size().
        vec = { 'a', 'b', 'c', 'd', 'e' };
        vec.assign( 5, 'y' );
        EXPECT_EQ( vec , ( which_lib::vector<char>{ 'y','y','y','y','y' } ) );
        EXPECT_EQ( vec.size() , 5 );
        EXPECT_EQ( vec.capacity() , 5 );

        // assigning count values to which_lib::vector, with count > size().
        vec = { 'a', 'b', 'c', 'd', 'e' };
        vec.assign( 8, 'z' );
        EXPECT_EQ( vec , ( which_lib::vector<char>{ 'z','z','z','z','z','z','z','z' } ) );
        EXPECT_EQ( vec.size() , 8 );
        EXPECT_EQ( vec.capacity() , 8 );
    }


    {
        BEGIN_TEST(tm, "EraseRange","vec.erase(first, last)");
        // Initial vector.
        which_lib::vector<int> vec { 1, 2, 3, 4, 5 };

        // removing a segment from the beginning.
        auto past_last = vec.erase( vec.begin(), std::next(vec.begin(),3) );
        EXPECT_EQ( vec.begin() , past_last );
        EXPECT_EQ( vec , ( which_lib::vector<int>{ 4, 5 } ) );
        // std::cout << *past_last <<" "<< *vec.begin()<< endl;
        EXPECT_EQ( vec.size() , 2 );

        // removing at the middle.
        vec = { 1, 2, 3, 4, 5 };
        past_last = vec.erase( std::next(vec.begin(),1), std::next(vec.begin(),4) );
        // std::cout  << *past_last << " "<< *std::next(vec.begin(),1)  << std::endl; 
        EXPECT_EQ( std::next(vec.begin(),1) , past_last );
        EXPECT_EQ( vec , ( which_lib::vector<int>{ 1, 5 } ) );
        EXPECT_EQ( vec.size() , 2 );

        // removing a segment that reached the end.
        vec = { 1, 2, 3, 4, 5 };
        past_last = vec.erase( std::next(vec.begin(),2), vec.end() );
        EXPECT_EQ( vec.end() , past_last );
        // std::cout  << *past_last << " "<< *std::next(vec.begin(),2)  << std::endl; 

        EXPECT_EQ( vec , ( which_lib::vector<int>{ 1, 2 } ) );
        EXPECT_EQ( vec.size() , 2 );

        // removing the entire vector.
        vec = { 1, 2, 3, 4, 5 };
        past_last = vec.erase( vec.begin(), vec.end() );
        EXPECT_EQ( vec.end() , past_last );
        EXPECT_TRUE( vec.empty() );
    }


    {
        BEGIN_TEST(tm, "ErasePos","vec.erase(pos)");
        // Initial vector.
        which_lib::vector<int> vec { 1, 2, 3, 4, 5 };

        // removing a single element.
        vec = { 1, 2, 3, 4, 5 };
        auto past_last = vec.erase( vec.begin() );
        EXPECT_EQ( vec , ( which_lib::vector<int>{ 2, 3, 4, 5 } ) );
        EXPECT_EQ( vec.begin() , past_last );
        EXPECT_EQ( vec.size() , 4 );

        // removing a single element in the middle.
        vec = { 1, 2, 3, 4, 5 };
        past_last = vec.erase( std::next(vec.begin(),2) );
        EXPECT_EQ( vec , ( which_lib::vector<int>{ 1, 2, 4, 5 } ) );
        EXPECT_EQ( std::next(vec.begin(),2) , past_last );
        EXPECT_EQ( vec.size() , 4 );

        // removing a single element at the end.
        vec = { 1, 2, 3, 4, 5 };
        past_last = vec.erase( std::next(vec.begin(),vec.size()-1 ) );
        EXPECT_EQ( vec , ( which_lib::vector<int>{ 1, 2, 3, 4 } ) );
        EXPECT_EQ( vec.end() , past_last );
        EXPECT_EQ( vec.size() , 4 );
    }

    tm.summary();
    std::cout << "\n\n";


    // Second batch of tests, focused on the iterator interface

    TestManager tm2{ "Iterator testing"};

    {
        BEGIN_TEST(tm2, "begin","vec.begin()");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.begin();
        EXPECT_EQ( *it , vec[0] );

        auto vec2 = vec;
        vec2[0] = 100; // Changing the copy
        it = vec2.begin();
        EXPECT_NE( *it , vec[0] );
        EXPECT_EQ( *it , vec2[0] );

        auto vec3 { vec };
        vec3[0] = 200; // Changing the copy
        it = vec3.begin();
        EXPECT_NE( *it , vec[0] );
        EXPECT_EQ( *it , vec3[0] );

        which_lib::vector<int> vec4 =  { 1, 2, 4, 5, 6 };
        it = vec4.begin();
        EXPECT_EQ( *it , vec4[0] );
    }

    {
        BEGIN_TEST(tm2, "cbegin","vec.cbegin()");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto cit = vec.cbegin();
        EXPECT_EQ( *cit , vec[0] );

        auto vec2 = vec;
        vec2[0] = 100; // Changing the copy
        cit = vec2.cbegin();
        EXPECT_NE( *cit , vec[0] );
        EXPECT_EQ( *cit , vec2[0] );

        auto vec3 { vec };
        vec3[0] = 200; // Changing the copy
        cit = vec3.cbegin();
        EXPECT_NE( *cit , vec[0] );
        EXPECT_EQ( *cit , vec3[0] );

        which_lib::vector<int> vec4 =  { 1, 2, 4, 5, 6 };
        cit = vec4.cbegin();
        EXPECT_EQ( *cit , vec4[0] );
    }

    {
        BEGIN_TEST(tm2, "end","vec.end()");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.end();
        EXPECT_EQ( *it , vec[vec.capacity()] );

        auto vec2 = vec;
        it = vec2.end();
        EXPECT_NE( it , vec.end() );
        EXPECT_EQ( it , vec2.end() );

        auto vec3 { vec };
        it = vec3.end();
        EXPECT_NE( it , vec.end() );
        EXPECT_EQ( it , vec3.end() );

        which_lib::vector<int> vec4 =  { 1, 2, 4, 5, 6 };
        it = vec4.end();
        EXPECT_EQ( it , vec4.end() );
    }

    {
        BEGIN_TEST(tm2, "cend","vec.cend()");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.cend();
        EXPECT_EQ( it , vec.cend() );

        auto vec2 = vec;
        it = vec2.cend();
        EXPECT_NE( it , vec.cend() );
        EXPECT_EQ( it , vec2.cend() );

        auto vec3 { vec };
        it = vec3.cend();
        EXPECT_NE( it , vec.cend() );
        EXPECT_EQ( it , vec3.cend() );

        which_lib::vector<int> vec4 =  { 1, 2, 4, 5, 6 };
        it = vec4.cend();
        EXPECT_EQ( it , vec4.cend() );
    }

    {
        BEGIN_TEST(tm2, "operator++()","Preincrement, ++it");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.begin();
        size_t i{0};
        while( it != vec.end() )
        {
            // same address
            EXPECT_EQ( *it , vec[i++] );
            ++it;
        }
    }
    
    {
        BEGIN_TEST(tm2, "operator++(int)","Postincrement, it++");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.begin();
        size_t i{0};
        while( it != vec.end() )
        {
            // same address
            EXPECT_EQ( *it , vec[i++] );
            it++;
        }
    }

    {
        BEGIN_TEST(tm2, "operator--()","Predecrement, --it");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.end();
        size_t i{vec.capacity()};
        while( it != vec.begin() )
        {
            // std::cout << it << " == " << &vec[i] << "\n";
            // same address
            EXPECT_EQ( *it , vec[i--] );
            --it;
        }
        EXPECT_EQ( *it , vec[i] );
        // std::cout << it << " == " << &vec[i] << "\n";
    }
    
    {
        BEGIN_TEST(tm2, "operator--(int)","Postdecrement, it--");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.end();
        size_t i{vec.capacity()};
        while( it != vec.begin() )
        {
            // same address
            EXPECT_EQ( *it , vec[i--] );
            it--;
        }
        EXPECT_EQ( *it , vec[i] );
    }

    {
        BEGIN_TEST(tm2, "operator*()"," x = *it1");

        which_lib::vector<int> vec { 1, 2, 3, 4, 5, 6 };

        auto it = vec.begin();
        int i{1};
        while( it != vec.end() )
            EXPECT_EQ( *it++ , i++ );
    }

    {
        BEGIN_TEST(tm2, "operator-()","it1 - it2");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it1 = vec.begin();
        auto it2 = vec.begin();
        ptrdiff_t i{0};
        while( it1 != vec.end() )
        {
            // same address
            EXPECT_EQ( it1-it2 , i );
            i++;
            it1++;
        }
    }

    {
        BEGIN_TEST(tm2, "operator+(int, iterator)","it = 2 + it");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.begin();
        for( size_t i{0} ; i < vec.size() ; ++i )
        {
            // same address
            EXPECT_EQ( *(i+it) , vec[i] );
            // std::cout << (i+it) << " == " << &vec[i] << "\n";
        }
    }

    {
        BEGIN_TEST(tm2, "operator+(iterator, int)","it = it + 2");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.begin();
        for( size_t i{0} ; i < vec.size() ; ++i )
        {
            // same address
            EXPECT_EQ( *(it+i) , vec[i] );
            // std::cout << (i+it) << " == " << &vec[i] << "\n";
        }
    }
    

    {
        BEGIN_TEST(tm2, "operator-(iterator, int)","it = it - 2");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.end()-1;
        for( size_t i{0} ; i < vec.size() ; ++i )
        {
            // same address
            EXPECT_EQ( *(it-i) , vec[vec.size()-i-1] );
        }
    }

    {
        BEGIN_TEST(tm2, "operator==()","it1 == it2");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it1 = vec.begin();
        auto it2 = vec.begin();
        while( it1 != vec.end() )
            EXPECT_EQ( it1++ , it2++ );
    }

    {
        BEGIN_TEST(tm2, "operator!=()","it1 != it2");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it1 = vec.begin();
        auto it2 = vec.end();
        while( it1 != it2 )
        {
            EXPECT_TRUE( it1 != it2 );
            ++it1;
        }
        EXPECT_FALSE( it1 != it2 );
    }
     
    tm2.summary();
   
    return 0;
}
