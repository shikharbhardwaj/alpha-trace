cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0011 NEW)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cfg")
include(cotire)
project("alpha-trace")


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Werror -Wextra -std=c++14 -pthread")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

set(bench_flags "-O3 -fno-exceptions -fno-rtti -fno-omit-frame-pointer -g")

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${bench_flags}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
# Configure sources, includes and libs
# Add the include directory
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/include)
# Add the link directory
link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(${PROJECT_SOURCE_DIR}/thirdparty/lib)

# Add the source directory
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
add_subdirectory(${PROJECT_SOURCE_DIR}/spike/code)
add_subdirectory(${PROJECT_SOURCE_DIR}/spike/bench)
