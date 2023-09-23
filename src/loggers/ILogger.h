#pragma once

#include <string>

class ILogger
{
public:
    enum class Level {
        Debug, Info, Warn, Err
    };
    virtual ~ILogger() {}
    virtual void debug(std::string_view msg) = 0;
    virtual void info(std::string_view msg) = 0;
    virtual void warn(std::string_view msg) = 0;
    virtual void err(std::string_view msg) = 0;
    virtual void fatal(std::string_view msg) = 0;

    virtual Level get_level() = 0;
};