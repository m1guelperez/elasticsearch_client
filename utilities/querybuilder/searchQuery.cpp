//
// Created by miguel on 12/19/22.
//

#include "searchQuery.h"
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

Search *Search::matchQuery(const std::string &field, const std::string &value) {
    const std::string body = "\"match\": {"
                       "\"" + field + "\": \"" + value + "\"";
    this->query.append(body);
    this->queryDepth += 1;
    std::cout << this->query << std::endl;
    return this;
}

// Omit the "" to let it behave as a number in ES.
Search *Search::matchQuery(const std::string &field, int value) {
    const std::string body = "\"match\": {"
                       "\"" + field + "\":" + std::to_string(value);
    this->query.append(body);
    this->queryDepth += 1;
    std::cout << this->query << std::endl;
    return this;
}

std::string Search::buildQuery() {
    for (int i = 0; i < this->queryDepth; ++i) {
        this->query.append("}");
    }
    // std::cout << this->query << std::endl;
    nlohmann::json j = nlohmann::json::parse(this->query);
    std::cout << "Query to execute: " << j.dump(4) << std::endl;
    return this->query;
}