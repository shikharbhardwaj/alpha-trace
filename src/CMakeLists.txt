# Configure sources, includes and libs
# Add the include directory
include_directories(${CMAKE_BINARY_DIR}/src/include)
# Add the link directory
link_directories(${CMAKE_BINARY_DIR}/src/lib)
# Set the executable paths
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
# Add executables here
add_executable(demo demo.cxx)
