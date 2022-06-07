//
// Created by miguel on 6/6/22.
//

#include "queries.h"

#include <string>
#include <curl/curl.h>


Query::Query(const std::string &hostParam) {
    this->host = hostParam.c_str();
    log.setLogLevel(log.INFO);
}

void Query::setHost(const char hostParam[]) {
    this->host = hostParam;
}

const char *Query::getHost() {
    return host;
}


void Query::setCurrentQuery() {

}

// As soon as we get the finalized query, the internal query string is reset.
const char *Query::getCurrentQuery() {
    const char *temp = currentQuery.c_str();
    this->currentQuery = "";
    return temp;
}


Query Query::match(std::string key, std::string value) {
    this->currentQuery = "{\n"
                         "  \"query\": {\n"
                         "    \"match\": {\n"
                         "      \"" + key + "\": " + "\"" + value + "\"\n" +
                         "    }\n"
                         "  }\n"
                         "}'";
    log.info(currentQuery);
    return *this;
}

Query Query::wildcard() {
    return *this;
}


int Query::sendQuery() {
    currentQuery.c_str();
    return 2;
}