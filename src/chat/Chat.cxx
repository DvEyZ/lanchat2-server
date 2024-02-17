#include "Chat.h"

void Chat::push_message(Message m) {
    this->handlers_mutex.lock();

    for(auto [i, end] = this->handlers.equal_range(m.handle_to); i != end; i++) {
        if(i->second.expired()) {
            this->handlers.erase(i);
        } else {
            auto h = i->second.lock();
            h->handle_message(m);
        }
    }
    
    this->handlers_mutex.unlock();
}

void Chat::subscribe(SubscribeRequest r, std::weak_ptr<IChatHandler> handler) {
    this->handlers_mutex.lock();
    this->handlers.insert({ r.handle , handler });
    this->handlers_mutex.unlock();
}