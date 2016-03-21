cmake_minimum_required(VERSION 2.6)

project("alpha-trace")


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror -std=c++14")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")
# Configure sources, includes and libs
# Add the include directory
include_directories(${PROJECT_SOURCE_DIR}/src/include)
# Add the link directory
link_directories(${PROJECT_SOURCE_DIR}/src/lib)

# Add the source directory
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

