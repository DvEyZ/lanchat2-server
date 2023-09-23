#include "ConsoleLogger.h"

std::mutex ConsoleLogger::out_lock;

void ConsoleLogger::write(std::string_view type, std::string_view msg) {
    out_lock.lock();
    std::cerr << type << "[" << this->prefix << "]\t " << msg << "\n";
    out_lock.unlock();
}

void ConsoleLogger::debug(std::string_view msg) {
    if(this->level <= Level::Debug) {
        this->write("\033[1m\033[94mDEBUG:\033[0m ", msg);
    }
}

void ConsoleLogger::info(std::string_view msg) {
    if(this->level <= Level::Info) {
        this->write("\033[1mINFO:\033[0m  ", msg);
    }
}

void ConsoleLogger::warn(std::string_view msg) {
    if(this->level <= Level::Warn) {
        this->write("\033[1m\033[93mWARN:\033[0m  ", msg);
    }
}

void ConsoleLogger::err(std::string_view msg) {
    if(this->level <= Level::Err) {
        this->write("\033[1m\033[91mERR:\033[0m   ", msg);
    }
}

void ConsoleLogger::fatal(std::string_view msg) {
    this->write("\033[1m\033[31mFATAL:\033[0m ", msg);
}

ConsoleLogger::Level ConsoleLogger::get_level() {
    return this->level;
}