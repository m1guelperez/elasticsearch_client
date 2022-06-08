//
// Created by miguel on 6/6/22.
//

#include "Client.h"

#include <string>
#include <curl/curl.h>
#include <cstring>
#include <iostream>

Client::Client(const std::string &hostParam, int portParam) {
    this->HOST = hostParam;
    this->PORT = portParam;
    this->url = (HOST + ":" + std::to_string(PORT));
    this->curl = curl_easy_init();
    this->header = nullptr;
    this->header = curl_slist_append(this->header, "application/x-www-form-urlencoded");
    log.setLogLevel(log.INFO);
}

void Client::setHost(const std::string &hostParam) {
    this->HOST = hostParam;
}

std::string Client::getHost() {
    return this->HOST;
}

int Client::getPort() const {
    return this->PORT;
}

void Client::setCurrentQuery(std::string query) {
    this->currentQuery = std::move(query);
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
    return executeQueryDirect("GET", query);
}

CURLcode Client::remove() {}

CURLcode Client::update(const std::string &index, const std::string &query, const std::string &id) {
    this->url.append(index + "/_update" + id);
    return executeQuery("POST", query);
}

//TODO: Add option (function overloading or so) to add body or not
CURLcode Client::index(const std::string &indexName, const std::string &query) {
    this->url.append(indexName);
    return executeQueryDirect("PUT", query);
}

//TODO eventually delete one of the following executions
CURLcode Client::executeQuery(const std::string &index, const std::string &requestMode) {
    this->url.append(index);
    std::cout << this->url << std::endl;
    curl_easy_setopt(this->curl, CURLOPT_BUFFERSIZE, 102400L);
    curl_easy_setopt(this->curl, CURLOPT_URL, this->url.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, this->currentQuery.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE_LARGE, strlen(this->currentQuery.c_str()));
    curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->header);
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, requestMode.c_str());
    curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 1L);
    CURLcode code = curl_easy_perform(this->curl);
    return code;
}

CURLcode Client::executeQueryDirect(const std::string &requestMode, std::string query) {
    curl_easy_setopt(this->curl, CURLOPT_BUFFERSIZE, 102400L);
    curl_easy_setopt(this->curl, CURLOPT_URL, this->url.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, this->currentQuery.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE_LARGE, strlen(query.c_str()));
    curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->header);
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, requestMode.c_str());
    curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 1L);
    CURLcode code = curl_easy_perform(this->curl);
    return code;
}


CURLcode Client::executeQuery(const std::string &index, QueryBuilder query, const std::string &requestMode) {
    std::string temp = query.getCurrentQuery();
    std::string requestUrl = this->url + index;
    curl_easy_setopt(this->curl, CURLOPT_BUFFERSIZE, 102400L);
    curl_easy_setopt(this->curl, CURLOPT_URL, requestUrl.c_str());
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