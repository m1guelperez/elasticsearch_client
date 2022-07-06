//
// Created by miguel on 6/7/22.
//

#include "queries.h"

#include <string>
#include <iostream>
#include <memory>

// Creates a ptr to a created subclass containing a wildcard request
std::unique_ptr<Query> QueryBuilder::wildcard(const std::string &field, const std::string &value) {
    std::unique_ptr<Query> query(new Query);
    std::string wildcardQuery = "\"wildcard\": {\n "
                                "  \"" + field + "\": {\n"
                                                 "    \"value\":" + "\"" + value + "\"";
    query->currentQuery = currentQuery.append(wildcardQuery);
    query->incrementQueryDepth(2);
    return query;
}

//TODO: Continue finishing bool queries
std::unique_ptr<BoolQuery> QueryBuilder::bools(const std::string &field, const std::string &value) {
    std::unique_ptr<BoolQuery> query(new BoolQuery);
    std::string boolQuery = "\"bool\": {\n ";
    query->currentQuery = currentQuery.append(boolQuery);
    query->incrementQueryDepth(1);
    return query;
}

void BoolQuery::must() {}

void BoolQuery::mustNot() {}

void BoolQuery::minimumShouldMatch() {}

void BoolQuery::should() {}

std::string QueryBuilder::getQuery() {
    return currentQuery;
}

void QueryBuilder::incrementQueryDepth(int inc) {
    this->queryDepth = queryDepth + inc;
}

int QueryBuilder::getQueryDepth() const {
    return queryDepth;
}

//Will check the number of nested statements and close them. Results in a built string.
std::string QueryBuilder::build() {
    for (int i = 0; i < this->queryDepth; ++i) {
        this->currentQuery.append("\n}");
    }
    return this->currentQuery;
}