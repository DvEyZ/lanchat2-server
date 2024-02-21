#pragma once
#include "IChatHook.h"

class ChatHookComposite : public IChatHook {
private:
    std::vector<std::shared_ptr<IChatHook>>& hooks;
public:
    ChatHookComposite(std::vector<std::shared_ptr<IChatHook>>& hooks) :hooks(hooks) {}
    ~ChatHookComposite() {}

    virtual ChatHookResult on_message_push(
        Message message
    );

    virtual void on_message_pushed(
        Message message
    );

    virtual void on_message_push_rejected(
        Rejection rejection,
        Message message
    );
    
    virtual ChatHookResult on_handler_subscribe(
        SubscribeRequest req
    );

    virtual void on_handler_subscribed(
        SubscribeRequest req
    );

    virtual void on_handler_subscribe_rejected(
        Rejection rejection,
        SubscribeRequest req
    );

    virtual ChatHookResult on_handler_match(
        Message message, 
        ChatHandle handle
    );

    virtual void on_handler_matched(
        Message message,
        ChatHandle handle
    );

    virtual void on_handler_match_rejected(
        Rejection rejection,
        Message message,
        ChatHandle handle
    );

    virtual void on_handler_expired(
        Message message, 
        ChatHandle handle
    );
};