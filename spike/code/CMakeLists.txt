# Set the executable paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
# Add executables here
add_executable(canvas_cords canvas_cords.cpp)
add_executable(pinhole pinhole.cpp)
add_executable(rasterisation rasterisation.cpp)
