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
# Check if binaries exist
file (GLOB SFML_DIRECTORIES "${PROJECT_SOURCE_DIR}/thirdparty/SFML-[0-9+].[0-9+].[0-9+]")
list(LENGTH SFML_DIRECTORIES SFML_DIRECTORIES_LEN)

if (${SFML_DIRECTORIES_LEN} EQUAL 1)
	list(GET SFML_DIRECTORIES 0 SFML_DOWNLOAD_DIR)
else()
	# Download suitable version from github.
	if(${MSVC} AND ${MSVC_VERSION} GREATER_EQUAL 1910)
		if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
			message(STATUS "${PROJECT_SOURCE_DIR}/thirdparty/SFML.tar.gz")
			file(DOWNLOAD https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-windows-vc15-32-bit.zip
				"${PROJECT_SOURCE_DIR}/thirdparty/SFML.tar.gz"
				STATUS SFML_DOWNLOAD_STATUS_LIST LOG SFML_DOWNLOAD_LOG
				SHOW_PROGRESS)
        else()
            file(DOWNLOAD https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-windows-vc15-64-bit.zip
                "${PROJECT_SOURCE_DIR}/thirdparty/SFML.tar.gz"
                STATUS SFML_DOWNLOAD_STATUS_LIST LOG SFML_DOWNLOAD_LOG
				SHOW_PROGRESS)
		endif()
	elseif (UNIX)
        file(DOWNLOAD https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-linux-gcc-64-bit.tar.gz
            "${PROJECT_SOURCE_DIR}/thirdparty/SFML.tar.gz"
            STATUS SFML_DOWNLOAD_STATUS_LIST LOG SFML_DOWNLOAD_LOG
            SHOW_PROGRESS)
    else()
        MESSAGE(FATAL_ERROR "Cannot find suitable SFML to download.")
    endif()
    list(GET SFML_DOWNLOAD_STATUS_LIST 0 SFML_DOWNLOAD_STATUS)
    if (SFML_DOWNLOAD_STATUS EQUAL 0)
        execute_process(COMMAND ${CMAKE_COMMAND} -E
            tar xvf "${PROJECT_SOURCE_DIR}/thirdparty/SFML.tar.gz"
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/thirdparty/")
    endif()

	# Check again
	file (GLOB SFML_DIRECTORIES "${PROJECT_SOURCE_DIR}/thirdparty/SFML-[0-9+].[0-9+].[0-9+]")
	list(LENGTH SFML_DIRECTORIES SFML_DIRECTORIES_LEN)
	if (NOT ${SFML_DIRECTORIES_LEN} EQUAL 1)
		message(FATAL_ERROR "Unable to download dependency: SFML")
	endif()

	list(GET SFML_DIRECTORIES 0 SFML_DOWNLOAD_DIR)
endif()

set(SFML_DIR "${SFML_DOWNLOAD_DIR}/lib/cmake/SFML")
find_package(SFML 2 COMPONENTS graphics window system)
include_directories("${SFML_DOWNLOAD_DIR}/include")

# Set flags according to the toolchain.
if (WIN32)
  # We are compling on Windows.
  if (MSVC)
    set(project_flags "/W4 /WX /EHs /openmp /Ox")
    set(debug_flags "/Oy-")
  endif()
elseif(UNIX)
  # Yay! Everything is sane.
  set(project_flags "-Wall -Werror -Wextra -std=c++14 -pthread -fopenmp -O3")
  set(debug_flags "-fno-rtti -fno-omit-frame-pointer -g")
endif()

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${project_flags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${project_flags}")


# if (${CMAKE_RELEASE_TYPE} STREQUAL "DEBUG")
# set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${debug_flags}")
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${debug_flags}")
# endif()

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

# Configure Catch.
set(CATCH_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/thirdparty/include/catch)
add_library(Catch INTERFACE)

target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
