#pragma once

#include <string>
#include <exception>
#include <fstream>
#include <nlohmann/json.hpp>
#include "loggers/ILogger.h"

using json = nlohmann::json;

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

class Config
{
private:
    const static std::string GLOBAL_CONFIG_FNAME;

    int port;
    ILogger::Level log_level;
public:
    Config() {
        port = 12398;
        log_level = ILogger::Level::Info;
    }

    void from_args(int argc, char** argv);
    void from_file();
    
    int get_port() {
        return this->port;
    }
    ILogger::Level get_log_level() {
        return this->log_level;
    }
};