//
// Created by miguel on 12/19/22.
//
#pragma once
#include <string>

class Search {
private:
    std::string query = "{\n \"query\": {\n ";
    int queryDepth = 2;
public:
    std::string getCurrentQuery();

    Search* matchQuery(const std::string& field, const std::string& value);
    Search* matchQuery(const std::string& field, int value);
    std::string buildQuery();
};
