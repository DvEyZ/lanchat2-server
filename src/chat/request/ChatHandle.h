#pragma once
#include <string>

class ChatHandle {
public:
    enum class Type {
        User, Group, System, Internal
    };

    std::string name;
    Type type;

    ChatHandle() 
        :type(Type::Internal)
    {};

    ChatHandle(std::string name, Type type) 
        :name(name), type(type)
    {};

    static ChatHandle from_descriptor(std::string descriptor);
    std::string to_descriptor();
};

bool operator<(const ChatHandle first, const ChatHandle second);