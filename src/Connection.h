#pragma once

#include <iostream>
#include <memory>
#include <asio.hpp>
#include <functional>
#include "Parser.h"
#include "loggers/ILogger.h"
#include "chat/IChat.h"
#include "chat/IChatHandler.h"

namespace ip = asio::ip;

class Connection :public std::enable_shared_from_this<Connection>, public IChatHandler {
    const static int CHUNK_SIZE = 16;
    std::array<char, CHUNK_SIZE> read_chunk;

    ChatHandle handle;
    ip::tcp::socket socket;
    Parser parser;
    std::unique_ptr<ILogger> logger;
    std::shared_ptr<IChat> chat;

    void read();
    void on_read(const asio::error_code e, size_t bytes_transferred);
    void on_message(json j);
    void on_write(const asio::error_code e, size_t bytes_transferred, std::shared_ptr<std::string> buffer);
    void shutdown();
public:
    Connection(ip::tcp::socket&& socket, std::unique_ptr<ILogger> logger, std::shared_ptr<IChat> chat)
        :socket(static_cast<ip::tcp::socket&&>(socket)), 
        logger(std::move(logger)),
        chat(chat)
    {   
        this->logger->info("connected");
    }

    Connection(Connection&& connection) 
        :socket(std::move(connection.socket)), 
        logger(std::move(connection.logger))
    {}

    virtual ~Connection() {
        this->logger->info("disconnected");
    }

    void run();
    virtual void handle_message(Message message);
};