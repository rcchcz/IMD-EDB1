/*!
 * \file searching.cpp
 * Binary search, Linear search, Upper bound, lower bound implementation for an array of integers.
 * \author Selan R. dos Santos
 * \date June 17th, 2021.
 */

#include "searching.h"

namespace sa {

    /*!
     * Performs a linear search for target-value in [first;last) and returns a pointer
       to the location of value in the range [first,last], or a pointer to last if no
       such element is found.
     * @param first Pointer to the begining of the data range.
     * @param last Pointer just past the last element of the data range.
     * @param value The value we are looking for.
     * @return a pointer to the location of target-value in the range [first, last)
     *     or a pointer to last if target is not found.
     */
    value_type * lsearch( value_type * first, value_type * last, value_type value )
    {
        while(first != last) {
            if(*(first) == value) return first;
                else first++;
        }
        // if the target is not within the range passed to the function
        // immediately after the last while loop, at this time first points to last
        return first;
    }

    /*!
     * Performs a binary search for target-value in [first;last) and returns a pointer
        to the location of value in the range [first,last], or a pointer to last if no
        such element is found.
     * @note The range **must** be sorted.
     * @param first Pointer to the begining of the data range.
     * @param last Pointer just past the last element of the data range.
     * @param value The value we are looking for.
     * @return a pointer to the location of target-value in the range [first, last)
     *     or a pointer to last if target is not found.
     */
    value_type * bsearch( value_type * first, value_type * last, value_type value )
    {
        int *saved_last = last;
        while(first != last) {
            // pointer to the middle
            int * mid = first + (last - first)/2;
            // the middle element is the target
            if(*mid == value) return mid;
            // middle element is greater than target, search in left subarray
            else if (*mid > value) last = mid;
            // middle element is less than target, search in right subarray
            else first = ++mid;
        }
        // if the target is not within the range passed to the function
        return saved_last;
    }

    /*!
     * A wrapper function that holds the position of last and calls the actual
       recursive binary search (bsearchr).
     * @note The range must be sorted.
     * @param first Pointer to the begining of the data range.
     * @param last Pointer just past the last element of the data range.
     * @param value The value we are looking for.
     * @return a pointer to the location of target-value in the range [first, last)
     *     or a null pointer if target is not found.
     */
    value_type * bsearchrwrapper( value_type * first, value_type * last, value_type value ) {
        int* pos = bsearchr(first, last, value);
        if(pos == nullptr) return last;
        else return pos;
    }

    /*!
     * Performs a recursive binary search for target-value in [first;last) and returns a pointer
       to the location of value in the range [first,last], or a pointer to last if no such
       element is found.
     * @note The range must be sorted.
     * @param first Pointer to the begining of the data range.
     * @param last Pointer just past the last element of the data range.
     * @param value The value we are looking for.
     * @return a pointer to the location of target-value in the range [first, last)
     *     or a pointer to last if target is not found.
     */
    value_type * bsearchr( value_type * first, value_type * last, value_type value )
    {
        if(first != last) {
            // pointer to the middle
            int* mid = first + (last - first)/2;
            // the middle element is the target
            if(*mid == value) return mid;
            // middle element is greater than target, search in left subarray
            else if(*mid > value) return bsearchr(first, mid, value);
            // middle element is less than target, search in right subarray
            else return bsearchr(++mid, last, value);
        // if the target is not within the range passed to the function
        } else return nullptr;         
    }

    /*!
     * Returns a pointer to the first element in the range [first, last) that is not less 
       than (i.e. greater or equal to) value, or a pointer to last if no such element is found.
     * @note The range must be sorted.
     * @param first Pointer to the begining of the data range.
     * @param last Pointer just past the last element of the data range.
     * @param value The value we are looking for.
     * @return a pointer to the location of the first element that is not less than 'value'
     *    in the range [first, last) or a pointer to last if there is no such element in
     *    this range.
     */
    value_type * lbound( value_type * first, value_type * last, value_type value )
    {
        // linear search for the first element that is not less than the target
        // search for the first element greater than or equal to the target
        while(first != last) {
            if(*first >= value) return first;
            else first++;
        }
        // if the target is not within the range passed to the function
        return last;
    }

    /*!
     * Returns a pointer to the first element in the range [first, last) that is greater
       than value, or a pointer to last if no such element is found.
     * @note The range must be sorted.
     * @param first Pointer to the begining of the data range.
     * @param last Pointer just past the last element of the data range.
     * @param value The value we are looking for.
     * @return a pointer within the range [first, last].
     */
    value_type * ubound( value_type * first, value_type * last, value_type value )
    {
        // linear search for the first element that is greater than the target
        while(first != last) {
            if(*first > value) return first;
            else first++;
        }
        // if the target is not within the range passed to the function
        return last;
    }
}