#pragma once
#include "../../ChatHookTemplate.h"
#include "../../IChat.h"
#include "CoreMsgConfig.h"
#include "../../../loggers/ILogger.h"

class CoreMsgHook : public ChatHookTemplate {
private:
    ChatHandle handle;
    std::shared_ptr<IChat> chat;
    CoreMsgConfig config;
    std::unique_ptr<ILogger> logger;
public:
    CoreMsgHook(std::shared_ptr<IChat> chat, ChatHandle handle, CoreMsgConfig config, std::unique_ptr<ILogger> logger)
        :chat(chat), handle(handle), config(config), logger(std::move(logger))
    {
        this->logger->debug("initialized with handle " + this->handle.to_descriptor());
    }
    virtual ~CoreMsgHook() {}

    // impl ChatHookTemplate
    virtual void on_message_pushed(
        Message message
    );

    // impl ChatHookTemplate
    virtual void on_message_push_rejected(
        Rejection rejection,
        Message message
    ); 

    // impl ChatHookTemplate
    virtual void on_handler_subscribed(
        SubscribeRequest req
    );

    // impl ChatHookTemplate
    virtual void on_handler_subscribe_rejected(
        Rejection rejection,
        SubscribeRequest req
    );
};