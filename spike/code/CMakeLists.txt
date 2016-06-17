# Set the executable paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
# Add executables here
add_executable(rasterisation rasterisation.cpp)
add_executable(antialiasing antialiasing.cpp)
add_executable(zbuf_dump zbuf_dump.cpp)
add_executable(mesh mesh.cpp)
add_executable(cube cube.cpp)
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)
