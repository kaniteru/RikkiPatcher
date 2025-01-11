cmake_minimum_required(VERSION 3.29)
project(RikkiPatcher)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")

include(json)
include(webview)
include(7zip)

set(7ZIP_VER "2409")
download_7zip("${7ZIP_VER}")
set(7ZIP_DIR ${7zip_${7ZIP_VER}_DIR})

file(GLOB_RECURSE SRC_FILES
        "${PROJECT_SOURCE_DIR}/src/**.hpp"
        "${PROJECT_SOURCE_DIR}/src/**.cpp"
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_executable(RikkiPatcher "${SRC_FILES}")
else()
    add_executable(RikkiPatcher WIN32 "${SRC_FILES}")
endif()

target_precompile_headers(RikkiPatcher
        PRIVATE "${PROJECT_SOURCE_DIR}/src/precompiled.hpp"
)

target_include_directories(RikkiPatcher
        PRIVATE "${PROJECT_SOURCE_DIR}/src"
        PRIVATE "${json_SOURCE_DIR}/single_include"
)

target_link_libraries(RikkiPatcher
        PRIVATE webview::core
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /utf-8")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

add_definitions("-DUNICODE" "-D_UNICODE")

add_custom_command(TARGET RikkiPatcher POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res/ ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}

        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${7ZIP_DIR}/ ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/7zip
)
