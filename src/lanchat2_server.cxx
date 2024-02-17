#include <iostream>
#include <vector>
#include <memory>
#include <asio.hpp>
#include <nlohmann/json.hpp>

#include "Config.h"
#include "Connection.h"
#include "loggers/ConsoleLogger.h"
#include "chat/Chat.h"


const char* VERSION = "0.0.0";

namespace ip = asio::ip;
using json = nlohmann::json;

void display_help() {
    std::cout 
        << "LanChat2 server v" << VERSION << "\n\n"
        << "Command line options:\n"
        << "\t-h, -?, --help\t\t show this help\n"
        << "\t-p, --port PORT:\t set listen port; default is 12398\n"
        << "\t-L, --log-level LEVEL:\t set log level; valid values are `debug`, `info`, `warn` and `err`; default is `info`\n";
}

void accept(ip::tcp::acceptor& acceptor, std::shared_ptr<Chat> chat, ILogger* logger) {
    acceptor.async_accept([&acceptor, chat, logger] (asio::error_code e, ip::tcp::socket socket) {
        if(e) {
            logger->err(e.message());
        }
        auto sock_logger = std::make_unique<ConsoleLogger>(ConsoleLogger(logger->get_level(), socket.remote_endpoint().address().to_string()));
        auto conn = std::shared_ptr<Connection>(new Connection(
            std::move(socket), 
            std::move(sock_logger),
            chat
        ));
        conn->run();
        accept(acceptor, chat, logger);
    });
}

int main(int argc, char** argv) {
    auto ctx = asio::io_context();

    auto config = Config();
    auto cli_logger = ConsoleLogger(ILogger::Level::Warn, "CLI");
    
    try {
        config.from_file();
    } catch(ConfigWarning& e) {
        cli_logger.warn(e.what());
    } catch(ConfigError& e) {
        cli_logger.fatal(e.what());
        return 1;
    }

    try {
        config.from_args(argc, argv);
    } catch(ConfigWarning& e) {
        cli_logger.warn(e.what());
    } catch(ConfigError& e) {
        cli_logger.fatal(e.what());
        return 1;
    }

    if(config.get_is_help()) {
        display_help();
        return 0;
    }

    int port = config.get_port();
    ILogger::Level log_level = config.get_log_level(); 

    auto global_logger = ConsoleLogger(log_level, "Global");

    try {
        auto acceptor = ip::tcp::acceptor(ctx, ip::tcp::endpoint(ip::tcp::v4(), port));
        auto chat = std::shared_ptr<Chat>(new Chat(std::make_unique<ConsoleLogger>(ConsoleLogger(global_logger.get_level(), "Chat"))));

        global_logger.debug("logging in debug mode");

        std::stringstream msg;
        msg << "listening on port " << port;
        global_logger.info(msg.view());

        accept(acceptor, chat, &global_logger);

        ctx.run();
    } catch(std::exception& e) {
        global_logger.fatal(e.what());
        return 2;
    }

    return 0;
}
