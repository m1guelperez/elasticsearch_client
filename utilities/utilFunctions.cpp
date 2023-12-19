//
// Created by miguel on 6/11/22.
//

#include "utilFunctions.h"

#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "logger/logger.h"

Logger logger{};

bool utils::responseCheck(CURLcode res) {
    if (res != CURLE_OK) {
        std::cout << "Error: " << *curl_easy_strerror(res) << std::endl;
        std::ostringstream errorMsg;
        errorMsg << "Request failed with the following error code: " << (int) res;
        logger.error(errorMsg.str());
        return false;
    } else {
        std::cout << "Request successfully!" << std::endl;
        return true;
    }
}

std::string utils::trim(std::string pattern) {
    pattern.erase(remove(pattern.begin(), pattern.end(), ' '), pattern.end());
    return pattern;
}