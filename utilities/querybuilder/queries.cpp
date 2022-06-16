//
// Created by miguel on 6/7/22.
//

#include "queries.h"

#include <string>

QueryBuilder QueryBuilder::match(const std::string& key, const std::string& value) {
    this->currentQuery = "{\n"
                         "  \"query\": {\n"
                         "    \"match\": {\n"
                         "      \"" + key + "\": " + "\"" + value + "\"\n" +
                         "    }\n"
                         "  }\n"
                         "}";
    return *this;
}

QueryBuilder QueryBuilder::wildcard() {
    return *this;
}

std::string QueryBuilder::getCurrentQuery() {
    return this->currentQuery;
}

void QueryBuilder::resetQuery() {
    this->currentQuery = "";
}