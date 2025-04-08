include(FetchContent)

function(download_7zip ver)
    set(CONT_NAME "7zip_${ver}")
    set(DOWNLOAD_URL "https://www.7-zip.org/a/7z${ver}-extra.7z")

    FetchContent_Declare(
            ${CONT_NAME}
            URL "${DOWNLOAD_URL}"
    )

    message(STATUS "fetching ${CONT_NAME}")
    FetchContent_MakeAvailable(${CONT_NAME})

    set(${CONT_NAME}_DIR "${${CONT_NAME}_SOURCE_DIR}" PARENT_SCOPE)
endfunction()
