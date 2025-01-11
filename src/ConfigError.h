#pragma once
#include <exception>
#include <string>

class ConfigError :public std::exception {
private:
    std::string msg;
public:
    ConfigError(std::string msg) :msg(msg) {};
    const char* what() {
        return msg.c_str();
    }
};

class ConfigWarning :public std::exception {
private:
    std::string msg;
public:
    ConfigWarning(std::string msg) :msg(msg) {};
    const char* what() {
        return msg.c_str();
    }
};
