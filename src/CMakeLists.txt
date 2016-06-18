# Set the executable paths
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
# Add executables here
add_executable(alpha alpha.cpp)
add_executable(render_mesh render_mesh.cpp)
cotire(alpha)
