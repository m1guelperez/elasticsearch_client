//
// Created by miguel on 6/7/22.
//

#pragma once

#include <string>
#include <memory>

class QueryBuilder;

class Query;

class BoolQuery;
/**
 * This will be the Querybuilder similar to the Python elasticsearch_dsl package
 */

//Base class
class QueryBuilder {
private:
    std::string currentQuery = "{\n \"query\": {\n ";
    int queryDepth = 2;

    friend class Query;

    friend class BoolQuery;

public:
    std::unique_ptr<Query> wildcard(const std::string &field, const std::string &value);

    std::unique_ptr<BoolQuery> bools(const std::string &field, const std::string &value);

    std::string getQuery();

    void incrementQueryDepth(int inc);

    int getQueryDepth() const;

    std::string build();
};

// First inheritance
class Query : public QueryBuilder {

private:
public:
};

class BoolQuery : public QueryBuilder {
public:
    void mustNot();

    void must();

    void should();

    void minimumShouldMatch();
};