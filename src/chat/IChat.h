#pragma once
#include <nlohmann/json.hpp>
#include <functional>
#include "request/ChatHandle.h"
#include "IChatHandler.h"
#include "request/SubscribeRequest.h"

using json = nlohmann::json;

class IChat
{
public:
    virtual ~IChat() {}
    virtual void push_message(Message m) = 0;
    virtual void subscribe(SubscribeRequest r, std::weak_ptr<IChatHandler> handler) = 0;
    virtual void subscribe_internal(SubscribeRequest r, std::weak_ptr<IChatHandler> handler) = 0;
};