#pragma once
#include <exception>
#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include "Message.h"
#include "SubscribeRequest.h"

using json = nlohmann::json;

class RequestFactoryError : public std::exception {
    std::string wat;
public:
    RequestFactoryError(std::string what)
        :wat(what) 
    {}
    ~RequestFactoryError() {}

    const char* what() {
        return this->wat.c_str();
    }
};

std::unique_ptr<IRequest> request_factory(json j, ChatHandle def);