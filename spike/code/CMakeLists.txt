# Set the executable paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# Add executables here
# add_executable(rasterisation rasterisation.cpp)
# add_executable(antialiasing antialiasing.cpp)
# add_executable(zbuf_dump zbuf_dump.cpp)
# add_executable(mesh mesh.cpp)
# add_executable(cow_pers cow_pers.cpp)
# add_executable(ray_trace ray_trace.cpp)
# add_executable(sfml_test sfml_test.cpp)
# add_executable(spdlog_test spdlog_test.cpp)

# target_link_libraries(sfml_test sfml-graphics)
# target_link_libraries(spdlog_test PRIVATE spdlog::spdlog)

set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)
