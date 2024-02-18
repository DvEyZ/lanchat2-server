#pragma once
#include <nlohmann/json.hpp>
#include <optional>

using json = nlohmann::json;

class CoreMsgConfig
{
public:
    bool active;
    bool on_message_pushed;
    bool on_message_push_rejected;
    bool on_handler_subscribed;
    bool on_handler_subscribe_rejected;

    CoreMsgConfig() 
        :active(true), on_message_pushed(true), on_message_push_rejected(true), on_handler_subscribed(true), on_handler_subscribe_rejected(true)
    {}

    CoreMsgConfig(json j) 
        :active(true), on_message_pushed(true), on_message_push_rejected(true), on_handler_subscribed(true), on_handler_subscribe_rejected(true)
    {
        if(j.contains("active")) this->active = j["active"].get<bool>();
        if(j.contains("on_message_pushed")) this->on_message_pushed = j["on_message_pushed"].get<bool>();
        if(j.contains("on_message_push_rejected")) this->on_message_push_rejected = j["on_message_push_rejected"].get<bool>();
        if(j.contains("on_handler_subscribed")) this->on_handler_subscribed = j["on_handler_subscribed"].get<bool>();
        if(j.contains("on_handler_subscribe_rejected")) this->on_handler_subscribe_rejected = j["on_handler_subscribe_rejected"].get<bool>();
    }

    ~CoreMsgConfig() {}
};