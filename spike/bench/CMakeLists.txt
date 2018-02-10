# Set the executable paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
# Add executables here
add_executable(rasteriser_bench rasteriser.cpp)
add_executable(antialiasing_bench antialiasing.cpp)
add_executable(math_bench math_bench.cpp)

# Target specific stuff here
target_link_libraries(rasteriser_bench benchmark)
target_link_libraries(math_bench benchmark)
