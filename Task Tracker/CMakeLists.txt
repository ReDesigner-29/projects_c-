cmake_minimum_required(VERSION 3.20)

project(QtClionProject)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)

FetchContent_MakeAvailable(nlohmann_json)

add_executable(QtClionProject main.cpp)

target_link_libraries(QtClionProject PRIVATE nlohmann_json::nlohmann_json)