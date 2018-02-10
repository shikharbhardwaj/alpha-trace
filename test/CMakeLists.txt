# Set the executable paths
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# Add executables here
set(TEST_SOURCES test_main.cpp math_test.cpp)
add_executable(math_test test_main.cpp math_test.cpp)

target_link_libraries(math_test Catch)

# Add the executable to CTest.
add_test(NAME math_test COMMAND math_test)
