/**
 * @file driver_dictionary.cpp
 * @brief Test suit for the linear search
 */

#include <iostream>   // cout, endl
#include <cassert>    // assert()
#include <random>     // random_device, mt19937
#include <iterator>   // std::begin(), std::end()
#include <algorithm>

#include "include/tm/test_manager.h"

#include "../src/searching.h"
using namespace sa;

int main ( void )
{
    // Creates a test manager for the DAL class.
    TestManager tm{ "Linear Search Test Suite" };

    {
        //=== Test #1
        BEGIN_TEST(tm, "BasicSearch", "Search for all n elements present in the array." );
        // DISABLE();
        int A[]{ 1, 2, 3, 4, 5, 6, 7 };
        std::random_device rd;
        std::shuffle(std::begin(A), std::end(A), rd);
        //std::copy( std::begin(A), std::end(A), std::ostream_iterator<int>(std::cout, " ") );

        // Looking for each element from A in A.
        for ( const auto & e : A )
        {
            auto result = lsearch( std::begin(A), std::end(A), e );
            EXPECT_EQ( *result, e );
        }
    }

    {
        //=== Test #2
        BEGIN_TEST(tm, "FailedSearchLeft", "Search for an element not present, which is smaller than the lowest value element." );
        // DISABLE();
        value_type A[]{ 1, 2, 3, 4, 5, 6, 7 };
        std::random_device rd;
        std::shuffle(std::begin(A), std::end(A), rd);

        auto target{-4};
        auto result = lsearch( std::begin(A), std::end(A), target );
        EXPECT_EQ( result, std::end(A) );
    }

    {
        //=== Test #3
        BEGIN_TEST(tm, "FailedSearchRight", "Search for an element not present, which is greater than the highest value element." );
        // DISABLE();
        value_type A[]{ 1, 2, 3, 4, 5, 6, 7 };
        std::random_device rd;
        std::shuffle(std::begin(A), std::end(A), rd);

        auto target{10};
        auto result = lsearch( std::begin(A), std::end(A), target );
        EXPECT_EQ( result, std::end(A) );
    }

    {
        //=== Test #4
        BEGIN_TEST(tm, "FailedSearchInBetween", "Search for an element not present, which has a value in the range of elements." );
        // DISABLE();
        value_type A[]{ 1, 3, 5, 7, 9, 11 };
        std::random_device rd;
        std::shuffle(std::begin(A), std::end(A), rd);

        for ( auto i{2} ; i < 11 ; i+=2 )
        {
            auto result = lsearch( std::begin(A), std::end(A), i );
            EXPECT_EQ( result, std::end(A) );
        }
    }

    {
        //=== Test #4
        BEGIN_TEST(tm, "EmptyArray", "Search for an element in an empty array." );
        // DISABLE();
        value_type A[]{ 1, 3, 5, 7, 9, 11 };

        // Let us simulate an empty range here.
        auto first = std::begin(A);
        auto last = std::begin(A);
        auto result = lsearch( first, last, 10 );
        EXPECT_EQ( result, last );
    }

    tm.summary();
    std::cout << std::endl;

    // Creates a test manager for the DAL class.
    TestManager tm2{ "Binary Search Test Suite" };

    {
        //=== Test #1
        BEGIN_TEST(tm2, "BasicSearch", "Search for all n elements present in the array." );
        // DISABLE();
        value_type A[]{ 1, 2, 3, 4, 5, 6, 7 };

        // Looking for each element from A in A.
        for ( const auto & e : A )
        {
            auto result = bsearch( std::begin(A), std::end(A), e );
            EXPECT_EQ( *result, e );
            EXPECT_EQ( e-1, std::distance(std::begin(A), result ) );
        }
    }
    {
        //=== Test #2
        BEGIN_TEST(tm2, "NotPresentToLeft", "Search for an element that is not present, whose value is smaller than the first element of the array." );
        // DISABLE();
        value_type A[]{ 1, 2, 3, 4, 5, 6, 7 };

        auto target{-4};
        auto result = bsearch( std::begin(A), std::end(A), target );
        EXPECT_EQ( result, std::end(A) );
    }

    {
        //=== Test #3
        BEGIN_TEST(tm2, "NotPresentToRight", "Search for an element that is not present, whose value is greater than the last element of the array." );
        // DISABLE();
        value_type A[]{ 1, 2, 3, 4, 5, 6, 7 };

        auto target{10};
        auto result = bsearch( std::begin(A), std::end(A), target );
        EXPECT_EQ( result, std::end(A) );
    }

    {
        //=== Test #4
        BEGIN_TEST(tm2, "NotPresentInBetween", "Search for an element that is not present, whose value is between the first and the last elements of the array." );
        // DISABLE();
        value_type A[]{ 1, 3, 5, 7, 9, 11 };

        for ( auto i{2} ; i < 11 ; i+=2 )
        {
            auto result = bsearch( std::begin(A), std::end(A), i );
            EXPECT_EQ( result, std::end(A) );
        }
    }

    {
        //=== Test #5
        BEGIN_TEST(tm2, "EmptyRange", "Search for an element on an empty range.");
        // DISABLE();
        value_type A[]{ 1, 3, 5, 7, 9, 11 };

        // Let us simulate an empty range here.
        auto first = std::begin(A);
        auto last = std::begin(A);
        auto result = bsearch( first, last, 10 );
        EXPECT_EQ( result, last );
    }


    tm2.summary();
    std::cout << std::endl;

    // Creates a test manager for the DAL class.
    TestManager tm3{ "Lower Bound Test Suite" };

    {
        //=== Test #1
        BEGIN_TEST(tm3, "EmptyRange", "Lower bound applied to an empty range." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 3 };
        auto lb_it = lbound( std::begin(A), std::begin(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::begin(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( lb_it, expected_lb_it );
    }
    {
        //=== Test #2
        BEGIN_TEST(tm3, "RangeHasSingleValue", "Range has a repeated single value, same as target." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

        auto value{ 1 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( *lb_it, value );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    {
        //=== Test #3
        BEGIN_TEST(tm3, "RegularCallOddLength", "Regular call, range size is odd." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 3 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( *lb_it, value );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    {
        //=== Test #4
        BEGIN_TEST(tm3, "LBToTheLeftOddLength", "Target element located to the left end of range" );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 2 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( *lb_it, value );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    {
        //=== Test #5
        BEGIN_TEST(tm3, "LBToTheRightOddLength", "Target element located to the right end of range." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 4 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( *lb_it, value );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    {
        //=== Test #6
        BEGIN_TEST(tm3, "LBAtBeginningOddLength", "Target is the first element." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 1 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( *lb_it, value );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    {
        //=== Test #7
        BEGIN_TEST(tm3, "LBAtEndOddLength", "Target is the first element." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 5 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( *lb_it, value );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    {
        //=== Test #8
        BEGIN_TEST(tm3, "RangeHasSingleValueLBNotPresent", "Range has a repeated single value, target not present." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

        auto value{ 2 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    {
        //=== Test #9
        BEGIN_TEST(tm3, "TargetOutsideLeft", "Target is not present and is lower than the first element." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ -2 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( lb_it, std::begin(A) );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    {
        //=== Test #10
        BEGIN_TEST(tm3, "TargetOutsideRight", "Target is not present and is greater than the last element.");
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 8 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( lb_it, std::end(A) );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    {
        //=== Test #11
        BEGIN_TEST(tm3, "TargetOutsideInBetween", "Target is not present and is a value between the first and the last element.");
        // DISABLE();
        value_type A[]{ 1, 1, 1, 3, 3, 5, 5, 5, 7, 7, 7, 9, 9 };

        auto value{ 2 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( lb_it, std::begin(A)+3 );
        EXPECT_EQ( lb_it, expected_lb_it );

        value = 4 ;
        lb_it = lbound( std::begin(A), std::end(A), value );
        expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( lb_it, std::begin(A)+5 );
        EXPECT_EQ( lb_it, expected_lb_it );

        value = 6 ;
        lb_it = lbound( std::begin(A), std::end(A), value );
        expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( lb_it, std::begin(A)+8 );
        EXPECT_EQ( lb_it, expected_lb_it );

        value = 8 ;
        lb_it = lbound( std::begin(A), std::end(A), value );
        expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( lb_it, std::begin(A)+11 );
        EXPECT_EQ( lb_it, expected_lb_it );
    }
    {
        //=== Test #12
        BEGIN_TEST(tm3, "RegularCallEvenLength", "Regular call, range size is odd." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 3 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( *lb_it, value );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    {
        //=== Test #13
        BEGIN_TEST(tm3, "LBToTheLeftEvenLength", "Target element located to the left end of range" );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 2 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( *lb_it, value );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    {
        //=== Test #14
        BEGIN_TEST(tm3, "LBToTheRightEvenLength", "Target element located to the right end of range." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 4 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( *lb_it, value );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    {
        //=== Test #15
        BEGIN_TEST(tm3, "LBAtBeginningEvenLength", "Target is the first element." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 1 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( *lb_it, value );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    {
        //=== Test #16
        BEGIN_TEST(tm3, "LBAtEndEvenLength", "Target is the first element." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 5 };
        auto lb_it = lbound( std::begin(A), std::end(A), value );
        auto expected_lb_it = std::lower_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( lb_it, nullptr );
        EXPECT_EQ( *lb_it, value );
        EXPECT_EQ( lb_it, expected_lb_it );
    }

    tm3.summary();
    std::cout << std::endl;

    // Creates a test manager for the DAL class.
    TestManager tm4{ "Uppert Bound Test Suite" };

    {
        //=== Test #1
        BEGIN_TEST(tm4, "EmptyRange", "Upper bound applied to an empty range." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 3 };
        auto ub_it = ubound( std::begin(A), std::begin(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::begin(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );
    }
    {
        //=== Test #2
        BEGIN_TEST(tm4, "RangeHasSingleValue", "Range has a repeated single value, same as target." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

        auto value{ 1 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    {
        //=== Test #3
        BEGIN_TEST(tm4, "RegularCallOddLength", "Regular call, range size is odd." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 3 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    {
        //=== Test #4
        BEGIN_TEST(tm4, "UbToTheLeftOddLength", "Target element located to the left end of range" );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 2 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    {
        //=== Test #5
        BEGIN_TEST(tm4, "UbToTheRightOddLength", "Target element located to the right end of range." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 4 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    {
        //=== Test #6
        BEGIN_TEST(tm4, "UbAtBeginningOddLength", "Target is the first element." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 1 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    {
        //=== Test #7
        BEGIN_TEST(tm4, "UbAtEndOddLength", "Target is the first element." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 5 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    {
        //=== Test #8
        BEGIN_TEST(tm4, "RangeHasSingleValueUbNotPresent", "Range has a repeated single value, target not present." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

        auto value{ 2 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    {
        //=== Test #9
        BEGIN_TEST(tm4, "TargetOutsideLeft", "Target is not present and is lower than the first element." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ -2 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, std::begin(A) );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    {
        //=== Test #10
        BEGIN_TEST(tm4, "TargetOutsideRight", "Target is not present and is greater than the last element.");
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 8 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, std::end(A) );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    {
        //=== Test #11
        BEGIN_TEST(tm4, "TargetOutsideInBetween", "Target is not present and is a value between the first and the last element.");
        // DISABLE();
        value_type A[]{ 1, 1, 1, 3, 3, 5, 5, 5, 7, 7, 7, 9, 9 };

        auto value{ 2 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );

        value = 4 ;
        ub_it = ubound( std::begin(A), std::end(A), value );
        expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );

        value = 6 ;
        ub_it = ubound( std::begin(A), std::end(A), value );
        expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );

        value = 8 ;
        ub_it = ubound( std::begin(A), std::end(A), value );
        expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );
    }
    {
        //=== Test #12
        BEGIN_TEST(tm4, "RegularCallEvenLength", "Regular call, range size is odd." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 3 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    {
        //=== Test #13
        BEGIN_TEST(tm4, "UbToTheLeftEvenLength", "Target element located to the left end of range" );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 2 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    {
        //=== Test #14
        BEGIN_TEST(tm4, "UbToTheRightEvenLength", "Target element located to the right end of range." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 4 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    {
        //=== Test #15
        BEGIN_TEST(tm4, "UbAtBeginningEvenLength", "Target is the first element." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 1 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    {
        //=== Test #16
        BEGIN_TEST(tm4, "UbAtEndEvenLength", "Target is the first element." );
        // DISABLE();
        value_type A[]{ 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5 };

        auto value{ 5 };
        auto ub_it = ubound( std::begin(A), std::end(A), value );
        auto expected_ub_it = std::upper_bound( std::begin(A), std::end(A), value );
        EXPECT_NE( ub_it, nullptr );
        EXPECT_EQ( ub_it, expected_ub_it );
    }

    tm4.summary();
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
