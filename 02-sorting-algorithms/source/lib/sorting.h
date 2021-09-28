/**
 * Several types of sorting algorithms that work on a data range.
 * @author 
 * @date July 5th, 2021
 * @file sorting.h
 */

#ifndef SORTING_H
#define SORTING_H

#include <sstream>
using std::ostringstream;
#include <iterator>
using std::next;
using std::ostream_iterator;
#include <functional>
using std::less;
using std::function;
#include <vector>
using std::vector;
#include <array>
using std::array;
#include <algorithm>
using std::max_element;
using std::for_each;
using std::copy;
#include <cmath>
using std::pow;
#include <string>
using std::string;
using std::to_string;
#include <bits/stdc++.h>
#include <type_traits>
#include <utility>
#include <iomanip>
#include <iostream>
namespace sa { // sa = sorting algorithms
    /// Prints out the range to a string and returns it to the client.
    template <typename FwrdIt>
    std::string to_string(FwrdIt first, FwrdIt last){
        std::ostringstream oss;
        oss << "[ ";
        while (first!=last)
            oss << *first++ << " ";
        oss << "]";
        return oss.str();
    }
    //{{{ INSERTION SORT
    /// Implementation of the Insertion Sort algorithm.
    template< typename RandomIt, typename Compare >
    void insertion(RandomIt first, RandomIt last, Compare cmp){
        for(auto i = 1; i < (last-first); i++){
            for(auto j=i; j > 0 && cmp(*(first+j),*(first+j-1)); j--)
                std::swap(*(first+j),*(first+j-1));
        }
        return;
    }
    //}}} INSERTION SORT

    //{{{ SELECTION SORT
    template< typename RandomIt, typename Compare >
    void selection(RandomIt first, RandomIt last, Compare cmp){
        int sz = std::distance(first, last);
        for(int i = 0; i <sz-1; i++){
            int min_index = i;
            for(int j=i+1; j <sz; j++){
                if(cmp(*(first+j),*(first+min_index)))
                    min_index = j;
            }
            if(min_index != i){
                std::swap(*(first+i),*(first+min_index));   
            }
        }
        return;
    }
    //}}} SELECTION SORT

    //{{{ BUBBLE SORT
    template< typename RandomIt, typename Compare >
    void bubble(RandomIt first, RandomIt last, Compare cmp){
        int temp, sz = std::distance(first, last);
        for(int i = sz; i > 1; i++){
            temp = 0;
            for(int j=1; j < sz; j++){
                if(cmp(*(first+j),*(first+j-1))){
                    std::swap(*(first+j),*(first+j-1));
                    temp = j;
                }
            }  
            i = temp;
        }
        return;  
    }
    //}}} BUBBLE SORT
    
    //{{{ SHELL SORT
    /*
    Knuth sequence was used.
    */
    template< typename RandomIt, typename Compare >
    void shell(RandomIt first, RandomIt last, Compare cmp){
        int gap;
        //Calculate the first gap, based on Knuth sequence
        for(gap = 1; gap < (last-first); gap = 3*gap+1); 
        while (gap > 0){
            //Descrease the gap
            gap = (gap-1)/3;
            //Pass by elements to swap then if necessary
            for(size_t i =0 ; first+gap+i < last ; i++){
                if(cmp(*(first+gap+i),*(first+i))){
                    std::swap(*(first+gap+i),*(first+i));
                    /*In case some element was sawpped, it will 
                    try swap the elements before, maintaining the gap
                    */
                    for(int j = i-gap; j >= 0; j-= gap){   
                        if(cmp(*(first+gap+j),*(first+j))){
                            std::swap(*(first+gap+j),*(first+j));
                        }         
                    }

                }
            }
            
        }
    }
    //}}} SHELL SORT

    //{{{ MERGE SORT
    /*!
     * Merge Sort divides the input range into two halves, calls itself for each of the two halves, and then merges 
     * the two sorted halves. The merge() function is used for merging two halves based on a comparison function.
     *
     * By **less** we mean a _strict order_ binary relation among the elements we
     * wantt to partition.
     *
     * @param first The first element in the range we want to reorder.
     * @param last Past the last element in the range we want to reorder.
     * @param l_first The first element in the left sub-range.
     * @param l_last Past the last element in the left sub-range.
     * @param r_first The first element in the right sub-range.
     * @param r_last Past the last element in the right sub-range.
     * @param cmp A comparison function that returns true if the first parameter is **less** than the second.
     */
    template< typename RandomIt, typename Compare >
    // void merge(RandomIt first, RandomIt last, Compare cmp) {
    void merge( RandomIt l_first, RandomIt l_last, // [l_first; l_last)
            RandomIt r_first, RandomIt r_last, // [r_first; r_last)
            RandomIt first, Compare cmp) {
        
        while(l_first != l_last && r_first != r_last) {
            if(cmp(*l_first, *r_first)) {
                *first = *l_first;
                first++;
                l_first++;
            } else {
                *first = *r_first;
                first++;
                r_first++;
            }
        }

        while(l_first != l_last) {
            *first = *l_first;
            first++;
            l_first++;
        }
    
        while(r_first != r_last) {
            *first = *r_first;
            first++;
            r_first++;
        }
    }

