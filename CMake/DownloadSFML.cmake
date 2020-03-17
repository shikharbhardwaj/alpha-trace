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
