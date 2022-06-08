#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>

#include "Client.h"
#include "logger.h"
#include "utilities/environment.h"


int main() {
    initEs();
    Logger logger{};
    logger.setLogLevel(logger.INFO);

    const std::string HOST = "http://localhost";
    constexpr int PORT = 9200;
    CURLcode res{};

    Client client{HOST, PORT};
    QueryBuilder builder{};


    //std::string key = "url";
    //std::string value = "https://www.google.de";
    client.setHeader("Content-Type: application/json");

    client.search("/dokumente","");

    // The first '/' is important!
    //res = client.executeQuery("/dokumente/_search","GET");

    res = CURLE_OK;

    if (res != CURLE_OK) {
        std::ostringstream errorMsg;
        errorMsg << "Request failed with the following error code: " << (int) res;
        logger.error(errorMsg.str());
        cleanUpEsClient();
    }
    client.cleanUp();
    cleanUpEsClient();
    return 0;
}
