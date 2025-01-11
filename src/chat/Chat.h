#pragma once
#include <vector>
#include <queue>
#include "IChat.h"
#include "IChatHook.h"
#include "../loggers/ILogger.h"
#include <asio.hpp>

class Chat : public IChat
{
private:
    asio::io_context::strand strand;

    std::multimap<ChatHandle, std::weak_ptr<IChatHandler>> handlers;
    std::vector<std::shared_ptr<IChatHook>> hooks;

    std::unique_ptr<ILogger> logger;

    void on_push_message(Message m);
    void on_subscribe(SubscribeRequest r, std::weak_ptr<IChatHandler> handler);
    void on_subscribe_internal(SubscribeRequest r, std::weak_ptr<IChatHandler> handler);
public:
    Chat(std::unique_ptr<ILogger> logger, asio::io_context::strand strand) 
        :logger(std::move(logger)), strand(strand)
    {}
    virtual ~Chat() {}

    void attach_hook(std::shared_ptr<IChatHook> hook);

    virtual void push_message(Message m);
    virtual void subscribe(SubscribeRequest r, std::weak_ptr<IChatHandler> handler);

    /// like `Chat::subscribe`, but without `on_handler_subscribe` hook
    /// use for internal subscriptions
    virtual void subscribe_internal(SubscribeRequest r, std::weak_ptr<IChatHandler> handler);
};