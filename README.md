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
* simdjson as `git submodule`

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

## TODO:

* [x] Set up default curl
    * [ ] Provide more curl options
* [x] Create easy-query/raw-string interface
* [x] Add configfile support
* [ ] Add all elasticsearch request types (e.g search, update, ...)
* [ ] Response processing (extract JSON values)
    * [x] Add json parsing functionality
* [ ] Make fully functional Querybuilder
    * [ ] Add all elasticsearch query parameters
*[ ] Rewrite logging
* [ ] Multithreading

### License:

Distributed under the MIT License.