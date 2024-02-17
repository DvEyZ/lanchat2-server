#include "Chat.h"
#include "ChatHookComposite.h"

void Chat::push_message(Message m) {
    this->chat_lock.lock();

    auto hooks = ChatHookComposite(this->hooks);

    hooks.on_message_pushed(std::move(m), [this, &hooks] (Message m) {
        for(auto [i, end] = this->handlers.equal_range(m.handle_to); i != end; i++) {
            ChatHandle h = i->first;
            
            if(i->second.expired()) {
                hooks.on_handler_expired(std::move(m), h);
                this->handlers.erase(i);
            } else {
                hooks.on_handler_matched(std::move(m), h, [this, &hooks, &i] (Message m, ChatHandle _) {
                    auto handler = i->second.lock();
                    handler->handle_message(m);
                }, [this] (Rejection r, Message m, ChatHandle h) {
                    this->logger->info("message reception by " + h.to_descriptor() + " rejected by " + r.hook + ", reason: " + r.what);
                });
            }
        }
    }, [this] (Rejection r, Message m) {
        this->logger->info("message rejected by " + r.hook + ", reason: " + r.what);
    });
    
    this->chat_lock.unlock();
}

void Chat::subscribe(SubscribeRequest r, std::weak_ptr<IChatHandler> handler) {
    this->chat_lock.lock();

    auto hooks = ChatHookComposite(this->hooks);
    hooks.on_handler_subscribed(r, [this, r, handler] (SubscribeRequest req) {
        this->handlers.insert({ r.handle_as, handler });
    }, [this] (Rejection r, SubscribeRequest req) {
        this->logger->info("subscription to " + req.handle_to.to_descriptor() + " rejected by " + r.hook + ", reason: " + r.what);
    });
    
    this->chat_lock.unlock();
}