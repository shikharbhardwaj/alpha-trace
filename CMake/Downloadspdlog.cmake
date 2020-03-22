# Download spdlog if it does not exist

set(spdlog_DOWNLOAD_URL "https://codeload.github.com/gabime/spdlog/tar.gz/v1.5.0")

# Check for existence
file (GLOB spdlog_DIRECTORIES "${PROJECT_SOURCE_DIR}/thirdparty/spdlog-[0-9+].[0-9+].[0-9+]")
list(LENGTH spdlog_DIRECTORIES spdlog_DIRECTORIES_LEN)

if (${spdlog_DIRECTORIES_LEN} EQUAL 1)
	list(GET spdlog_DIRECTORIES 0 spdlog_DOWNLOAD_DIR)
else()
	# Download suitable version from github.
    file(DOWNLOAD ${spdlog_DOWNLOAD_URL}
        "${PROJECT_SOURCE_DIR}/thirdparty/spdlog.tar.gz"
        STATUS spdlog_DOWNLOAD_STATUS_LIST LOG spdlog_DOWNLOAD_LOG
        SHOW_PROGRESS)

    list(GET spdlog_DOWNLOAD_STATUS_LIST 0 spdlog_DOWNLOAD_STATUS)

    if (spdlog_DOWNLOAD_STATUS EQUAL 0)
        execute_process(COMMAND ${CMAKE_COMMAND} -E
            tar xvf "${PROJECT_SOURCE_DIR}/thirdparty/spdlog.tar.gz"
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/thirdparty/")
    endif()

	# Check again
	file (GLOB spdlog_DIRECTORIES "${PROJECT_SOURCE_DIR}/thirdparty/spdlog-[0-9+].[0-9+].[0-9+]")
	list(LENGTH spdlog_DIRECTORIES spdlog_DIRECTORIES_LEN)
	if (NOT ${spdlog_DIRECTORIES_LEN} EQUAL 1)
		message(FATAL_ERROR "Unable to download dependency: spdlog")
	endif()

	list(GET spdlog_DIRECTORIES 0 spdlog_DOWNLOAD_DIR)
endif()

# Build spdlog
add_subdirectory("${spdlog_DOWNLOAD_DIR}")

set(spdlog_DIR "${spdlog_DOWNLOAD_DIR}")
