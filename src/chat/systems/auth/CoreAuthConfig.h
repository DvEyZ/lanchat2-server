#pragma once
#include <nlohmann/json.hpp>
#include "../../../ConfigError.h"

using json = nlohmann::json;

class CoreAuthConfig {
public:
    enum class ProviderType {
        File
    };

    bool active;
    ProviderType provider;

    CoreAuthConfig()
        :active(false)
    {}

    CoreAuthConfig(json j) 
        :active(false)
    {
        if(j.contains(json::json_pointer("active"))) {
            this->active = j["active"].get<bool>();
            return;
        }

        if(j.contains(json::json_pointer("provider"))) {
            std::string provider = j["provider"].get<std::string>();
            if(provider == "file") {
                this->provider = ProviderType::File;
            } else {
                throw new ConfigError("unsupported core:auth provider");
            }
        }
    }
};