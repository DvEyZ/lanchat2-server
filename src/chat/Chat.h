#pragma once
#include <vector>
#include "IChat.h"
#include "IChatHook.h"
#include "../loggers/ILogger.h"

class Chat : public IChat
{
private:
    std::mutex chat_lock;  // makeshift sync solution, todo: asynchronize mutual exclusion
    std::multimap<ChatHandle, std::weak_ptr<IChatHandler>> handlers;
    std::vector<std::shared_ptr<IChatHook>> hooks;

    std::unique_ptr<ILogger> logger;
public:
    Chat(std::unique_ptr<ILogger> logger) 
        :logger(std::move(logger))
    {}
    virtual ~Chat() {}

    virtual void push_message(Message m);
    virtual void subscribe(SubscribeRequest r, std::weak_ptr<IChatHandler> handler);
};