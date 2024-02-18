#pragma once
#include "IChatHook.h"

class ChatHookComposite : public IChatHook {
private:
    std::vector<std::shared_ptr<IChatHook>>& hooks;
public:
    ChatHookComposite(std::vector<std::shared_ptr<IChatHook>>& hooks) :hooks(hooks) {}
    ~ChatHookComposite() {}

    virtual void on_message_push(
        Message message, 
        std::function<void(Message)> proceed,
        std::function<void(Rejection, Message)> reject
    );

    virtual void on_message_pushed(
        Message message
    );

    virtual void on_message_push_rejected(
        Rejection rejection,
        Message message
    );
    
    virtual void on_handler_subscribe(
        SubscribeRequest req,
        std::function<void(SubscribeRequest)> proceed,
        std::function<void(Rejection, SubscribeRequest)> reject
    );

    virtual void on_handler_subscribed(
        SubscribeRequest req
    );

    virtual void on_handler_subscribe_rejected(
        Rejection rejection,
        SubscribeRequest req
    );

    virtual void on_handler_match(
        Message message, 
        ChatHandle handle, 
        std::function<void(Message, ChatHandle)> proceed,
        std::function<void(Rejection, Message, ChatHandle)> reject
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