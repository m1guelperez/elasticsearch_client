# Elasticsearch Client for C++

## About The Project

A library to make easy use of elasticsearch in C++ projects similar to the Python elasticsearch package.

## Prerequisites:

The code has only been tested on Linux so far.

To get the best results note the following:

* C++ version >= 17
* CMake version >= 3.22
* Elasticsearch version >= 7.5

## Dependencies:

* libcurl version >= 7.17.0
* simdjson 
* nlohmann/json

## How to use:

* ### Clone with submodules:
    * `git clone --recurse-submodules -j8 https://github.com/m1guelperez/elasticsearch_client.git`
* ### Install libcurl:
    * on Debian based distributions via:
  ``` shell
    sudo apt-get update && sudo apt install libcurl
  ```
    * on Arch via:
  ``` shell 
    sudo pacman -S curl 
  ```

* ### Fill your configfile like the following:
    * ```
      HOST=<HOST>
      PORT=<PORT>
      ``` 

## Recommendations:
Depending on your usage, I highly recommend you to eventually install the `nlohmann` library
for pretty printing/debugging and the `simdjson` library for faster parsing.

### Installation of nlohmann json library via cmake:

```cmake 
include(FetchContent) 
FetchContent_Declare(json 
        URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz 
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(json)  
target_link_libraries(<your_target> PRIVATE nlohmann_json::nlohmann_json)
```



### Installation of simdjson library via cmake:
  ```cmake 
include(FetchContent)
FetchContent_Declare(
        simdjson
        GIT_REPOSITORY https://github.com/simdjson/simdjson.git
        GIT_SHALLOW TRUE 
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(simdjson)
target_link_libraries(<your_target> PRIVATE simdjson)

  ```
## TODO:

* [x] Set up default curl
    * [ ] Provide more curl options
* [x] Create easy-query/raw-string interface
* [x] Add configfile support
* [ ] Add all elasticsearch request types (e.g search, update, ...)
* [ ] Response processing (extract JSON values)
    * [x] Add json parsing functionality
    * [x] Add pretty print for queries
* [ ] Make fully functional Querybuilder
    * [ ] Add all elasticsearch query parameters
* [ ] Rewrite logging

### License:

Distributed under the MIT License.