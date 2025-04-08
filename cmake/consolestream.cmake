include(FetchContent)

FetchContent_Declare(
        consolestream
        GIT_REPOSITORY https://github.com/kaniteru/CPP-ConsoleStream
        GIT_TAG                 main
)

message(STATUS "fetching consolestream")
FetchContent_MakeAvailable(consolestream)