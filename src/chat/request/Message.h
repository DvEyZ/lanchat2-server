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
    const ChatHandle handle_from;
    const ChatHandle handle_to;

    const std::map<std::string, std::string> extensions;

    const std::optional<std::string> body;

    Message(json j) 
        :handle_from(ChatHandle::from_descriptor(j["from"].get<std::string>())),
        handle_to(ChatHandle::from_descriptor(j["to"].get<std::string>())),
        extensions(j["extensions"].get<std::map<std::string, std::string>>()),
        body(j["body"].get<std::optional<std::string>>())
    {}

    virtual ~Message() {}

    virtual void accept_visitor(IRequestVisitor& v) {
        v.visit(*this);
    }
};