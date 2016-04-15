# Set the executable paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
# Add executables here
add_executable(projection projection.cpp)
add_executable(local_world local_world.cpp)
