#pragma once
#include <map>
#include <nlohmann/json.hpp>
#include "ChatHandle.h"
#include "IRequest.h"
#include "IRequestVisitor.h"

using json = nlohmann::json;

class UnsubscribeRequest : public IRequest {
public:
    std::string req_id;

    ChatHandle internal_as;
    ChatHandle handle_as;
    ChatHandle handle_from;
    std::map<std::string, std::string> extensions;

    UnsubscribeRequest() {}

    UnsubscribeRequest(json j, ChatHandle internal_as) 
        :req_id(j["id"].get<std::string>()),
        internal_as(internal_as),
        handle_from(ChatHandle::from_descriptor(j["from"].get<std::string>())),
        extensions(j["extensions"].get<std::map<std::string, std::string>>())
    {
        if(j.contains("as")) {
            this->handle_as = ChatHandle::from_descriptor(j["as"].get<std::string>());
        } else {
            this->handle_as = internal_as;
        }
    }

    virtual ~UnsubscribeRequest() {}

    virtual void accept_visitor(IRequestVisitor& v) {
        v.visit(*this);
    }
};