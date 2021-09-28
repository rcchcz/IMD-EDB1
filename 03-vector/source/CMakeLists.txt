cmake_minimum_required(VERSION 3.5)
project ( Vector VERSION 1.0 LANGUAGES CXX )

# #=== Test target ===
set ( TEST_DRIVER "all_tests")
add_subdirectory(tests)

# This custom target runs the tests.
add_custom_target(
    run_tests
    COMMAND ${TEST_DRIVER} 2> /dev/null 
    DEPENDS ${LIB_NAME}
)
