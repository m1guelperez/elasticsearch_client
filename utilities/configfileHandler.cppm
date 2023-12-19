//
// Created by miguel on 6/14/22.
//

export module configfileHandler;

#include <string>
#include <fstream>
#include <algorithm>

//TODO: Is there a better path logic?
//TODO: Delete whitespaces

class Configuration {
    std::string Host{};
    int Port{};

public:
    void loadConfigfile();
    std::string getHost() const;
    int getPort() const;
};
void Configuration::loadConfigfile() {
    std::ifstream file;
    file.open("../resources/configfile.txt");

    std::string value;
    std::string line;
    while (std::getline(file, line, '=')) {
        std::getline(file, value, '\n');
        if (line == "HOST") {
            value.erase(std::remove(value.begin(), value.end(), '"'), value.end());
            this->Host = value;
        } else if (line == "PORT") {
            this->Port = std::stoi(value);
        }
    }
    file.close();
}

std::string Configuration::getHost() const {
    return this->Host;
}

int Configuration::getPort() const {
    return this->Port;
}