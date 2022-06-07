//
// Created by miguel on 6/7/22.
//

#pragma once

#include <string>

class Logger {
public:
    void setLogLevel(int level);

    int getCurrentLogLevel() const;

    void error(const std::string &msg);

    void debug(const std::string &msg);

    void info(const std::string &msg);

    const int ERROR = 0;
    const int DEBUG = 1;
    const int INFO = 2;

private:
    int currentLogLevel = 0;
};
