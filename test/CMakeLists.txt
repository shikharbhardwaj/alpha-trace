# Set the executable paths
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# Add executables here
# set(TEST_SOURCES test_main.cpp math_test.cpp)
add_executable(math_test test_main.cpp math_test.cpp)
add_executable(buffer_test test_main.cpp buffer_test.cpp)
add_executable(mesh_renderer_test test_main.cpp mesh_renderer_test.cpp)
add_executable(spdlog_test test_main.cpp spdlog_test.cpp)
add_executable(trace_test test_main.cpp trace_test.cpp)


target_link_libraries(math_test Catch spdlog::spdlog)
target_link_libraries(buffer_test Catch spdlog::spdlog)
target_link_libraries(mesh_renderer_test Catch spdlog::spdlog)
target_link_libraries(spdlog_test Catch spdlog::spdlog)
target_link_libraries(trace_test Catch spdlog::spdlog)

# Add the executable to CTest.
add_test(NAME math_test COMMAND math_test)
add_test(NAME buffer_test COMMAND buffer_test)
add_test(NAME mesh_renderer_test COMMAND mesh_renderer_test WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
add_test(NAME spdlog_test COMMAND spdlog_test)
add_test(NAME trace_test COMMAND trace_test WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
