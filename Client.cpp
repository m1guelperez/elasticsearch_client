//
// Created by miguel on 6/6/22.
//

#include "Client.h"

#include <string>
#include <curl/curl.h>
#include <cstring>
#include <iostream>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}

Client::Client(const std::string &hostParam, int portParam) {
    this->HOST = hostParam;
    this->PORT = portParam;
    this->url = (HOST + ":" + std::to_string(PORT));
    this->curl = curl_easy_init();
    this->header = nullptr;
    this->header = curl_slist_append(this->header, "Content-Type: application/json");
    log.setLogLevel(log.INFO);
}

void Client::setHost(const std::string &hostParam) {
    this->HOST = hostParam;
}

//TODO: Maybe make all getter functions const?
std::string Client::getReadBuffer() {
    return this->readBuffer;
}

std::string Client::getHost() {
    return this->HOST;
}

int Client::getPort() const {
    return this->PORT;
}

void Client::setHeader(const std::string &headerOptions) {
    this->header = nullptr;
    this->header = curl_slist_append(this->header, headerOptions.c_str());
}

void Client::resetHeader() {
    curl_slist_free_all(this->header);
    this->header = nullptr;
}

CURLcode Client::search(const std::string &index, const std::string &query) {
    this->url.append(index + "/_search");
    return executeQuery("GET", query);
}

CURLcode Client::search(const std::string &index) {
    this->url.append(index + "/_search");
    return executeQuery("GET");
}

CURLcode Client::remove(const std::string &index) {
    this->url.append(index);
    return executeQuery("DELETE");
}


CURLcode Client::update(const std::string &index, const std::string &query, const std::string &id) {
    this->url.append(index + "/_update" + id);
    return executeQuery("POST", query);
}

CURLcode Client::index(const std::string &indexName) {
    this->url.append(indexName);
    return executeQuery("PUT");
}

CURLcode Client::index(const std::string &indexName, const std::string &query) {
    this->url.append(indexName);
    return executeQuery("PUT", query);
}

CURLcode Client::insertDocument(const std::string &index, const std::string &body) {
    this->url.append(index + "/_doc");
    std::cout << this->url << std::endl;
    return executeQuery("POST", body);
}

CURLcode Client::insertDocument(const std::string &index, const std::string &body, const std::string &id) {
    this->url.append(index + "/_doc/" + id);
    return executeQuery("POST", body);
}

CURLcode Client::executeQuery(const std::string &requestMode, const std::string &query) {
    curl_easy_setopt(this->curl, CURLOPT_BUFFERSIZE, 102400L);
    curl_easy_setopt(this->curl, CURLOPT_URL, this->url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, query.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE_LARGE, strlen(query.c_str()));
    curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->header);
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, requestMode.c_str());
    curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 1L);
    CURLcode code = curl_easy_perform(this->curl);
    return code;
}

CURLcode Client::executeDirtyQuery(const std::string &requestMode, const std::string &index, const std::string &query) {
    this->url.append(index);
    curl_easy_setopt(this->curl, CURLOPT_BUFFERSIZE, 102400L);
    curl_easy_setopt(this->curl, CURLOPT_URL, this->url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, query.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE_LARGE, strlen(query.c_str()));
    curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->header);
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, requestMode.c_str());
    curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 1L);
    CURLcode code = curl_easy_perform(this->curl);
    return code;
}

CURLcode Client::executeQuery(const std::string &requestMode) {
    std::string requestUrl = this->url;
    curl_easy_setopt(this->curl, CURLOPT_BUFFERSIZE, 102400L);
    curl_easy_setopt(this->curl, CURLOPT_URL, requestUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->header);
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, requestMode.c_str());
    curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 1L);
    CURLcode code = curl_easy_perform(this->curl);
    return code;
}

// Will be used for when the QueryBuilder is ready
CURLcode Client::executeQuery(const std::string &index, QueryBuilder query, const std::string &requestMode) {
    std::string temp = query.getCurrentQuery();
    std::string requestUrl = this->url + index;
    curl_easy_setopt(this->curl, CURLOPT_BUFFERSIZE, 102400L);
    curl_easy_setopt(this->curl, CURLOPT_URL, requestUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, temp.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE_LARGE, strlen(temp.c_str()));
    curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->header);
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, requestMode.c_str());
    curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 1L);
    CURLcode code = curl_easy_perform(this->curl);
    return code;
}

void Client::cleanUp() {
    curl_easy_cleanup(this->curl);
    if (this->header != nullptr) {
        curl_slist_free_all(this->header);
    }
}