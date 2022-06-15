//
// Created by miguel on 6/14/22.
//


#pragma once

#include <string>

/**
 * Loads a config from a textfile
 */
class Configuration {
private:
    std::string Host{};
    int Port{};

public:
    void loadConfigfile();
    std::string getHost() const;
    int getPort() const;
};
