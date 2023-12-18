//
// Created by miguel on 6/7/22.
//

#include "queries.h"
#include "../utilFunctions.h"

#include <string>
#include <iostream>
#include <memory>

const std::string TOKEN = "$TOKEN$";
constexpr int REPLACE_TOKEN = 7;
const std::string BOOL_PARAM = "$BOOL_PARAM$";
constexpr int REPLACE_BOOL_PARAM = 12;

class QueryBuilder {
    std::string currentQuery = R"("query": {$TOKEN$})";
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

    BoolQueryType exists(std::vector<std::string>& fieldName);

    BoolQueryType term(std::string term);

    BoolQueryType range(std::string upperBound, std::string lowerBound, const std::string& pattern);
};

class BoolQueryType : public BoolQueryParams {
private:
    QueryBuilder base;
public:
    QueryBuilder mustNot();

    QueryBuilder must();

    QueryBuilder should(int minimumMatches);
};


QueryBuilder BoolQueryType::must() {
    this->base.currentQuery.replace(base.currentQuery.find(TOKEN), REPLACE_TOKEN, R"("bool":{"must":[{$TOKEN$}])");
    return this->base;
}


QueryBuilder BoolQueryType::mustNot() {
    this->base.currentQuery.replace(base.currentQuery.find(TOKEN), REPLACE_TOKEN,
                                    R"("bool": {"must_not": [{$BOOL_PARAM$}]})");
    return this->base;
}

QueryBuilder BoolQueryType::should(int minimumMatches = 1) {
    this->base.currentQuery.replace(base.currentQuery.find(TOKEN), REPLACE_TOKEN,
                                    R"("bool": {"should": [{$BOOL_PARAM$}]})");
    this->base.currentQuery.append(R"(minimum_should_match" :")" + std::to_string(minimumMatches) + ",");
    return this->base;
}

BoolQueryType BoolQueryParams::exists(std::vector<std::string>& fieldName) {

    for (auto& field : fieldName) {
        this->base.currentQuery.replace(base.currentQuery.find(TOKEN), REPLACE_TOKEN,
                                        R"("exists": {"field": ")" + field + R"("},$BOOL_PARAM$)");
    }
    return BoolQueryType();
}

BoolQueryType BoolQueryParams::term(std::string term) {
    return BoolQueryType();
}

BoolQueryType BoolQueryParams::range(std::string upperBound, std::string lowerBound, const std::string& pattern = "==") {
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
    return this->currentQuery = clean_token_fields(this->currentQuery);
}

std::string clean_token_fields(std::string query) {
    return query.replace(query.find(TOKEN), REPLACE_TOKEN, "");
}