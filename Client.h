//
// Created by miguel on 6/6/22.
//

#pragma once

#include <string>
#include <curl/curl.h>

#include "logger.h"
#include "utilities/queries.h"
#include "simdjson.h"


class Client {

private:
    std::string HOST;
    int PORT;
    std::string url;
    CURL *curl;
    struct curl_slist *header;
    std::string readBuffer;

    CURLcode executeQuery(const std::string &requestMode, const std::string &query);

    CURLcode executeQuery(const std::string &requestMode);

    CURLcode executeQuery(const std::string &index, QueryBuilder query, const std::string &requestMode);


public:
    Logger log{};

    explicit Client(const std::string &hostParam, int portParam);

    std::string getReadBuffer();

    std::string getHost();

    int getPort() const;

    void setHost(const std::string &hostParam);
    
    CURLcode search(const std::string &index, const std::string &query);

    CURLcode search(const std::string &index);

    CURLcode remove(const std::string &index);

    CURLcode index(const std::string &indexName, const std::string &query);

    CURLcode index(const std::string &indexName);

    CURLcode update(const std::string &index, const std::string &query, const std::string &id);

    //TODO: Eventually put it into the index function
    CURLcode insertDocument(const std::string &index, const std::string &body, const std::string &id);

    CURLcode insertDocument(const std::string &index, const std::string &body);

    CURLcode executeDirtyQuery(const std::string &requestMode, const std::string &index, const std::string &query);

    void setHeader(const std::string &headerOptions);

    void resetHeader();

    void cleanUp();
};