//
// Created by miguel on 6/7/22.
//
export module enviorment;

#include <curl/curl.h>
namespace environment {
    void environment::initEsClient() {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }

    void environment::cleanUpEsClient() {
        curl_global_cleanup();
    }
}