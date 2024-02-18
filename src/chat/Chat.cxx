#include "Chat.h"
#include "ChatHookComposite.h"

void Chat::push_message(Message m) {
    this->chat_lock.lock();
    this->logger->debug("message to " + m.handle_to.to_descriptor() + " pushed");

    auto hooks = ChatHookComposite(this->hooks);

    hooks.on_message_push(std::move(m), [this, &hooks] (Message m) {  // HOOK POINT on_message_push
        auto [i, end] = this->handlers.equal_range(m.handle_to);

        for(;i != end; i++) {
            ChatHandle h = i->first;
            
            if(i->second.expired()) {
                hooks.on_handler_expired(std::move(m), h);  // HOOK POINT on_handler_expired
                this->handlers.erase(i);
                this->logger->debug("handler at " + h.to_descriptor() + " removed");
            } else {
                hooks.on_handler_match(std::move(m), h, [this, &hooks, &i] (Message m, ChatHandle h) {    // HOOK POINT on_handler_match
                    auto handler = i->second.lock();
                    this->logger->debug("message passed to " + h.to_descriptor());
                    handler->handle_message(m);

                    hooks.on_handler_matched(m, h); // HOOK POINT on_handler_matched
                }, [this, &hooks] (Rejection r, Message m, ChatHandle h) {
                    this->logger->info("message reception by " + h.to_descriptor() + " rejected by " + r.hook + ", reason: " + r.what);

                    hooks.on_handler_match_rejected(r, m, h);   // HOOK POINT on_handler_match_rejected
                });
            }
        }

        hooks.on_message_pushed(m); // HOOK POINT on_message_pushed
    }, [this, &hooks] (Rejection r, Message m) {
        this->logger->info("message rejected by " + r.hook + ", reason: " + r.what);
        hooks.on_message_push_rejected(r, m); // HOOK POINT on_message_push_rejected
    });
    
    this->chat_lock.unlock();
}

void Chat::subscribe(SubscribeRequest r, std::weak_ptr<IChatHandler> handler) {
    this->chat_lock.lock();

    auto hooks = ChatHookComposite(this->hooks);
    hooks.on_handler_subscribe(r, [this, r, handler, &hooks] (SubscribeRequest req) {  // HOOK POINT on_handler_subscribe
        this->handlers.insert({ r.handle_to, handler });
        hooks.on_handler_subscribed(req); // HOOK POINT on_handler_subscribed
        this->logger->debug(req.handle_as.to_descriptor() + " subscribed to " + req.handle_to.to_descriptor());
    }, [this, &hooks] (Rejection r, SubscribeRequest req) {
        hooks.on_handler_subscribe_rejected(r, req); // HOOK POINT on_handler_subscribe rejected
        this->logger->info("subscription to " + req.handle_to.to_descriptor() + " rejected by " + r.hook + ", reason: " + r.what);
    });
    
    this->chat_lock.unlock();
}