//
// Created by miguel on 6/7/22.
//

#pragma once

#include <curl/curl.h>
namespace utils {
//Init cURL
    void initEsClient();

//Global cURL cleanup
    void cleanUpEsClient();
}