    template< typename RandomIt, typename Compare >
    void mergesort(RandomIt first, RandomIt last, Compare cmp) {
        
        using DataType = typename std::remove_reference<decltype(*std::declval<RandomIt>())>::type;

        int sz = std::distance(first, last);
        
        // basis step: 0 or 1 element
        if(sz < 2) return;

        // find out the size of the first half
        int n = sz/2;

        // left and right auxiliary arrays
        int L_sz = n; 
        int R_sz = sz - L_sz; 

        // dynamic allocation
        DataType *L = new DataType[L_sz]; 
        DataType *R = new DataType[R_sz];

        // copy elements from each half of A, respectively into L and R
        std::copy(first, first + n, L);
        std::copy(first + n, last, R);

        mergesort(L, L + L_sz, cmp);
        mergesort(R, R + R_sz, cmp); //  L + L_sz (R) belongs to the second half
        merge(L, L + L_sz, // [l_first; l_last)
            R, R + R_sz, // [r_first; r_last)
            first, cmp);
        
        // free auxiliary memory to avoid any memory leak
        delete [] L;
        delete [] R;
    }
    //}}} MERGE SORT

    //{{{ QUICK SORT
    /*!
     * Partition reorders the elements in the range [first;last) in such a way that
     * all elements **less** than the pivot appear before the pivot, and all elements
     * equal or greater than the pivot appear after the pivot.
     *
     * Any relative order among elements of the array might not be preserved.
     *
     * By **less** we mean a _strict order_ binary relation among the elements we
     * wantt to partition.
     *
     * \note We assume the pivot is a valid iterator in [first; last).
     *
     * @param first The first element in the range we want to reorder.
     * @param last Past the last element in the range we want to reorder.
     * @param cmp A comparison function that returns true if the first parameter is **less** than the second.
     * @return An iterator to the new pivot location within the range.
     */
    template<class FwrdIt, class Compare>
    FwrdIt partition(FwrdIt first, FwrdIt last, Compare cmp){
        // Let us apply the Lamuto's median-of-three pivot selection strategy
        // to avoid segfault (stack overflow) in case the array is already
        // sorted.
        FwrdIt mid = first + std::distance(first, last)/2;
        FwrdIt last_value = last - 1;
        if(cmp(*mid, *first)) std::iter_swap(mid, first);
        if(cmp(*last_value, *first)) std::iter_swap(first, last_value);
        if(cmp(*mid, *last_value)) std::iter_swap(mid, last_value);
        FwrdIt pivot = last_value;
        
        // Slow/fast approach: operating within the own range.
        FwrdIt slow = first - 1;
        FwrdIt fast = first;
        
        // Traverse range, rearranging the elements
        // Move smallest to the front region of the array.
        // Advance frontier..
        while(fast != last) {
            if(cmp(*fast, *pivot)) { 
                slow++;
                std::swap(*slow, *fast);
            }
            fast++;
        }
        // We need a final swap, so that the pivot end up in its final position
        // in the sorted array.
        std::swap(*(slow + 1), *(last - 1));
        return slow + 1;
    }
    /// Quick sort implementation.
    template<typename RandomIt, typename Compare>
    void quick(RandomIt first,RandomIt last,Compare comp){
        if(first < last) {
            RandomIt p = sa::partition(first, last, comp);
            quick(first, p, comp); 
            quick(p + 1, last, comp);
        }
    }
    //}}} QUICK SORT 

    //{{{ RADIX SORT
    /*!
     * This function implements the Radix Sorting Algorithm based on the **less significant digit** (LSD).
     * 
     * @note There is no need for a comparison function to be passed as argument.
     *
     * @param first Pointer/iterator to the beginning of the range we wish to sort.
     * @param last Pointer/iterator to the location just past the last valid value of the range we wish to sort.
     * @tparam FwrdIt A forward iterator to the range we need to sort.
     */
    template <typename FwrdIt>
    void radix(FwrdIt first, FwrdIt last){
        
        using DataType = typename std::remove_reference<decltype(*std::declval<FwrdIt>())>::type;
        
        // the number of digits of max element indicates how many times the main loop will be executed 
        size_t max_d = std::to_string(*std::max_element(first, last)).size(); 

        // one bucket for each digit from 0 to 9
        std::array<std::vector<DataType>, 10> buckets;

        // main loop; max_d times
        for(size_t i = 0; i < max_d; i++) {
            // inter loop; insert each element into its respective bucket depending on which digit position is being analyzed
            std::for_each(first, last, [&buckets, i](DataType value){ buckets[(int)(value/std::pow(10, i))%10].push_back(value); });
            // ==============================================================
            // What the for_each above does is:
            // --------------------------------------------------------------
            // Assuming value=123 and that the largest number in the collection has 4 digits.
            // 1st pass: 123/1 = 123; 123 % 10 = 3. buckets[3].push_back(123).
            // 2nd pass: 123/10 = 12; 12 % 10 = 2.  buckets[2].push_back(123).
            // 3rd pass: 123/100 = 1; 1 % 10 = 1.   buckets[1].push_back(123).
            // 4th pass: 123/1000 = 0; 0 % 10 = 0.  buckets[0].push_back(123).
            
            // copy from buckets to the original range
            FwrdIt destination = first;
            for(auto &b : buckets) {
                destination = std::copy(b.begin(), b.end(), destination);
                b.clear();
            }
        }
    }
    //}}} RADIX SORT

};
#endif // SORTING_H

