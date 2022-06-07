//
// Created by miguel on 6/7/22.
//

#pragma once

#include <string>

class QueryBuilder {
    std::string currentQuery;
public:
    QueryBuilder match(std::string key, std::string value);

    QueryBuilder wildcard();

    std::string getCurrentQuery();

    void resetQuery();
};
