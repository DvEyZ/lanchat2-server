#include "ChatHandle.h"

ChatHandle ChatHandle::from_descriptor(std::string descriptor) {
    char type_char = descriptor.at(0);
    std::string name = descriptor.substr(1, descriptor.length() - 1);
    Type type;

    if(type_char == '@') type = Type::User;
    else if(type_char == '#') type = Type::Group;
    else type = Type::System;

    return ChatHandle(name, type);
}

std::string ChatHandle::to_descriptor() {
    std::string descriptor;

    if(this->type == Type::User) descriptor += "@";
    else if(this->type == Type::Group) descriptor += "#";
    else if(this->type == Type::Internal) descriptor += "!";
        
    descriptor += this->name;
    return descriptor;
}

bool operator<(const ChatHandle first, const ChatHandle second) {
    if(first.type == second.type) {
        return first.name < second.name;
    } else {
        return first.type < second.type;
    }
}