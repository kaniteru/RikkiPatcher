include(FetchContent)

FetchContent_Declare(
        webview
        GIT_REPOSITORY https://github.com/webview/webview
        GIT_TAG        f9cbb69abe5d875bb7c4bafe8329340462ad1ca9
)

message(STATUS "fetching webview")
FetchContent_MakeAvailable(webview)