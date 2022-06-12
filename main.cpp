#include <iostream>
#include <curl/curl.h>
#include <string>

#include "Client.h"
#include "logger.h"
#include "utilities/environment.h"
#include "simdjson/singleheader/simdjson.h"

int main() {

    initEsClient();
    Logger logger{};
    logger.setLogLevel(logger.INFO);

    const std::string HOST = "http://localhost";
    constexpr int PORT = 9200;
    CURLcode res{};
    Client client{HOST, PORT};

    // The first '/' is important!
    //res = client.search("/miguels_test_index");
    //std::cout << "Print: " << client.getReadBuffer() << client.getReadBuffer().length() << std::endl;

    std::string document = "{\n"
                           "  \"name\" : \"test2\",\n"
                           "  \"height\": 1239\n"
                           "}";


    res = client.insertDocument("/test_index", document);
    std::cout << "Print: " << client.getReadBuffer() << std::endl;

    if (res != CURLE_OK) {
        std::cout << "Error: " << *curl_easy_strerror(res) << std::endl;
        std::ostringstream errorMsg;
        errorMsg << "Request failed with the following error code: " << (int) res;
        logger.error(errorMsg.str());
        cleanUpEsClient();
    } else {
        std::cout << "Request successfully!" << std::endl;
    }

    client.cleanUp();
    cleanUpEsClient();
    return 0;
}
