#pragma once
#include <map>
#include <nlohmann/json.hpp>
#include "ChatHandle.h"
#include "IRequest.h"
#include "IRequestVisitor.h"

using json = nlohmann::json;

class SubscribeRequest : public IRequest {
public:
    ChatHandle handle_as;
    ChatHandle handle_to;
    std::map<std::string, std::string> extensions;

    SubscribeRequest() {};

    SubscribeRequest(json j, ChatHandle def)
        :handle_to(ChatHandle::from_descriptor(j["to"].get<std::string>())),
        extensions(j["extensions"].get<std::map<std::string, std::string>>())
    {
        if(j.contains("as")) {
            this->handle_as = ChatHandle::from_descriptor(j["as"].get<std::string>());
        } else {
            this->handle_as = def;
        }
    }
    
    virtual ~SubscribeRequest() {}

    virtual void accept_visitor(IRequestVisitor& v) {
        v.visit(*this);
    }
};