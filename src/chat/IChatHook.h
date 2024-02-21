#pragma once
#include <functional>
#include "request/Message.h"
#include "request/SubscribeRequest.h"

struct Rejection {
    std::string hook;
    std::string what;
};

class ChatHookResult {
private:
    bool is_accepted;
    Rejection rejection;
    ChatHookResult(bool accepted, Rejection rejection)
        :is_accepted(accepted), rejection(rejection)
    {}
    ChatHookResult() {};
public:
    static ChatHookResult accepted() {
        ChatHookResult res;
        res.is_accepted = true;
        return res;
    }

    static ChatHookResult rejected(Rejection rejection) {
        ChatHookResult res;
        res.is_accepted = false;
        res.rejection = rejection;
        return res;
    };

    bool get_is_accepted() {
        return this->is_accepted;
    }

    Rejection get_rejection() {
        return this->rejection;
    }
};

class IChatHook {
public:
    virtual ~IChatHook() {};
    virtual ChatHookResult on_message_push(
        Message message
    ) = 0;

    virtual void on_message_pushed(
        Message message
    ) = 0;

    virtual void on_message_push_rejected(
        Rejection rejection,
        Message message
    ) = 0;
    
    virtual ChatHookResult on_handler_subscribe(
        SubscribeRequest req
    ) = 0;

    virtual void on_handler_subscribed(
        SubscribeRequest req
    ) = 0;

    virtual void on_handler_subscribe_rejected(
        Rejection rejection,
        SubscribeRequest req
    ) = 0;

    virtual ChatHookResult on_handler_match(
        Message message, 
        ChatHandle handle
    ) = 0;

    virtual void on_handler_matched(
        Message message,
        ChatHandle handle
    ) = 0;

    virtual void on_handler_match_rejected(
        Rejection rejection,
        Message message,
        ChatHandle handle
    ) = 0;

    virtual void on_handler_expired(
        Message message, 
        ChatHandle handle
    ) = 0;
};