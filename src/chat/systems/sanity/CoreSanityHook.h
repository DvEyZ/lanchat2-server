#pragma once
#include "../../ChatHookTemplate.h"
#include "../../../loggers/ILogger.h"
#include "CoreSanityConfig.h"

class CoreSanityHook : public ChatHookTemplate {
private:
    ChatHandle handle;
    CoreSanityConfig config;
    std::unique_ptr<ILogger> logger;
public:
    CoreSanityHook(ChatHandle handle, CoreSanityConfig config, std::unique_ptr<ILogger> logger) 
        :handle(handle), config(config), logger(std::move(logger))
    {
        this->logger->debug("initialized with handle " + this->handle.to_descriptor());
    }

    virtual ~CoreSanityHook() {}

    virtual ChatHookResult on_message_push(
        Message message
    );
};