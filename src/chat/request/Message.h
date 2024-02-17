#pragma once
#include <map>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include "ChatHandle.h"
#include "IRequest.h"
#include "IRequestVisitor.h"

using json = nlohmann::json;

class Message : public IRequest {
public:
    ChatHandle handle_from;
    ChatHandle handle_to;

    std::map<std::string, std::string> extensions;

    std::optional<std::string> body;

    Message(json j, ChatHandle def) 
        :handle_to(ChatHandle::from_descriptor(j["to"].get<std::string>())),
        extensions(j["extensions"].get<std::map<std::string, std::string>>()),
        body(j["body"].get<std::optional<std::string>>())
    {
        if(j.contains("from")) {
            this->handle_from = ChatHandle::from_descriptor(j["from"].get<std::string>());
        } else {
            this->handle_from = def;
        }
    }

    virtual ~Message() {}

    virtual void accept_visitor(IRequestVisitor& v) {
        v.visit(*this);
    }
};