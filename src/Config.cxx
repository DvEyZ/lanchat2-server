#include "Config.h"

const std::string Config::GLOBAL_CONFIG_FNAME = "lanchat2.json";

void Config::from_args(int argc, char** argv) {
    for(int i = 1; i < argc; i++) {
        if(
            !strcmp(argv[i], "-L") || !strcmp(argv[i], "--log-level")
        ) {
            int nxt = ++i;
            if(nxt >= argc) {
                throw ConfigError("--log-level must be one of: `debug`, `info`, `warn`, `err`");
            }
            if(!strcmp(argv[nxt], "debug")) {
                this->log_level = ILogger::Level::Debug;
            } else if(!strcmp(argv[nxt], "info")) {
                this->log_level = ILogger::Level::Info;
            } else if(!strcmp(argv[nxt], "warn")) {
                this->log_level = ILogger::Level::Warn;
            } else if(!strcmp(argv[nxt], "err")) {
                this->log_level = ILogger::Level::Err;
            } else {
                throw ConfigError("--log-level must be one of: `debug`, `info`, `warn`, `err`");
            }
        }
        else if(
            !strcmp(argv[i], "-p") || !strcmp(argv[i], "--port")
        ) {
            int nxt = ++i;
            if(nxt >= argc) {
                throw ConfigError("--port must be a number from 0 to 65535");
            }
            try {
                int p = std::stoi(argv[nxt]);
                if(p < 0 || p > 65535) {
                    throw ConfigError("--port must be a number from 0 to 65535");
                }
                this->port = p;
            } catch(std::invalid_argument& e) {
                throw ConfigError("--port must be a number from 0 to 65535");
            }
        }
        else if(
            !strcmp(argv[i], "-h") || !strcmp(argv[i], "-?") || !strcmp(argv[i], "--help")
        ) {
            this->is_help = true;
        }
        else {
            throw ConfigError("unrecognized parameter");
        }
    }
}

void Config::from_file() {
    auto global_config_file = std::fstream(Config::GLOBAL_CONFIG_FNAME, std::ios::in);
    if(!global_config_file.good()) {
        throw ConfigWarning("no global config file found");
    }

    json global_config;

    try {
        global_config_file >> global_config;
    } catch(json::exception& e) {
        throw ConfigError(e.what());
    }
    
    if(global_config.contains("port")) {
        this->port = global_config["port"].get<int>();
    }
    if(global_config.contains("log_level")) {
        auto lv = global_config["log_level"].get<std::string>();

        if(lv == "debug") {
            this->log_level = ILogger::Level::Debug;
        } else if(lv == "info") {
            this->log_level = ILogger::Level::Info;
        } else if(lv == "warn") {
            this->log_level = ILogger::Level::Warn;
        } else if(lv == "err") {
            this->log_level = ILogger::Level::Err;
        } else {
            throw ConfigError("log_level must be one of: `debug`, `info`, `warn`, `err`");
        }
    }
    if(global_config.contains("core_systems")) {
        json core_systems = global_config["core_systems"].get<json>();
        if(core_systems.contains("msg")) {
            this->core_msg_config = CoreMsgConfig(core_systems["msg"].get<json>());
        }
        if(core_systems.contains("sanity")) {
            this->core_sanity_config = CoreSanityConfig(core_systems["sanity"].get<json>());
        }
        if(core_systems.contains("auth")) {
            this->core_auth_config = CoreAuthConfig(core_systems["auth"].get<json>());
        }
    }
}