# Using TestManager Library
# [1] Compile the TestManagere first into a lib.
set( TEST_LIB "TM")
add_library( ${TEST_LIB} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/include/tm/test_manager.cpp )
target_include_directories( ${TEST_LIB} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/tm )
set_target_properties( ${TEST_LIB} PROPERTIES CXX_STANDARD 11 )

# [2] Setup the executable that will run the tests.
add_executable( ${TEST_DRIVER} main.cpp )
target_include_directories( ${TEST_DRIVER} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties( ${TEST_DRIVER} PROPERTIES CXX_STANDARD 11 )
# if necessary, add any other test source that exists.
# target_sources( ${TEST_DRIVER} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/test_01.cpp" )
# Link tests with the TestManager lib.
target_link_libraries( ${TEST_DRIVER} PRIVATE ${TEST_LIB} )
