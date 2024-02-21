#include "ChatHookComposite.h"

ChatHookResult ChatHookComposite::on_message_push(
    Message message
) {
    for(auto i : this->hooks) {
        auto r = i->on_message_push(message);
        if(!r.get_is_accepted()) {
            return r;
        }
    }
    return ChatHookResult::accepted();
}

void ChatHookComposite::on_message_pushed(Message message) {
    for(auto i : this->hooks) {
        i->on_message_pushed(message);
    }
}

void ChatHookComposite::on_message_push_rejected(Rejection rejection, Message message) {
    for(auto i : this->hooks) {
        i->on_message_push_rejected(rejection, message);
    }
}

ChatHookResult ChatHookComposite::on_handler_subscribe(
    SubscribeRequest req
) {
    for(auto i : this->hooks) {
        auto r = i->on_handler_subscribe(req);
        if(!r.get_is_accepted()) {
            return r;
        }
    }
    return ChatHookResult::accepted();
}

void ChatHookComposite::on_handler_subscribed(SubscribeRequest req) {
    for(auto i : this->hooks) {
        i->on_handler_subscribed(req);
    }
}

void ChatHookComposite::on_handler_subscribe_rejected(Rejection rejection, SubscribeRequest req) {
    for(auto i : this->hooks) {
        i->on_handler_subscribe_rejected(rejection, req);
    }
}

ChatHookResult ChatHookComposite::on_handler_match(
    Message message, 
    ChatHandle handle
) {
    for(auto i : this->hooks) {
        auto r = i->on_handler_match(message, handle);
        if(!r.get_is_accepted()) {
            return r;
        }
    }
    return ChatHookResult::accepted();
}

void ChatHookComposite::on_handler_matched(Message message, ChatHandle handle) {
    for(auto i : this->hooks) {
        i->on_handler_matched(message, handle);
    }
}

void ChatHookComposite::on_handler_match_rejected(Rejection rejection, Message message, ChatHandle handle) {
    for(auto i : this->hooks) {
        i->on_handler_match_rejected(rejection, message, handle);
    }
}

void ChatHookComposite::on_handler_expired(
    Message message, 
    ChatHandle handle
) {
    for(auto i : this->hooks) {
        i->on_handler_expired(message, handle);
    }
}