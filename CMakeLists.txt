cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0011 NEW)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cfg")
include(cotire)
project("alpha-trace")


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
set(warnings "-Wall -Werror -Wextra -std=c++11 -pthread -march=native")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
find_package(GLUT)
find_package(OpenGL)
find_library(GOOGLE_BENCHMARK NAME libbenchmark 
    HINTS "/usr/local/lib"
    )
# Configure sources, includes and libs
# Add the include directory
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)
# Add the link directory
link_directories(${PROJECT_SOURCE_DIR}/lib)

# Add the source directory
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
add_subdirectory(${PROJECT_SOURCE_DIR}/spike/code)
add_subdirectory(${PROJECT_SOURCE_DIR}/spike/bench)
