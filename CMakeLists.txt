cmake_minimum_required(VERSION 3.22)
project(elastic)

set(CMAKE_CXX_STANDARD 17)
add_executable(elastic main.cpp queries.cpp queries.h logger.cpp logger.h)
find_package( CURL REQUIRED )
pkg_check_modules(libcurl REQUIRED IMPORTED_TARGET libcurl>=7.17.0)
target_link_libraries(elastic PUBLIC PkgConfig::libcurl)
