# Set the executable paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
# Add executables here
add_executable(rasteriser_bench rasteriser.cpp)
cotire(rasteriser_bench)
