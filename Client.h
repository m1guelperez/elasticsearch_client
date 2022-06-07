//
// Created by miguel on 6/6/22.
//

#pragma once

#include <string>
#include <curl/curl.h>

#include "logger.h"
#include "utilities/queries.h"

class Client {

private:
    std::string HOST;
    int PORT;
    std::string url;
    std::string currentQuery;
    CURL *curl;
    struct curl_slist *header;

public:
    Logger log{};

    explicit Client(const std::string &hostParam, int portParam);

    std::string getHost();

    int getPort() const;

    void setHost(const std::string &hostParam);

    void setIndex(const std::string &index);

    void setCurrentQuery(std::string query);

    CURLcode executeQuery(const std::string &requestMode);

    CURLcode executeQuery(QueryBuilder query, const std::string& requestMode);

    void setHeader(const std::string &headerOptions);

    void resetHeader();

    void cleanUp();
};