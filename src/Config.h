#pragma once

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "ConfigError.h"
#include "loggers/ILogger.h"
#include "chat/systems/msg/CoreMsgConfig.h"
#include "chat/systems/sanity/CoreSanityConfig.h"
#include "chat/systems/auth/CoreAuthConfig.h"

using json = nlohmann::json;


class Config {
public:
    const static std::string GLOBAL_CONFIG_FNAME;

    bool is_help;
    int port;
    ILogger::Level log_level;

    CoreMsgConfig core_msg_config;
    CoreSanityConfig core_sanity_config;
    CoreAuthConfig core_auth_config;

    Config() {
        is_help = false;
        port = 12398;
        log_level = ILogger::Level::Info;
        core_msg_config = CoreMsgConfig();
        core_sanity_config = CoreSanityConfig();
        core_auth_config = CoreAuthConfig();
    }

    void from_args(int argc, char** argv);
    void from_file();
};