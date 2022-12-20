#include <iostream>
#include <curl/curl.h>
#include <string>

#include "Client.h"
#include "utilities/environment.h"
#include "utilities/utilFunctions.h"
#include "utilities/configfileHandler.h"
#include <simdjson/simdjson.h>
#include "utilities/querybuilder/searchQuery.h"
#include <nlohmann/json.hpp>

/**
 * Only used for testing the library.
 *
 */
int main() {

    utils::initEsClient();
    simdjson::ondemand::parser parser;

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
    utils::responseCheck(finalRes);
    utils::cleanUpEsClient();
    return 0;
}


/*
 * Lets say I have the following class:

```c++
class Text {
private:
  std::string content;
  std::string title;
public:
  void add_content();
  void add_title();
}
```
And I have the following implementation:
```c++
void Text::add_content(std::string content) {
  this->content.append(content);
}
```


 */