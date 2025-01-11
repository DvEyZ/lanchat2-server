#pragma once
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CoreSanityConfig {
public:
    bool active;
    bool reject_to_internal;
    bool reject_from_group_handle;

    CoreSanityConfig()
        :active(true), reject_to_internal(true), reject_from_group_handle(true)
    {}

    CoreSanityConfig(json j) 
        :active(true), reject_to_internal(true), reject_from_group_handle(true)
    {
        if(j.contains(json::json_pointer("active"))) 
            this->active = j["active"].get<bool>();

        if(j.contains(json::json_pointer("reject_to_internal"))) 
            this->active = j["reject_to_internal"].get<bool>();
            
        if(j.contains(json::json_pointer("reject_from_group_handle"))) 
            this->active = j["reject_from_group_handle"].get<bool>();

    }

    ~CoreSanityConfig() {}
};