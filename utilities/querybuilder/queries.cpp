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

//TODO: Continue finishing bool queries
Query Query::boolQuery() {
    if (this->queryDepth > 2) {
        this->currentQuery.append(", \n \" bool\": {\n");
    } else {
        this->currentQuery.append("\n \" bool\": {\n");

    }
    return *this;
}