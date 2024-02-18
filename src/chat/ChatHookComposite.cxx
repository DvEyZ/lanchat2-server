#include "ChatHookComposite.h"

void ChatHookComposite::on_message_push(
    Message message, 
    std::function<void(Message)> proceed,
    std::function<void(Rejection, Message)> reject
) {
    for(auto i : this->hooks) {
        bool rejected = false;
        Rejection rejection;
        i->on_message_push(message, [] (auto msg) {}, [&rejected, &rejection] (auto r, auto msg) {
            rejected = true;
            rejection = r;
        });

        if(rejected) {
            reject(rejection, message);
            return;
        }
    }
    proceed(message);
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

void ChatHookComposite::on_handler_subscribe(
    SubscribeRequest req,
    std::function<void(SubscribeRequest)> proceed,
    std::function<void(Rejection, SubscribeRequest)> reject
) {
    for(auto i : this->hooks) {
        bool rejected = false;
        Rejection rejection;
        i->on_handler_subscribe(req, [] (auto req) {}, [&rejected, &rejection] (auto r, auto req) {
            rejected = true;
            rejection = r;
        });

        if(rejected) {
            reject(rejection, req);
            return;
        }
    }
    proceed(req);
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

void ChatHookComposite::on_handler_match(
    Message message, 
    ChatHandle handle, 
    std::function<void(Message, ChatHandle)> proceed,
    std::function<void(Rejection, Message, ChatHandle)> reject
) {
    for(auto i : this->hooks) {
        bool rejected = false;
        Rejection rejection;
        i->on_handler_match(message, handle, [] (auto msg, auto h) {}, [&rejected, &rejection] (auto r, auto msg, auto h) {
            rejected = true;
            rejection = r;
        });

        if(rejected) {
            reject(rejection, message, handle);
            return;
        }
    }
    proceed(message, handle);
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