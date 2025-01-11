#include "request_factory.h"

std::unique_ptr<IRequest> request_factory(json j, ChatHandle def) {
    std::string type = j["type"].get<std::string>();

    if(type == "message") {
        return std::make_unique<Message>(Message(j, def));
    } else if(type == "subscribe") {
        return std::make_unique<SubscribeRequest>(SubscribeRequest(j, def));
    } else if( type == "unsubscribe" ) {
        return std::make_unique<UnsubscribeRequest>(UnsubscribeRequest(j, def));
    } else {
        throw RequestFactoryError("unsupported request type");
    }
}