#pragma once

#include <string>
#include <exception>
#include <fstream>
#include <nlohmann/json.hpp>
#include "loggers/ILogger.h"
#include "chat/systems/msg/CoreMsgConfig.h"
#include "chat/systems/sanity/CoreSanityConfig.h"

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

class Config {
public:
    const static std::string GLOBAL_CONFIG_FNAME;

    bool is_help;
    int port;
    ILogger::Level log_level;

    CoreMsgConfig core_msg_config;
    CoreSanityConfig core_sanity_config;

    Config() {
        is_help = false;
        port = 12398;
        log_level = ILogger::Level::Info;
        core_msg_config = CoreMsgConfig();
        core_sanity_config = CoreSanityConfig();
    }

    void from_args(int argc, char** argv);
    void from_file();
};