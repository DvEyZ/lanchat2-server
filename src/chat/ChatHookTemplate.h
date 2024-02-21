#pragma once
#include "IChatHook.h"

class ChatHookTemplate : public IChatHook {
public:
    ChatHookTemplate() {}
    virtual ~ChatHookTemplate() {}

    virtual ChatHookResult on_message_push(
        Message message
    ) { return ChatHookResult::accepted(); };

    virtual void on_message_pushed(
        Message message
    ) {};

    virtual void on_message_push_rejected(
        Rejection rejection,
        Message message
    ) {};
    
    virtual ChatHookResult on_handler_subscribe(
        SubscribeRequest req
    ) { return ChatHookResult::accepted(); };

    virtual void on_handler_subscribed(
        SubscribeRequest req
    ) {};

    virtual void on_handler_subscribe_rejected(
        Rejection rejection,
        SubscribeRequest req
    ) {};

    virtual ChatHookResult on_handler_match(
        Message message, 
        ChatHandle handle
    ) { return ChatHookResult::accepted(); };

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