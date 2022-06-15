//
// Created by miguel on 6/11/22.
//

#include "validationHandler.h"

#include <curl/curl.h>
#include <iostream>
#include <sstream>

#include "environment.h"
#include "logger/logger.h"

Logger logger{};

bool responseCheck(CURLcode res) {
    if (res != CURLE_OK) {
        std::cout << "Error: " << *curl_easy_strerror(res) << std::endl;
        std::ostringstream errorMsg;
        errorMsg << "Request failed with the following error code: " << (int) res;
        logger.error(errorMsg.str());
        cleanUpEsClient();
        return false;
    } else {
        std::cout << "Request successfully!" << std::endl;
        return true;
    }
}
