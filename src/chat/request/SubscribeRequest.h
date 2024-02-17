#pragma once
#include <map>
#include <nlohmann/json.hpp>
#include "ChatHandle.h"
#include "IRequest.h"
#include "IRequestVisitor.h"

using json = nlohmann::json;

class SubscribeRequest : public IRequest {
public:
    const ChatHandle handle;
    const std::map<std::string, std::string> extensions;

    SubscribeRequest(json j)
        :handle(ChatHandle::from_descriptor(j["handle"].get<std::string>())),
        extensions(j["extensions"].get<std::map<std::string, std::string>>())
    {}
    
    virtual ~SubscribeRequest() {}

    virtual void accept_visitor(IRequestVisitor& v) {
        v.visit(*this);
    }
};