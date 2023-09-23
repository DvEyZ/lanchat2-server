#pragma once

#include <nlohmann/json.hpp>
#include <optional>

using json = nlohmann::json;

class Parser {
private:
    std::string buffer;
    std::optional<json> doc;
public:
    Parser() {};
    void reset();
    bool feed(std::string_view content);
    std::optional<json>& get_json();
};