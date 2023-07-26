//
// Created by miguel on 6/7/22.
//

#pragma once

#include <string>
#include <memory>
#include <vector>

class Query;

class QueryBuilder;

class BoolQueryType;

class BoolQueryParams;

/**
 * This will be the Querybuilder similar to the Python elasticsearch_dsl package
 */
//Base class
class QueryBuilder {
private:
    std::string currentQuery = R"("query": {$TOKEN$)";
    std::string tempString;
    int queryDepth = 2;

    friend class Query;

    friend class BoolQueryParams;

    friend class BoolQueryType;

public:

    std::string getQuery();

    void incrementQueryDepth(int inc);

    std::string build();
};

class BoolQueryParams {
private:
    QueryBuilder base;
public:
    std::vector<std::string> tempParams;

    BoolQueryType exists(std::string fieldName);

    BoolQueryType term(std::string term);

    BoolQueryType range(std::string upperBound, std::string lowerBound, std::string pattern);
};

class BoolQueryType : public BoolQueryParams {
private:
    QueryBuilder base;
public:
    QueryBuilder mustNot();

    QueryBuilder must();

    QueryBuilder should(int minimumMatches);
};