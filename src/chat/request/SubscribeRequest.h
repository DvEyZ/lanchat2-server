#pragma once
#include <map>
#include <nlohmann/json.hpp>
#include "ChatHandle.h"
#include "IRequest.h"
#include "IRequestVisitor.h"

using json = nlohmann::json;

class SubscribeRequest : public IRequest {
public:
    std::string req_id;

    ChatHandle internal_as;
    ChatHandle handle_as;
    ChatHandle handle_to;
    std::map<std::string, std::string> extensions;

    SubscribeRequest() {};

    SubscribeRequest(json j, ChatHandle internal_as)
        :req_id(j["id"].get<std::string>()),
        internal_as(internal_as),
        handle_to(ChatHandle::from_descriptor(j["to"].get<std::string>())),
        extensions(j["extensions"].get<std::map<std::string, std::string>>())
    {
        if(j.contains("as")) {
            this->handle_as = ChatHandle::from_descriptor(j["as"].get<std::string>());
        } else {
            this->handle_as = internal_as;
        }
    }

    SubscribeRequest(std::string req_id, ChatHandle internal_as, ChatHandle handle_as, ChatHandle handle_to, std::map<std::string, std::string> extensions) 
        :req_id(req_id), internal_as(internal_as), handle_as(handle_as), handle_to(handle_to), extensions(extensions)
    {}
    
    virtual ~SubscribeRequest() {}

    virtual void accept_visitor(IRequestVisitor& v) {
        v.visit(*this);
    }
};