#include "Chat.h"
#include "ChatHookComposite.h"

void Chat::on_push_message(Message m) {
    this->logger->debug("message to " + m.handle_to.to_descriptor() + " pushed");

    auto hooks = ChatHookComposite(this->hooks);

    auto on_push = hooks.on_message_push(std::move(m)); // HOOK POINT on_message_push
    if(on_push.get_is_accepted())
    {
        auto [i, end] = this->handlers.equal_range(m.handle_to);

        for(;i != end; i++) {
            ChatHandle h = i->first;
            
            if(i->second.expired()) {
                hooks.on_handler_expired(std::move(m), h);  // HOOK POINT on_handler_expired
                this->handlers.erase(i);
                this->logger->debug("handler at " + h.to_descriptor() + " removed");
            } else {
                auto on_match = hooks.on_handler_match(m, h); // HOOK POINT on_handler_match

                if(on_match.get_is_accepted()) {    
                    auto handler = i->second.lock();
                    this->logger->debug("message passed to " + h.to_descriptor());
                    handler->handle_message(m);
                    hooks.on_handler_matched(m, h); // HOOK POINT on_handler_matched
                } else {
                    auto rej = on_match.get_rejection();
                    this->logger->info("message reception by " + h.to_descriptor() + " rejected by " + rej.hook + ", reason: " + rej.what);
                    hooks.on_handler_match_rejected(rej, m, h);   // HOOK POINT on_handler_match_rejected
                };
            }
        }

        hooks.on_message_pushed(m); // HOOK POINT on_message_pushed
    } else {
        auto rej = on_push.get_rejection();
        this->logger->info("message rejected by " + rej.hook + ", reason: " + rej.what);
        hooks.on_message_push_rejected(rej, m); // HOOK POINT on_message_push_rejected
    };
}

void Chat::on_subscribe(SubscribeRequest r, std::weak_ptr<IChatHandler> handler) {
    auto hooks = ChatHookComposite(this->hooks);
    auto on_subscribe = hooks.on_handler_subscribe(r);
    if(on_subscribe.get_is_accepted()) {  // HOOK POINT on_handler_subscribe
        this->handlers.insert({ r.handle_to, handler });
        hooks.on_handler_subscribed(r); // HOOK POINT on_handler_subscribed
        this->logger->debug(r.handle_as.to_descriptor() + " subscribed to " + r.handle_to.to_descriptor());
    } else {
        auto rej = on_subscribe.get_rejection();
        hooks.on_handler_subscribe_rejected(rej, r); // HOOK POINT on_handler_subscribe rejected
        this->logger->info("subscription to " + r.handle_to.to_descriptor() + " rejected by " + rej.hook + ", reason: " + rej.what);
    };
}

void Chat::push_message(Message m) {
    this->strand.wrap([this, m] () {
        this->on_push_message(m);  
    })();
}

void Chat::subscribe(SubscribeRequest r, std::weak_ptr<IChatHandler> handler) {
    this->strand.wrap([this, r, handler] () {
        this->on_subscribe(r, handler);
    })();
}

void Chat::attach_hook(std::shared_ptr<IChatHook> hook) {
    this->strand.wrap([this, hook] () {
        this->hooks.push_back(hook);
    })();
}