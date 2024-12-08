include(FetchContent)

FetchContent_Declare(
        sha
        GIT_REPOSITORY https://github.com/kaniteru/SHA.git
        GIT_TAG                 master
)

message("fetching sha")
FetchContent_MakeAvailable(sha)