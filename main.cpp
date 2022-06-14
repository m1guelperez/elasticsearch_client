#include <iostream>
#include <curl/curl.h>
#include <string>

#include "Client.h"
#include "utilities/logger/logger.h"
#include "utilities/environment.h"
#include "simdjson/singleheader/simdjson.h"
#include "utilities/validationHandler.h"

int main() {

    initEsClient();
    Logger logger{};
    logger.setLogLevel(logger.INFO);

    const std::string HOST = "http://localhost";
    constexpr int PORT = 9200;
    CURLcode res{};
    Client client{HOST, PORT};
    //client.setCurlVerbose();

    // The first '/' is important!
    //res = client.search("/miguels_test_index");
    //std::cout << "Print: " << client.getReadBuffer() << client.getReadBuffer().length() << std::endl;

    std::string document = "{\n"
                           "  \"name\" : \"uff\",\n"
                           "  \"height\": 0\n"
                           "}";

    res = client.insertDocument("/miguels_test_index", document);
    std::cout << "Response: " << client.getReadBuffer() << std::endl;
    responseCheck(res);

    std::string req = "{\n"
                      "  \"query\": {\n"
                      "    \"match\": {\n"
                      "      \"name\": \"uff\"\n"
                      "    }\n"
                      "  }\n"
                      "}";

    auto res3 = client.search("/miguels_test_index",req);
    std::cout << "Response: " << client.getReadBuffer() << std::endl;
    responseCheck(res3);

    auto res2 = client.search("/miguels_test_index");
    std::cout << "Response: " << client.getReadBuffer() << std::endl;
    responseCheck(res2);

    client.cleanUp();
    cleanUpEsClient();
    return 0;
}
