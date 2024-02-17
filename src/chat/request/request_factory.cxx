#include "request_factory.h"

std::unique_ptr<IRequest> request_factory(json j) {
    std::string type = j["type"].get<std::string>();

    if(type == "message") {
        return std::make_unique<Message>(Message(j));
    } else if(type == "subscribe") {
        return std::make_unique<SubscribeRequest>(SubscribeRequest(j));
    } else {
        throw RequestFactoryError("unsupported request type");
    }
}