cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0011 NEW)

# For cotire
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire)


project("alpha-trace")

# We need to test things.
include(CTest)
enable_testing()

# Set flags according to the toolchain.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Werror -Wextra -std=c++14 -pthread")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(bench_flags "-O3 -fno-rtti -fno-omit-frame-pointer -g")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(bench_flags "/Oy- -DEBUG")
endif()

set(bench_flags "-O3 -fno-rtti -fno-omit-frame-pointer -g")

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${bench_flags}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

if ("${CMAKE_RELEASE_TYPE}" STREQUAL "DEBUG")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${bench_flags} -DALPHA_DEBUG")
endif()


# Configure sources, includes and libs
# Add the include directory
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/include)

# Add the link directory
link_directories(${PROJECT_SOURCE_DIR}/ib)
link_directories(${PROJECT_SOURCE_DIR}/thirdparty/lib)

# Add the source directory
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
add_subdirectory(${PROJECT_SOURCE_DIR}/spike/code)
add_subdirectory(${PROJECT_SOURCE_DIR}/spike/bench)
add_subdirectory(${PROJECT_SOURCE_DIR}/spike/test)

# Configure Catch.
set(CATCH_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/thirdparty/include/catch)
add_library(Catch INTERFACE)

target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
