#pragma once

#include <iostream>
#include <memory>
#include <asio.hpp>
#include "Parser.h"
#include "loggers/ILogger.h"

namespace ip = asio::ip;

class Connection :public std::enable_shared_from_this<Connection> {
    const static int CHUNK_SIZE = 16;
    std::array<char, CHUNK_SIZE> chunk;

    ip::tcp::socket socket;
    Parser parser;
    std::unique_ptr<ILogger> logger;

    void read();
    void on_read(const asio::error_code e, size_t bytes_transferred);
    void shutdown();
public:
    Connection(ip::tcp::socket& socket, ILogger* logger)
        :socket(std::move(socket)), logger(logger)
    {
        this->logger->info("connected");
    }
    ~Connection() {
        this->logger->info("disconnected");
    }
    void run();
};