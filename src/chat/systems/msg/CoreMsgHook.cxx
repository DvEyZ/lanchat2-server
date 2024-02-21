#include "CoreMsgHook.h"
#include "../../../utils/uuid.h"

void CoreMsgHook::on_message_pushed(Message message) {
    if(message.internal_from.type == ChatHandle::Type::System) return;

    auto msg = Message(
        generate_uuidv4(), 
        this->handle, 
        this->handle, 
        message.internal_from, 
        {
            { "res_to", message.req_id },
            { "status", "Completed" }
        }, 
        "message delivered"
    );
    this->chat->push_message(msg);
}

void CoreMsgHook::on_message_push_rejected(Rejection rejection, Message message) {
    if(message.internal_from.type == ChatHandle::Type::System) return;

    auto msg = Message(
        generate_uuidv4(),
        this->handle,
        this->handle, 
        message.internal_from, 
        {
            { "res_to", message.req_id },
            { "status", "Failed" }
        }, 
        rejection.hook + ": failed to push message: " + rejection.what
    );
    this->chat->push_message(msg);
}

void CoreMsgHook::on_handler_subscribed(SubscribeRequest req) {
    auto msg = Message(
        generate_uuidv4(), 
        this->handle, 
        this->handle, 
        req.internal_as, 
        {
            { "res_to", req.req_id },
            { "status", "Completed" }
        }, 
        "subscribed to " + req.handle_to.to_descriptor()
    );
    this->chat->push_message(msg);
}

void CoreMsgHook::on_handler_subscribe_rejected(Rejection rejection, SubscribeRequest req) {
    auto msg = Message(
        generate_uuidv4(),
        this->handle,
        this->handle, 
        req.internal_as, 
        {
            { "res_to", req.req_id },
            { "status", "Failed" }
        }, 
        rejection.hook + ": failed to subscribe to " + req.handle_to.to_descriptor() + ": " + rejection.what
    );
    this->chat->push_message(msg);
}