//
// Created by miguel on 6/7/22.
//

#include "queries.h"
#include "../utilFunctions.h"

#include <string>
#include <iostream>
#include <memory>

std::shared_ptr<QueryBuilder> queryBuilder() {
    std::shared_ptr<QueryBuilder> baseQuery(new QueryBuilder);
    return baseQuery;
}


QueryBuilder BoolQueryType::must() {
    this->base.currentQuery.append("\"bool\": {\n"
                                   "      \"must\": [\n"
                                   "        {\n");
    this->base.tempString.append("}\n"
                                   "      ]");
    return this->base;
}



QueryBuilder BoolQueryType::mustNot() {
    this->base.currentQuery.append("\"bool\": {\n"
                                   "      \"must_not\": [\n"
                                   "        {\n");
    this->base.currentQuery.append("}\n"
                                   "      ]");
    return this->base;
}

QueryBuilder BoolQueryType::should(int minimumMatches) {
    this->base.currentQuery.append("\"bool\": {\n"
                                   "      \"should\": [\n"
                                   "        {\n");
    this->base.currentQuery.append("}\n"
                                   "      ]");
    this->base.currentQuery.append("\"minimum_should_match\" :" + std::to_string(minimumMatches) + ",");
    return this->base;
}

BoolQueryType BoolQueryParams::exists(std::string fieldName) {
    return BoolQueryType();
}

BoolQueryType BoolQueryParams::term(std::string term) {
    return BoolQueryType();
}

BoolQueryType BoolQueryParams::range(std::string upperBound, std::string lowerBound, std::string pattern = "==") {
    //Default pattern is gte and lte
    if (utils::trim(pattern) == "><") {
        //use gt and lt
    } else if (utils::trim(pattern) == "=><") {
        //use gte and lt
    } else if (utils::trim(pattern) == ">=<") {
        //use gt and lte
    } else {
        std::cout << "Pattern not recognized." << std::endl;
    }
}

std::string QueryBuilder::getQuery() {
    return currentQuery;
}

void QueryBuilder::incrementQueryDepth(int inc) {
    this->queryDepth = queryDepth + inc;
}

//Will check the number of nested statements and close them. Results in a built string.
std::string QueryBuilder::build() {
    for (int i = 0; i < this->queryDepth; ++i) {
        this->currentQuery.append("\n}");
    }
    return this->currentQuery;
}