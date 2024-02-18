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

    json to_json() {
        json json;
        if(this->handle_from.type != ChatHandle::Type::Internal) {
            json["from"] = this->handle_from.to_descriptor();
        }
        if(this->handle_to.type != ChatHandle::Type::Internal) {
            json["to"] = this->handle_to.to_descriptor();
        }
        json["extensions"] = this->extensions;
        if(this->body.has_value()) {
            json["body"] = this->body.value();
        }
        return json;
    }

    virtual void accept_visitor(IRequestVisitor& v) {
        v.visit(*this);
    }
};