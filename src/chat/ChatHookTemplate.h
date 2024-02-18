#pragma once
#include "IChatHook.h"

class ChatHookTemplate : public IChatHook {
public:
    ChatHookTemplate() {}
    virtual ~ChatHookTemplate() {}

    virtual void on_message_push(
        Message message, 
        std::function<void(Message)> proceed,
        std::function<void(Rejection, Message)> reject
    ) { proceed(message); };

    virtual void on_message_pushed(
        Message message
    ) {};

    virtual void on_message_push_rejected(
        Rejection rejection,
        Message message
    ) {};
    
    virtual void on_handler_subscribe(
        SubscribeRequest req,
        std::function<void(SubscribeRequest)> proceed,
        std::function<void(Rejection, SubscribeRequest)> reject
    ) { proceed(req); };

    virtual void on_handler_subscribed(
        SubscribeRequest req
    ) {};

    virtual void on_handler_subscribe_rejected(
        Rejection rejection,
        SubscribeRequest req
    ) {};

    virtual void on_handler_match(
        Message message, 
        ChatHandle handle, 
        std::function<void(Message, ChatHandle)> proceed,
        std::function<void(Rejection, Message, ChatHandle)> reject
    ) { proceed(message, handle); };

    virtual void on_handler_matched(
        Message message,
        ChatHandle handle
    ) {};

    virtual void on_handler_match_rejected(
        Rejection rejection,
        Message message,
        ChatHandle handle
    ) {};

    virtual void on_handler_expired(
        Message message, 
        ChatHandle handle
    ) {};
};