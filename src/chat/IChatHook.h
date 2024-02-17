#pragma once
#include <functional>
#include "request/Message.h"
#include "request/SubscribeRequest.h"

struct Rejection {
    std::string hook;
    std::string what;
};

class IChatHook {
public:
    virtual ~IChatHook() {};
    virtual void on_message_pushed(
        Message message, 
        std::function<void(Message)> proceed,
        std::function<void(Rejection, Message)> reject
    ) = 0;
    
    virtual void on_handler_subscribed(
        SubscribeRequest req,
        std::function<void(SubscribeRequest)> proceed,
        std::function<void(Rejection, SubscribeRequest)> reject
    ) = 0;

    virtual void on_handler_matched(
        Message message, 
        ChatHandle handle, 
        std::function<void(Message, ChatHandle)> proceed,
        std::function<void(Rejection, Message, ChatHandle)> reject
    ) = 0;

    virtual void on_handler_expired(
        Message message, 
        ChatHandle handle
    ) = 0;
};