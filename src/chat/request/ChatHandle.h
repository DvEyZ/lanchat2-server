#pragma once
#include <string>

class ChatHandle {
public:
    enum class Type {
        User, Group, System
    };

    const std::string name;
    const Type type;

    ChatHandle(std::string name, Type type) 
        :name(name), type(type)
    {};

    static ChatHandle from_descriptor(std::string descriptor);
    std::string to_descriptor();
};

bool operator<(const ChatHandle first, const ChatHandle second);