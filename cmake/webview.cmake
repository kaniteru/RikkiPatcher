include(FetchContent)

FetchContent_Declare(
        webview
        GIT_REPOSITORY https://github.com/webview/webview
        GIT_TAG                 0.12.0
)

message("fetching webview")
FetchContent_MakeAvailable(webview)