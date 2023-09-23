#include "Config.h"

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
            !strcmp(argv[i], "--config-file")
        ) {
            int nxt = ++i;
            if(nxt >= argc) {
                throw ConfigError("--config-file must be a file name");
            }
            this->config_fname = argv[nxt];
        }
        else {
            throw ConfigError("unrecognized parameter");
        }
    }
}

void Config::from_file() {
    auto config_file = std::fstream(this->config_fname, std::ios::in);
    if(!config_file.good()) {
        throw ConfigWarning("no config file found");
    }

    json config;
    config_file >> config;
    
    if(config.contains("port")) {
        this->port = config["port"].get<int>();
    }
    if(config.contains("log_level")) {
        auto lv = config["port"].get<std::string>();

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
}