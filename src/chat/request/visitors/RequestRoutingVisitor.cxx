#include "RequestRoutingVisitor.h"
#include "../Message.h"
#include "../SubscribeRequest.h"

void RequestRoutingVisitor::visit(Message msg) {
    this->chat->push_message(msg);
}

void RequestRoutingVisitor::visit(SubscribeRequest req) {
    this->chat->subscribe(req, this->handler);
}