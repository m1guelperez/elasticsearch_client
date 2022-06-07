#include <iostream>
#include <curl/curl.h>
#include <string>
#include <cstring>

#include "queries.h"
#include "logger.h"


int main() {
    Logger logger{};
    logger.setLogLevel(logger.INFO);

    const std::string HOST = "http://localhost:9200/dokumente/_search";


    CURL *curl;
    CURLcode res;

    Query x{HOST};
    x.getHost();

    std::string key = "url";
    std::string value = "https://www.gailingen.de/index.php?id=308&publish%5Bid%5D=407680&publish%5Bstart%5D=";

    x.match(key,value);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {

        struct curl_slist *slist1;
        slist1 = nullptr;
        slist1 = curl_slist_append(slist1, "Content-Type: application/json");

        const char * query  = x.getCurrentQuery();
        size_t size = std::strlen(query);
        logger.info("Initialize cURL!");
        curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 102400L);
        curl_easy_setopt(curl, CURLOPT_URL, HOST.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, size);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        std::cout << "" << std::endl;

        if (res != CURLE_OK) {
            logger.error("Request failed!");
            curl_easy_cleanup(curl);
            curl_slist_free_all(slist1);
        }
    }
    curl_global_cleanup();
    return 0;
}
