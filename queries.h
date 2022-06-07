//
// Created by miguel on 6/6/22.
//

#pragma once

#include <string>

#include "logger.h"

class Query {

private:
    const char *host;
    std::string currentQuery;

public:
    Logger log{};

    explicit Query(const std::string& hostParam);

    Query match(std::string key, std::string value);

    Query wildcard();

    const char *getHost();

    void setHost(const char host[]);

    const char *getCurrentQuery();

    void setCurrentQuery();

    int sendQuery();
};