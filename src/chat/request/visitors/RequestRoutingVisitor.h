#pragma once
#include <memory>
#include "../IRequestVisitor.h"
#include "../../IChat.h"

class RequestRoutingVisitor : public IRequestVisitor {
private:
    std::shared_ptr<IChat> chat;
    std::shared_ptr<IChatHandler> handler;
public:
    RequestRoutingVisitor(std::shared_ptr<IChat> chat, std::shared_ptr<IChatHandler> handler)
        :chat(chat), handler(handler)
    {}
    virtual ~RequestRoutingVisitor() {}

    virtual void visit(Message msg);
    virtual void visit(SubscribeRequest req);
    virtual void visit(UnsubscribeRequest req);
};