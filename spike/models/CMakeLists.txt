# Set the executable paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

configure_file(cube.raw ${PROJECT_BINARY_DIR}/cube.raw COPYONLY)
configure_file(cube_vert.raw ${PROJECT_BINARY_DIR}/cube_vert.raw COPYONLY)
configure_file(cow_vert.raw ${PROJECT_BINARY_DIR}/cow_vert.raw COPYONLY)
configure_file(mod_cube.raw ${PROJECT_BINARY_DIR}/mod_cube.raw COPYONLY)
configure_file(axis.raw ${PROJECT_BINARY_DIR}/axis.raw COPYONLY)
configure_file(boat.raw ${PROJECT_BINARY_DIR}/boat.raw COPYONLY)
configure_file(camera_settings.cfg ${PROJECT_BINARY_DIR}/camera_settings.cfg
        COPYONLY)

set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)
