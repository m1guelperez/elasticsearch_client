//
// Created by miguel on 6/6/22.
//

#pragma once

#include <string>
#include <curl/curl.h>

#include "utilities/logger/logger.h"
#include "utilities/querybuilder/queries.h"
#include "simdjson.h"

/**
 * Client which will execute queries to elasticsearch
 * @param hostParam elasticsearch host
 * @param portParam elasticsearch port
 */
class Client {

private:
    std::string HOST;
    int PORT;
    std::string baseUrl;
    std::string executionUrl;
    CURL *curl{};
    struct curl_slist *header{};
    std::string readBuffer;

    void setCurlParams(const std::string &requestMode, const std::string &query);

    void setCurlParamsWithoutPostBody(const std::string &requestMode);

    //Function overloading for different executions via cURL
    CURLcode executeQuery(const std::string &requestMode, const std::string &query);

    CURLcode executeQuery(const std::string &requestMode);

    CURLcode executeQuery(const std::string &index, QueryBuilder query, const std::string &requestMode);

    void initCurlDefaults();

    void resetReadBuffer();

public:
    Logger log{};

    explicit Client(const std::string &hostParam, int portParam);

    ~Client();

    std::string getReadBuffer() const;

    std::string getHost() const;

    int getPort() const;

    void setHost(const std::string &hostParam);

    // Several queries

    CURLcode elasticUnderscoreApi(const std::string &index, const std::string &api, const std::string &query,
                                  const std::string &requestMode);

    CURLcode elasticUnderscoreApi(const std::string &index, const std::string &api);

    CURLcode elasticUnderscoreApi(const std::string &index, const std::string &api, const std::string &query,
                                  const std::string &documentID,
                                  const std::string &requestMode);

    CURLcode elasticSingleRequest(const std::string &index, const std::string& query, const std::string &requestMode);

    CURLcode elasticSingleRequest(const std::string &index, const std::string &requestMode);

    CURLcode search(const std::string &index, const std::string &query);

    CURLcode search(const std::string &index);

    CURLcode count(const std::string &index);

    CURLcode count(const std::string &index, const std::string &query);

    CURLcode refresh(const std::string &index);

    CURLcode remove(const std::string &index);

    CURLcode index(const std::string &indexName, const std::string &query);

    CURLcode index(const std::string &indexName);

    CURLcode update(const std::string &index, const std::string &query, const std::string &id);

    //TODO: Eventually put it into the index function
    CURLcode insertDocument(const std::string &index, const std::string &body, const std::string &id);

    CURLcode insertDocument(const std::string &index, const std::string &query);

    CURLcode executeDirtyQuery(const std::string &requestMode, const std::string &index, const std::string &query);

    //1L will activate verbose output and 0L will deactivate it.
    void setCurlVerbose(long param);

    void setHeader(const std::string &headerOptions);

    void resetHeader();

    void cleanUp();
};