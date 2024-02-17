#pragma once
#include "IChat.h"

class Chat : public IChat
{
private:
    std::mutex handlers_mutex;  // makeshift sync solution, todo: asynchronize mutual exclusion
    std::multimap<ChatHandle, std::weak_ptr<IChatHandler>> handlers;
public:
    Chat() {}
    virtual ~Chat() {}

    virtual void push_message(Message m);
    virtual void subscribe(SubscribeRequest r, std::weak_ptr<IChatHandler> handler);
};