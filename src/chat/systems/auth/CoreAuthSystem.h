#pragma once
#include <map>
#include "../../ChatHookTemplate.h"
#include "../../IChatHandler.h"
#include "CoreAuthConfig.h"
#include "../../../loggers/ILogger.h"
#include "../../IChat.h"
#include "IAuthProvider.h"
#include "../../../utils/uuid.h"

class CoreAuthSystem : public ChatHookTemplate, public IChatHandler {
private:
    CoreAuthConfig config;
    std::unique_ptr<ILogger> logger;

    ChatHandle handle;
    std::shared_ptr<IChat> chat;
    std::map<ChatHandle, std::string> auth_keys;
    std::unique_ptr<IAuthProvider> auth_provider;

    Message send_failure_message(Message res_to, std::string body);
    std::string generate_token();
public:
    CoreAuthSystem(CoreAuthConfig config, std::unique_ptr<ILogger> logger)  
        :config(config), logger(std::move(logger))
    {}
    ~CoreAuthSystem() {};

    // impl IChatHandler
    virtual void handle_message(Message message);

    // impl ChatHookTemplate
    virtual ChatHookResult on_message_push(Message m);
    // impl ChatHookTemplate
    virtual ChatHookResult on_handler_subscribe(SubscribeRequest req);
};