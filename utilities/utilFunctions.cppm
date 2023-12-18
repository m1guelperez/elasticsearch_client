//
// Created by miguel on 6/11/22.
//
export module utils;
import <curl/curl.h>;
import <iostream>;
import <sstream>;
import "../utilities/logger/local_logger.cppm";


Logger logger{};

namespace utils {
    bool utils::responseCheck(CURLcode res) {
        if (res != CURLE_OK) {
            std::cout << "Error: " << *curl_easy_strerror(res) << std::endl;
            std::ostringstream errorMsg;
            errorMsg << "Request failed with the following error code: " << res;
            logger.error(errorMsg.str());
            return false;
        }
        std::cout << "Request successfully!" << std::endl;
        return true;
    }

    std::string utils::trim(std::string pattern) {
        pattern.erase(remove(pattern.begin(), pattern.end(), ' '), pattern.end());
        return pattern;
    }
}
