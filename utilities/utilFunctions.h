//
// Created by miguel on 6/11/22.
//

#pragma once

#include <curl/curl.h>
#include <string>
#include <vector>

namespace utils {
//Check if the query to elasticsearch was successfully
    bool responseCheck(CURLcode res);

    static std::string trim(std::string s);

    std::string buildParametersIntoQuery(std::vector<std::string> tempParams);
}