# Configure sources, includes and libs
# Add the include directory
include_directories(${CMAKE_BINARY_DIR}/src/include)
# Add the link directory
link_directories(${CMAKE_BINARY_DIR}/src/lib)
# Set the executable paths
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
# Add executables here
add_executable(demo demo.cxx)
