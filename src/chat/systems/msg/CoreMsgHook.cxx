#include "CoreMsgHook.h"

void CoreMsgHook::on_message_pushed(Message message) {
    if(message.handle_from.type == ChatHandle::Type::System) return;

    auto msg = Message(this->handle, message.handle_from, {}, "message delivered");
    this->chat->push_message(msg);
}

void CoreMsgHook::on_message_push_rejected(Rejection rejection, Message message) {
    if(message.handle_from.type == ChatHandle::Type::System) return;

    auto msg = Message(
        this->handle, 
        message.handle_from, 
        {}, 
        rejection.hook + ": failed to push message: " + rejection.what
    );
    this->chat->push_message(msg);
}

void CoreMsgHook::on_handler_subscribed(SubscribeRequest req) {
    auto msg = Message(this->handle, req.handle_to, {}, "subscribed to " + req.handle_to.to_descriptor());
    this->chat->push_message(msg);
}

void CoreMsgHook::on_handler_subscribe_rejected(Rejection rejection, SubscribeRequest req) {
    auto msg = Message(
        this->handle, 
        req.handle_as, 
        {}, 
        rejection.hook + ": failed to subscribe to " + req.handle_to.to_descriptor() + ": " + rejection.what
    );
    this->chat->push_message(msg);
}