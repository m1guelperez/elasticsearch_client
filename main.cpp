#include <iostream>
#include <curl/curl.h>
#include <string>
#include <cstring>

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

    //TODO: Make this reversible
    client.setIndex("/dokumente/_search");
    std::string key = "url";
    std::string value = "https://www.gailingen.de/index.php?id=308&publish%5Bid%5D=407680&publish%5Bstart%5D=";

    //builder.match(key, value);
    client.setHeader("Content-Type: application/json");
    res = client.executeQuery("GET");
    if (res != CURLE_OK) {
        logger.error("Request failed!");
        cleanUpEsClient();
    }
    client.cleanUp();
    cleanUpEsClient();
    return 0;
}
