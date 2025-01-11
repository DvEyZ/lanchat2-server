#include "CoreAuthSystem.h"

Message CoreAuthSystem::send_failure_message(Message res_to, std::string body) {
    auto msg = Message(
        generate_uuidv4(), 
        this->handle, 
        this->handle, 
        res_to.internal_from, 
        {
            { "core:res_to", res_to.req_id },
            { "core:auth:type", "err"}
        },
        body
    );
    this->chat->push_message(msg);
}

std::string CoreAuthSystem::generate_token() {
    return generate_uuidv4();   // MAKESHIFT
}

void CoreAuthSystem::handle_message(Message message) {
    if(!message.extensions.contains("core:auth:type")) {
        this->send_failure_message(message, "`core:auth:type` not specified");
        return;
    }

    auto type = message.extensions["core:auth:type"];

    if(type == "core:auth:pass_auth") {
        if(!message.extensions.contains("core:auth:user_handle") || !message.extensions.contains("core:auth:pass_auth:password")) {
            this->send_failure_message(message, "bad message format");
            return;
        }

        auto handle = ChatHandle::from_descriptor(message.extensions["core:auth:user_handle"]);
        if(handle.type != ChatHandle::Type::User) {
            this->send_failure_message(message, "`core:auth:user_handle` must be an user handle");
            return;
        }
        auto password = message.extensions["core:auth:pass_auth:password"];
        auto result = this->auth_provider->authenticate(handle, password);

        
    } else {
        this->send_failure_message(message, "unsupported type");
        return;
    }
}

ChatHookResult CoreAuthSystem::on_message_push(Message m) {
    
}

ChatHookResult CoreAuthSystem::on_handler_subscribe(SubscribeRequest req) {
    
}