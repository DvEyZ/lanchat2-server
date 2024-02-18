#pragma once
#include <string>

struct ChatHandle {
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

    auto operator<=>(ChatHandle const& other) const = default;
};