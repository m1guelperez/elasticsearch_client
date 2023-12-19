cmake_minimum_required(VERSION 3.25)
project(elastic)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(elastic
        main.cpp Client.cppm utilities/logger/local_logger.cppm utilities/querybuilder/queries.cppm
        utilities/utilFunctions.cppm utilities/configfileHandler.cppm utilities/querybuilder/searchQuery.cppm
        utilities/querybuilder/queries.cppm)

find_package(CURL REQUIRED)
pkg_check_modules(libcurl REQUIRED IMPORTED_TARGET libcurl>=7.17.0)
include(FetchContent)
FetchContent_Declare(json
        URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(json)
FetchContent_Declare(
        simdjson
        GIT_REPOSITORY https://github.com/simdjson/simdjson.git
        GIT_SHALLOW TRUE
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(simdjson)
target_link_libraries(elastic PUBLIC PkgConfig::libcurl simdjson nlohmann_json::nlohmann_json)
