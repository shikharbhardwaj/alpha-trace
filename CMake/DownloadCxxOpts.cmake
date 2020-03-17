# Download cxxopts if it does not exist

set(cxxopts_DOWNLOAD_URL "https://codeload.github.com/jarro2783/cxxopts/tar.gz/v2.2.0")

# Check for existence
file (GLOB cxxopts_DIRECTORIES "${PROJECT_SOURCE_DIR}/thirdparty/cxxopts-[0-9+].[0-9+].[0-9+]")
list(LENGTH cxxopts_DIRECTORIES cxxopts_DIRECTORIES_LEN)

if (${cxxopts_DIRECTORIES_LEN} EQUAL 1)
	list(GET cxxopts_DIRECTORIES 0 cxxopts_DOWNLOAD_DIR)
else()
	# Download suitable version from github.
    file(DOWNLOAD ${cxxopts_DOWNLOAD_URL}
        "${PROJECT_SOURCE_DIR}/thirdparty/cxxopts.tar.gz"
        STATUS cxxopts_DOWNLOAD_STATUS_LIST LOG cxxopts_DOWNLOAD_LOG
        SHOW_PROGRESS)

    list(GET cxxopts_DOWNLOAD_STATUS_LIST 0 cxxopts_DOWNLOAD_STATUS)

    if (cxxopts_DOWNLOAD_STATUS EQUAL 0)
        execute_process(COMMAND ${CMAKE_COMMAND} -E
            tar xvf "${PROJECT_SOURCE_DIR}/thirdparty/cxxopts.tar.gz"
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/thirdparty/")
    endif()

	# Check again
	file (GLOB cxxopts_DIRECTORIES "${PROJECT_SOURCE_DIR}/thirdparty/cxxopts-[0-9+].[0-9+].[0-9+]")
	list(LENGTH cxxopts_DIRECTORIES cxxopts_DIRECTORIES_LEN)
	if (NOT ${cxxopts_DIRECTORIES_LEN} EQUAL 1)
		message(FATAL_ERROR "Unable to download dependency: cxxopts")
	endif()

	list(GET cxxopts_DIRECTORIES 0 cxxopts_DOWNLOAD_DIR)
endif()

set(cxxopts_DIR "${cxxopts_DOWNLOAD_DIR}")
