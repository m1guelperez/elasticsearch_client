//
// Created by miguel on 6/7/22.
//

#pragma once

#include <string>

/**
 * This will be the Querybuilder similar to the Python elasticsearch_dsl package
 */
class QueryBuilder {
    std::string currentQuery;
public:
    QueryBuilder match(const std::string &key, const std::string &value);

    QueryBuilder wildcard();

    std::string getCurrentQuery();

    void resetQuery();
};
