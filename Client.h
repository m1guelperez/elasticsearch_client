//
// Created by miguel on 6/6/22.
//

#pragma once

#include <string>
#include <curl/curl.h>

#include "logger.h"
#include "utilities/queries.h"


// TODO: Refactor object attributes, especially currentQuerry
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

    void setCurrentQuery(std::string query);

    CURLcode search(const std::string &index, const std::string &query);

    CURLcode remove();

    CURLcode index(const std::string &indexName, const std::string &query);

    CURLcode update(const std::string &index, const std::string &query, const std::string &id);

    CURLcode executeQuery(const std::string &index, const std::string &requestMode);

    CURLcode executeQuery(const std::string &index, QueryBuilder query, const std::string &requestMode);

    CURLcode executeQueryDirect(const std::string &requestMode, std::string query);

    void setHeader(const std::string &headerOptions);

    void resetHeader();

    void cleanUp();
};