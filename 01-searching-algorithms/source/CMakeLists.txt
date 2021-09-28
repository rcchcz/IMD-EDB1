cmake_minimum_required(VERSION 3.18)
project(SearchAlgorithms VERSION 0.1 LANGUAGES CXX )

### [1] This creates a static lib with all the searching algorihtms 
set( SEARCHING_LIB "sa" ) # sa is short for searching algorithms
add_library( ${SEARCHING_LIB} src/searching.cpp)
set_target_properties( ${SEARCHING_LIB} PROPERTIES CXX_STANDARD 11 )

### [2] The testing target
set ( TEST_NAME "all_tests")
add_subdirectory(tests)

### [3] The timing example app
# define the sources for the project
add_executable( timing
                src/searching.cpp
                src/timing_template.cpp ) # This is the runtime measuring code. 
target_include_directories( timing PRIVATE src/include)
# define C++11 standard
set_property(TARGET timing PROPERTY CXX_STANDARD 11)

### [4] The target to run the tests with 'make run_tests'
add_custom_target(
    run_tests
    COMMAND ${TEST_NAME} 
    # COMMAND ${CMAKE_BINARY_DIR}/tests/tests
    DEPENDS ${SEARCHING_LIB}
)
