# Set the executable paths
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# Add executables here
# set(TEST_SOURCES test_main.cpp math_test.cpp)
add_executable(math_test test_main.cpp math_test.cpp)
add_executable(buffer_test test_main.cpp buffer_test.cpp)

target_link_libraries(math_test Catch)
target_link_libraries(buffer_test Catch)

# Add the executable to CTest.
add_test(NAME math_test COMMAND math_test)
add_test(NAME buffer_test COMMAND buffer_test)
