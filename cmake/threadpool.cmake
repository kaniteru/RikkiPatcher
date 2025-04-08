include(FetchContent)

FetchContent_Declare(
        threadpool
        GIT_REPOSITORY https://github.com/kaniteru/CPP-ThreadPool
        GIT_TAG                 main
)

message(STATUS "fetching threadpool")
FetchContent_MakeAvailable(threadpool)