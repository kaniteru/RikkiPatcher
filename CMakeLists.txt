cmake_minimum_required(VERSION 3.20)
project(rikkipatcher)

# ============================================================================
# C++ Standard Configuration
# ============================================================================
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================
# Build Configuration
# ============================================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============================================================================
# Dependencies (FetchContent)
# ============================================================================
include(FetchContent)

# nlohmann/json
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG        v3.12.0
        GIT_SHALLOW    TRUE
)

# webview
FetchContent_Declare(webview
        GIT_REPOSITORY https://github.com/webview/webview
        GIT_TAG        55b438dc11d0e46bc68526822380963ae9d362af
)

# Thread pool
FetchContent_Declare(threadpool
        GIT_REPOSITORY https://github.com/kaniteru/CPP-ThreadPool
        GIT_TAG        main
        GIT_SHALLOW    TRUE
)

# ANSI escapes
FetchContent_Declare(ansi_escapes
        GIT_REPOSITORY https://github.com/kaniteru/CPP-ANSIEscapes.git
        GIT_TAG        master
        GIT_SHALLOW    TRUE
)

message(STATUS "Fetching dependencies...")
FetchContent_MakeAvailable(json webview threadpool ansi_escapes)

# ============================================================================
# 7-Zip Download
# ============================================================================
set(7ZIP_VERSION "2501")
set(7ZIP_URL "https://www.7-zip.org/a/7z${7ZIP_VERSION}-extra.7z")

FetchContent_Declare(7zip_extra
        URL "${7ZIP_URL}"
)
FetchContent_MakeAvailable(7zip_extra)
set(7ZIP_DIR "${7zip_extra_SOURCE_DIR}")

# ============================================================================
# Source Files
# ============================================================================
file(GLOB_RECURSE SRC_FILES
        "${PROJECT_SOURCE_DIR}/src/**.hpp"
        "${PROJECT_SOURCE_DIR}/src/**.cpp"
)

# ============================================================================
# Executable
# ============================================================================
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(rikkipatcher ${SRC_FILES})
else()
    add_executable(rikkipatcher WIN32 ${SRC_FILES})
endif()

# ============================================================================
# Precompiled Header
# ============================================================================
target_precompile_headers(rikkipatcher PRIVATE
        "${CMAKE_SOURCE_DIR}/src/precompiled.hpp"
)

# ============================================================================
# Include Directories
# ============================================================================
target_include_directories(rikkipatcher PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
)

# ============================================================================
# Link Libraries
# ============================================================================
target_link_libraries(rikkipatcher PRIVATE
        webview::core
        nlohmann_json::nlohmann_json
        ThreadPool
        kani::ansiescapes
)

# ============================================================================
# Compile Definitions
# ============================================================================
target_compile_definitions(rikkipatcher PRIVATE
        UNICODE
        _UNICODE
        KANI_WINDOWS_FORCE_ANSI_ONLY
        #$<$<CONFIG:Debug>:RIKKI_DEBUG>
)

# ============================================================================
# Compile Options
# ============================================================================
target_compile_options(rikkipatcher PRIVATE
        /utf-8
        /W4
        /permissive-
        /Zc:preprocessor
        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:Debug>:/Od /Zi>
)

# ============================================================================
# Post-Build: Copy Resources
# ============================================================================
add_custom_command(TARGET rikkipatcher POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res/ ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}

        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${7ZIP_DIR}/ ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/7zip
)