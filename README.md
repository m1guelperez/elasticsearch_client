# Elasticsearch Client

A simple Elasticsearch client, to make use of queries in C++ code.

## Prerequisites:

To get the best results note the following:

* C++ version >= 17
* CMake version >= 3.22
* Elasticsearch version >= 7.5

## Dependencies:

* libcurl version >= 7.17.0
* simdjson as `git submodule`

TODO:

* [x] Set up default curl
    * [ ] Provide more curl options
* [x] Create easy-query/raw-string interface
* [ ] Add all elasticsearch request types (e.g search, update, ...)
* [ ] Response processing (extract JSON values)
  * [x] Add json parsing functionality
* [ ] Make fully functional Querybuilder
    * [ ] Add all elasticsearch query parameters
* [ ] Multithreading