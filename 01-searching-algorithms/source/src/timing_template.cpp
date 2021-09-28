/*!
 * This is a template code to demonstrate how to measure runtime of part of your code.
 * I'm using the chrono C++ library.
 * @date September 8th, 2020.
 * @author Selan
 */

#include <iostream>
#include <chrono>
#include <vector>
#include "searching.h"

int main( void )
{
    std::vector<int> v(1000000);
    int* first = &v[0];
    int* last = &v[950000]; // change size input here
    std::chrono::duration<double> sum;
    std::chrono::duration<double> average;
    std::cout << ">>> STARTING computation that needs timing, please WAIT.... <<<\n";
    for(int i = 0; i < 10; i++) {
        auto start = std::chrono::steady_clock::now();
        //================================================================================
        int* pointer = sa::bsearchrwrapper(first, last, 1); // call the function here
        //================================================================================
        std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
        std::cout << ">>> ENDING computation that needs timing <<<\n";

        //Store the time difference between start and end
        // auto diff = end - start;
        std::chrono::duration<double> diff = end - start;
        if(i == 0) sum = diff;
        else sum += diff;
    }
    average = sum/10;
    // Milliseconds (10^-3)
    std::cout << "\t\t>>> " << std::chrono::duration <double, std::milli> (average).count()
        << " ms" << std::endl;

    /*
    // Nanoseconds (10^-9)
    std::cout << "\t\t>>> " << std::chrono::duration <double, std::nano> (diff).count()
        << " ns" << std::endl;

    // Seconds
    auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
    std::cout << "\t\t>>> " << diff_sec.count() << " s" << std::endl;
    */
    return EXIT_SUCCESS;
}
