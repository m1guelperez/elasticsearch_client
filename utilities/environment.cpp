//
// Created by miguel on 6/7/22.
//

#include "environment.h"
#include <curl/curl.h>

void utils::initEsClient() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

void utils::cleanUpEsClient() {
    curl_global_cleanup();
}