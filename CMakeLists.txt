cmake_minimum_required(VERSION 3.22)
project(elastic)

set(CMAKE_CXX_STANDARD 17)
add_executable(elastic main.cpp Client.cpp Client.h utilities/logger/logger.cpp utilities/logger/logger.h utilities/environment.cpp utilities/environment.h utilities/querybuilder/queries.cpp utilities/querybuilder/queries.h utilities/utilFunctions.cpp utilities/utilFunctions.h utilities/configfileHandler.cpp utilities/configfileHandler.h utilities/querybuilder/searchQuery.cpp utilities/querybuilder/searchQuery.h)
set(SIMDJSON_JUST_LIBRARY ON CACHE STRING "Build just the library, nothing else." FORCE)
add_subdirectory(simdjson EXCLUDE_FROM_ALL)
find_package( CURL REQUIRED )
pkg_check_modules(libcurl REQUIRED IMPORTED_TARGET libcurl>=7.17.0)
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(json)

target_link_libraries(elastic PUBLIC PkgConfig::libcurl simdjson nlohmann_json::nlohmann_json)
