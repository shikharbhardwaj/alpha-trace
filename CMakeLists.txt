cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0011 NEW)
cmake_policy(SET CMP0058 NEW)

# For cotire
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire)

project("alpha-trace" VERSION 0.0.1 LANGUAGES CXX)

# We need to test things.
include(CTest)
enable_testing()

# Dependencies

# SFML
include(DownloadSFML)
find_package(SFML 2 COMPONENTS graphics window system)
include_directories("${SFML_DOWNLOAD_DIR}/include")

# cxxopts
include(Downloadcxxopts)
include_directories("${cxxopts_DOWNLOAD_DIR}/include")

# spdlog
include(Downloadspdlog)
include_directories("${spdlog_DOWNLOAD_DIR}/include")

# Set flags according to the toolchain.

if (WIN32)
  # We are compling on Windows.
  if (MSVC)
    set(project_flags "/W4 /WX /EHs /openmp /Ox")
    set(debug_flags "/Oy-")
  endif()
elseif(UNIX)
  # Yay! Everything is sane.
  set(base_flags "-Wall -Werror -Wextra -std=c++14 -pthread -fopenmp \
-fno-rtti -fno-omit-frame-pointer")
  set(optimization_flags "-O3")

  set(release_flags "${base_flags} ${optimization_flags}")
  set(debug_flags "${base_flags} -g")
endif()

# Coerce to lower for comparision.
string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)

if (${CMAKE_BUILD_TYPE} STREQUAL "debug")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${debug_flags}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${debug_flags}")
else()
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${release_flags}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${release_flags}")
endif()

message("Set C flags to ${CMAKE_C_FLAGS}")
message("Set CXX flags to ${CMAKE_CXX_FLAGS}")

# Configure sources, includes and libs
# Add the include directory
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/include)

# Add the link directories
link_directories(${PROJECT_SOURCE_DIR}/ib)
link_directories(${PROJECT_SOURCE_DIR}/thirdparty/lib)

# Add the source directories
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
add_subdirectory(${PROJECT_SOURCE_DIR}/spike/code)
add_subdirectory(${PROJECT_SOURCE_DIR}/spike/bench)
add_subdirectory(${PROJECT_SOURCE_DIR}/spike/test)
add_subdirectory(${PROJECT_SOURCE_DIR}/spike/models)

# Configure Catch.
set(CATCH_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/thirdparty/include/catch)
add_library(Catch INTERFACE)

target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
