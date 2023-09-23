#pragma once

#include <iostream>
#include <memory>
#include <asio.hpp>
#include <functional>
#include "Parser.h"
#include "loggers/ILogger.h"

namespace ip = asio::ip;

class Connection :public std::enable_shared_from_this<Connection> {
    const static int CHUNK_SIZE = 16;
    std::array<char, CHUNK_SIZE> chunk;

    ip::tcp::socket socket;
    Parser parser;
    std::function<void(json)> on_message;
    std::unique_ptr<ILogger> logger;

    void read();
    void on_read(const asio::error_code e, size_t bytes_transferred);
    void shutdown();
public:
    Connection(ip::tcp::socket&& socket, ILogger* logger)
        :socket(static_cast<ip::tcp::socket&&>(socket)), 
        logger(logger),
        on_message(std::function<void(json)>(
            [] (json j) {}
        ))
    {
        this->logger->info("connected");
    }
    Connection(Connection&& connection) 
        :socket(std::move(connection.socket)), 
        logger(std::move(connection.logger)), 
        on_message(std::move(connection.on_message))
    {}
    ~Connection() {
        this->logger->info("disconnected");
    }
    void run();
};