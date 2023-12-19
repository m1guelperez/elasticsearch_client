import environment;
import utilFunctions;
import client;
import searchquery;

#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <simdjson/simdjson.h>
#include <iostream>
#include <string>


/**
 * Only used for testing the library.
 *
 */
int main() {
    std::string xx = R"(hello $TOKEN$ "are" you?)";
    xx.replace(xx.find("$TOKEN$"), 7,"how");
    std::cout << xx << std::endl;
//    utils::initEsClient();
    std::string data = R"({"query": {"match": {"_id": "1JmY64cBVyaa_XZk6pTw"}})";
    simdjson::padded_string xxx(data);
    std::cout << xxx << std::endl;
    int indent = 4;

    // Configuration config;
    // config.loadConfigfile();

    const std::string HOST = "localhost";
    const int PORT = 9200;


    CURLcode res{};
    Client client{HOST, PORT};
    client.verboseLogging(1L);

    Search search{};
    std::string body = search.matchQuery("name", "test")->buildQuery();
    auto finalRes = client.search("miguel", body);
    nlohmann::json j = nlohmann::json::parse(client.getReadBuffer());
    std::cout << "Response from ES: " << j.dump(indent) << std::endl;
//    utils::responseCheck(finalRes);
//    utils::cleanUpEsClient();
    return 0;
}