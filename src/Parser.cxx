#include "Parser.h"

void Parser::reset() {
    this->buffer.erase();
    this->doc.reset();
}

bool Parser::feed(std::string_view content) {
    this->buffer.append(content);
    try {
        json j = json::parse(buffer);
        this->doc = std::optional<json>(std::move(j));
    } catch(json::parse_error& e) {
        if(e.id == 101) {
            auto e_msg = std::string_view(e.what());
            if(
                (e_msg.find("unexpected end of input") != std::string_view::npos) ||
                (e_msg.find("missing closing quote") != std::string_view::npos)
            ) {
                // JSON is incomplete, continue reading
            } else {
                throw e;
            }
        }
    }

    return this->doc.has_value();
}

std::optional<json> Parser::get_json() {
    return this->doc;
}