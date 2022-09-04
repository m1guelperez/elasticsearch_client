#include <iostream>
#include <curl/curl.h>
#include <string>

#include "Client.h"
#include "utilities/environment.h"
#include "simdjson/singleheader/simdjson.h"
#include "utilities/utilFunctions.h"
#include "utilities/configfileHandler.h"

/**
 * Only used for testing the library.
 *
 */
int main() {

    utils::initEsClient();

    Configuration config;
    config.loadConfigfile();

    const std::string HOST = config.getHost();
    const int PORT = config.getPort();


    CURLcode res{};
    Client client{HOST, PORT};
    client.verboseLogging(1L);

    // The first '/' is important!
    //res = client.search("/miguels_test_index");
    //std::cout << "Print: " << client.getReadBuffer() << client.getReadBuffer().length() << std::endl;



    auto res2 = client.search("/miguels_test_index");
    std::cout << "Response: " << client.getReadBuffer() << std::endl;
    utils::responseCheck(res2);
    utils::cleanUpEsClient();
    return 0;
}
