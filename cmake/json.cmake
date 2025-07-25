include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG        v3.12.0
)

message(STATUS "fetching json")
FetchContent_MakeAvailable(json)