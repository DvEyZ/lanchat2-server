#pragma once

class Message;
class SubscribeRequest;

class IRequestVisitor {
public:
    virtual ~IRequestVisitor() {};
    virtual void visit(Message message) = 0;
    virtual void visit(SubscribeRequest req) = 0;
};