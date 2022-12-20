//
// Created by miguel on 6/6/22.
//

#include "Client.h"

#include <string>
#include <curl/curl.h>
#include <cstring>
#include <iostream>

static size_t WriteCallback(void *receivedContents, size_t size, size_t nmemb, void *buffer) {
    ((std::string *) buffer)->append((char *) receivedContents, size * nmemb);
    return size * nmemb;
}

Client::Client(const std::string &hostParam, int portParam) {
    this->HOST = hostParam;
    this->PORT = portParam;
    this->baseUrl = (HOST + ":" + std::to_string(PORT) + "/");
    this->executionUrl = baseUrl;
    initCurlDefaults();
    log.setLogLevel(log.INFO);
}

Client::~Client() {
    this->cleanUp();
}

//TODO: Reset set variables (POSTFIELDS etc.)
void Client::initCurlDefaults() {
    this->curl = curl_easy_init();
    this->header = nullptr;
    this->header = curl_slist_append(this->header, "Content-Type: application/json");
    curl_easy_setopt(this->curl, CURLOPT_BUFFERSIZE, 102400L);
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &this->readBuffer);
    curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->header);
    curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 0L);
}

CURLcode Client::elasticUnderscoreApi(const std::string &index, const std::string &api, const std::string &query,
                                      const std::string &requestMode) {
    this->executionUrl.append(index + "/" + api);
    return executeQuery(requestMode, query);
}

CURLcode Client::elasticUnderscoreApi(const std::string &index, const std::string &api, const std::string &query,
                                      const std::string &id,
                                      const std::string &requestMode) {
    this->executionUrl.append(index + "/" + api + "/" + id);
    return executeQuery(requestMode, query);
}

CURLcode Client::elasticUnderscoreApi(const std::string &index, const std::string &api) {
    this->executionUrl.append(index + "/" + api);
    return executeQuery("GET");
}

CURLcode Client::elasticSingleRequest(const std::string &index, const std::string &requestMode) {
    this->executionUrl.append(index);
    return executeQuery(requestMode);
}

CURLcode
Client::elasticSingleRequest(const std::string &index, const std::string &query, const std::string &requestMode) {
    this->executionUrl.append(index);
    return executeQuery(requestMode, query);
}

CURLcode Client::search(const std::string &index, const std::string &query) {
    return this->elasticUnderscoreApi(index, "_search", query, "GET");
}

CURLcode Client::search(const std::string &index) {
    return this->elasticUnderscoreApi(index, "_search");
}

CURLcode Client::count(const std::string &index) {
    return this->elasticUnderscoreApi(index, "_count");
}

CURLcode Client::count(const std::string &index, const std::string &query) {
    return this->elasticUnderscoreApi(index, "_search", query, "POST");
}

CURLcode Client::refresh(const std::string &index) {
    return this->elasticUnderscoreApi(index, "_refresh");
}

CURLcode Client::remove(const std::string &index) {
    return this->elasticSingleRequest(index, "DELETE");
}

CURLcode Client::update(const std::string &index, const std::string &query, const std::string &id) {
    return this->elasticUnderscoreApi(index, "_update", query, id, "POST");
}

CURLcode Client::index(const std::string &indexName) {
    return elasticSingleRequest(indexName, "PUT");
}

CURLcode Client::index(const std::string &indexName, const std::string &query) {
    return this->elasticSingleRequest(indexName, query, "PUT");
}

CURLcode Client::insertDocument(const std::string &index, const std::string &query) {
    return this->elasticUnderscoreApi(index, "_doc", query, "POST");
}

CURLcode Client::insertDocument(const std::string &index, const std::string &query, const std::string &id) {
    return this->elasticUnderscoreApi(index, "_doc", query, id, "POST");
}
//TODO: Implement
CURLcode bulk(const std::string) {}

CURLcode Client::executeQuery(const std::string &requestMode, const std::string &query) {
    resetReadBuffer();
    setCurlParams(requestMode, query);
    CURLcode code = curl_easy_perform(this->curl);
    this->executionUrl = this->baseUrl;
    return code;
}

CURLcode Client::stringQuery(const std::string &requestMode, const std::string &index, const std::string &query) {
    resetReadBuffer();
    setCurlParams(requestMode, query);
    CURLcode code = curl_easy_perform(this->curl);
    this->executionUrl = this->baseUrl;
    return code;
}

CURLcode Client::executeQuery(const std::string &requestMode) {
    resetReadBuffer();
    std::string requestUrl = this->executionUrl;
    setCurlParamsWithoutPostBody(requestMode);
    CURLcode code = curl_easy_perform(this->curl);
    this->executionUrl = this->baseUrl;
    return code;
}

// Will be used for when the QueryBuilder is ready
CURLcode Client::executeQuery(const std::string &index, QueryBuilder query, const std::string &requestMode) {
    resetReadBuffer();
    std::string temp = query.getQuery();
    std::string requestUrl = this->executionUrl + index;
    curl_easy_setopt(this->curl, CURLOPT_URL, this->executionUrl.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, temp.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE_LARGE, strlen(temp.c_str()));
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, requestMode.c_str());
    CURLcode code = curl_easy_perform(this->curl);
    this->executionUrl = this->baseUrl;
    return code;
}

void Client::cleanUp() {
    curl_easy_cleanup(this->curl);
    if (this->header != nullptr) {
        curl_slist_free_all(this->header);
    }
}

std::string Client::getHost() const {
    return this->HOST;
}

int Client::getPort() const {
    return this->PORT;
}

void Client::setHeader(const std::string &headerOptions) {
    this->header = nullptr;
    this->header = curl_slist_append(this->header, headerOptions.c_str());
}

void Client::setHost(const std::string &hostParam) {
    this->HOST = hostParam;
}

void Client::verboseLogging(long param) {
    curl_easy_setopt(this->curl, CURLOPT_VERBOSE, param);
}

//TODO: Maybe make all getter functions const?
std::string Client::getReadBuffer() const {
    return this->readBuffer;
}

void Client::resetHeader() {
    curl_slist_free_all(this->header);
    this->header = nullptr;
}

void Client::resetReadBuffer() {
    this->readBuffer = "";
}

//Used for every request which uses a body/POSTFIELDS.
void Client::setCurlParams(const std::string &requestMode, const std::string &query) {
    curl_easy_setopt(this->curl, CURLOPT_URL, this->executionUrl.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, query.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE_LARGE, strlen(query.c_str()));
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, requestMode.c_str());
}

//Only used for requests which do not have a body.
void Client::setCurlParamsWithoutPostBody(const std::string &requestMode) {
    //Fields like POSTFIELDSIZE etc., have to be unset when sending a GET, which does not have any POSTFIELDS otherwise this will be reused.
    curl_easy_setopt(this->curl, CURLOPT_HTTPGET, true);
    curl_easy_setopt(this->curl, CURLOPT_URL, this->executionUrl.c_str());
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, requestMode.c_str());
}