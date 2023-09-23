#pragma once

#include "ILogger.h"
#include <mutex>
#include <iostream>

class ConsoleLogger :public ILogger {
private:
    static std::mutex out_lock;

    std::string prefix;
    Level level;

    void write(std::string_view type, std::string_view msg);
public:
    ConsoleLogger(Level level, std::string prefix) 
        :prefix(prefix), level(level)
    {}

    virtual ~ConsoleLogger() {};

    void debug(std::string_view msg);
    void info(std::string_view msg);
    void warn(std::string_view msg);
    void err(std::string_view msg);
    void fatal(std::string_view msg);
    Level get_level();
};