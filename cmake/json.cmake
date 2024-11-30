include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG                 v3.11.3
)

message("fetching json")
FetchContent_MakeAvailable(json)