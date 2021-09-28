/*!
 * @file main.cpp
 * Benchmarking suit to compare sorting algorithms under various situations.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include <cassert>
#include <algorithm>
#include <functional>
using std::function;
using std::cout;
#include "lib/sorting.h"
#include <numeric>
#include <random>
#include <time.h>  
#include <cstdlib> 

//=== ALIASES

/// Data type we are working with.
using value_type = long int;
/// Size type.
using size_type = long int;
/// Alias for duration measure.
using duration_t = std::chrono::duration<double, std::milli>;

struct RunningOpt{
    size_t min_sample_sz{100};   //!< Default 10^5. 100
    size_t max_sample_sz{100000}; //!< The max sample size. 100000 
    int n_samples{25};            //!< The number of samples to collect.
    /// Returns the sample size step, based on the [min,max] sample sizes and # of samples.
    size_type sample_step(void){
        return static_cast<float>(max_sample_sz-min_sample_sz)/(n_samples-1);
    }
};

//=== CONSTANT DEFINITIONS.

/// Number of runs we need to calculate the average runtime for a single algorithm.
constexpr short N_RUNS = 5;

//Seed used to random the numbers when creating the vector
const int SEED = rand()%100;

//Path where you want to save the DATASET files
const string PATH = "data/";

//Last digits of the DATASET file
const string FILE_FORMAT = ".txt";

/// Comparison function for the test experiment.
constexpr bool compare( const int&a, const int &b ){
    return ( a < b );
}

//=== AUXILIAR FUNCTIONS.

/**
 * @brief Recieves a size and the type of the vector and return the vector
 * 
 * @param i Determine the type of the vector (ascending,descending, 25% order....,all random)
 * @param size Determine the vector size
 * @return std::vector<int> 
 */
std::vector<int> set_vector(size_t i, size_type size){
    std::vector<int> set(size);
    std::iota(set.begin(), set.end(), 1); // Fill with 0, 1, ..., 99, 100, .....
    switch (i){
        case 0: //Ascending order
            return set;
        case 1: //Descending order
            std::reverse(set.begin(),set.end());
            return set;
        case 2: //75% random
            std::shuffle(set.begin() + size/4, set.end(),std::default_random_engine(SEED));
            return set;
        case 3: //50% random
            std::shuffle(set.begin() + (2*size/4), set.end(),std::default_random_engine(SEED));
            return set;
        case 4: //25% random
            std::shuffle(set.begin() + (3*size/4), set.end(),std::default_random_engine(SEED));
            return set;
        case 5: //All random
            std::shuffle(set.begin(), set.end(),std::default_random_engine(SEED));
            return set;
        }
        return set;
    }

/**
 * @brief This function recieves an array and the identifier of the algorithm and return the duration to run it, in milliseconds
 * @param first First element of the array, the interval is [first,last)
 * @param last Next element after the last element, the interval is [first,last)
 * @param cmp This function is used for compare the valeus of the vector
 * @param sorting_type determine what sorting algorithm will be used (inserction sort, selection sort, bubble sort, ..., radix sort)
 * @return Return the duration of an specific sorting algorithm using a vector
 */
template< typename RandomIt, typename Compare >
duration_t time_algorithm(RandomIt first, RandomIt last, Compare cmp, size_t sorting_type){
    duration_t diff;
    std::chrono::time_point<std::chrono::steady_clock> end,start;
    switch (sorting_type){
    case 0:
        start = std::chrono::steady_clock::now();
        sa::insertion(first, last,cmp);
        end = std::chrono::steady_clock::now();
        diff = end - start;
        return diff; 
    case 1:
        start = std::chrono::steady_clock::now();
        sa::selection(first, last,cmp);
        end = std::chrono::steady_clock::now();
        diff = end - start;
        return diff;
    case 2:
        start = std::chrono::steady_clock::now();
        sa::bubble(first, last,cmp);
        end = std::chrono::steady_clock::now();
        diff = end - start;
        return diff; 
    case 3:
        start = std::chrono::steady_clock::now();
        sa::shell(first, last,cmp);
        end = std::chrono::steady_clock::now();
        diff = end - start;
        return diff;
    case 4:
        start = std::chrono::steady_clock::now();
        sa::quick(first, last,cmp);
        end = std::chrono::steady_clock::now();
        diff = end - start;
        return diff; 
    case 5:
        start = std::chrono::steady_clock::now();
        sa::mergesort(first, last,cmp);
        end = std::chrono::steady_clock::now();
        diff = end - start;
        return diff;
    case 6:
        start = std::chrono::steady_clock::now();
        sa::radix(first, last);
        end = std::chrono::steady_clock::now();
        diff = end - start;
        return diff;
    }   
    start = std::chrono::steady_clock::now();
    end = std::chrono::steady_clock::now();
    diff = end - start;
    return diff;   
}

//=== The main function, entry point.
int main()
{
    std::chrono::time_point<std::chrono::steady_clock> end,start; //REMOVE
    duration_t coisa;
    duration_t time_mean;
    RunningOpt info;
    //Names of the dataset columns
    std::vector<std::string> names {"INSERTION", "SELECTION", "BUBBLE", "SHELL","QUICK","MERGE","RADIX"};
    std::vector<std::string> files {"ASCENDING_ORDER", "DESCENDING_ORDER", "75_RANDOM", "50_RANDOM", "25_RANDOM" , "ALL_RANDOM"};
    
    //Loop to each type of vector organization
    for(size_t ifile = 0; ifile < files.size(); ifile++){
        std::ofstream DATASET(PATH+files[ifile]+ FILE_FORMAT); //INITIALIZE FILE
        DATASET << "SIZE" ;
        //Print columns names
        for(size_t i =0 ;i < names.size(); i++){
        DATASET << "," << names[i] ;
        }
        DATASET << std::endl;

        //Copy of last work
            //This for loop pass step by step
            for(size_type size = info.min_sample_sz; 
                        size <= info.max_sample_sz;
                        size += info.sample_step()){
                std::vector<int> arr_test = set_vector(ifile, size); 
                vector<int> copy = arr_test; 
                cout << " Type:["<< files[ifile] << "] Size:[" << size << "/" <<info.max_sample_sz << "] Algorithm(ms): ";
                //Pass by diferents algorithms
                for(size_t algo_type =0; algo_type < names.size(); algo_type++){
                    cout << "["  <<names[algo_type] << ","; 
                    //Repeat the same vector and calculate the mean
                    time_mean = std::chrono::milliseconds::zero();
                    DATASET << size; 
                    for(int ct_run = 1; ct_run <= N_RUNS; ct_run++){
                        duration_t diff = time_algorithm(copy.begin(), copy.end(),compare,algo_type);
                        time_mean = time_mean + (diff - time_mean)/ct_run;    
                        copy = arr_test;
                    }
                    DATASET <<  "," << time_mean.count();  
                    cout << time_mean.count() << "]"; 
                }
                cout << "]\n";
                DATASET << std::endl;
            }
            DATASET.close();
    }
}




