cmake_minimum_required(VERSION 3.5)
project (HashTable VERSION 1.0.0 LANGUAGES CXX )

#=== FINDING PACKAGES ===#

# Locate GTest package (library)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#=== Test target ===

include_directories( include )
add_executable(run_tests test/main.cpp
                         driver/account.cpp )

# Link with the google test libraries.
target_link_libraries(run_tests PRIVATE ${GTEST_LIBRARIES} PRIVATE pthread )
target_compile_features(run_tests PUBLIC cxx_std_11)

#=== Driver target ===

include_directories( driver )
add_executable(driver_hash driver/account.cpp
                           driver/driver_ht.cpp )
target_compile_features(driver_hash PUBLIC cxx_std_11)


set(CMAKE_CXX_FLAGS "-fsanitize=address") 