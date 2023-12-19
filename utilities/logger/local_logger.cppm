//
// Created by miguel on 6/7/22.
//
export module local_logger;

#include <iostream>
#include <string>

class Logger {
public:
    void setLogLevel(int level);

    int getCurrentLogLevel() const;

    void error(const std::string &msg) const;

    void debug(const std::string &msg) const;

    void info(const std::string &msg) const;

    const int ERROR = 0;
    const int DEBUG = 1;
    const int INFO = 2;

private:
    int currentLogLevel = 0;
};

int Logger::getCurrentLogLevel() const {
    std::cout << "Current Loglevel is: " << currentLogLevel << std::endl;
    return currentLogLevel;
}

void Logger::setLogLevel(int level) {
    currentLogLevel = level;
    std::cout << "Set Loglevel to: " << level << std::endl;
}

void Logger::error(const std::string &msg) const {
    if (currentLogLevel >= ERROR) {
        std::cout << "[ERROR]: " << msg << std::endl;
    }
}

void Logger::debug(const std::string &msg) const {
    if (currentLogLevel >= DEBUG) {
        std::cout << "[DEBUG]: " << msg << std::endl;
    }
}

void Logger::info(const std::string &msg) const {
    if (currentLogLevel == INFO) {
        std::cout << "[INFO]: " << msg << std::endl;
    }
}