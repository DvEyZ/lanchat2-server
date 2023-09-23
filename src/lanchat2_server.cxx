#include <iostream>
#include <vector>
#include <memory>
#include <asio.hpp>
#include <nlohmann/json.hpp>

#include "Config.h"
#include "Connection.h"
#include "loggers/ConsoleLogger.h"

namespace ip = asio::ip;
using json = nlohmann::json;

void accept(ip::tcp::acceptor& acceptor, ILogger* logger) {
    acceptor.async_accept([&acceptor, logger] (asio::error_code e, ip::tcp::socket socket) {
        if(e) {
            logger->err(e.message());
        }
        auto sock_logger = new ConsoleLogger(logger->get_level(), socket.remote_endpoint().address().to_string());
        auto conn = std::shared_ptr<Connection>(new Connection(socket, sock_logger));
        conn->run();
        accept(acceptor, logger);
    });
}

int main(int argc, char** argv) {
    auto ctx = asio::io_context();

    auto config = Config();
    auto cli_logger = ConsoleLogger(ILogger::Level::Warn, "CLI");
    try {
        config.from_args(argc, argv);
        config.from_file();
    } catch(ConfigWarning& e) {
        cli_logger.warn(e.what());
    } catch(ConfigError& e) {
        cli_logger.fatal(e.what());
        return 1;
    }

    int port = config.get_port();
    ILogger::Level log_level = config.get_log_level(); 

    auto global_logger = ConsoleLogger(log_level, "Global");

    try {
        auto acceptor = ip::tcp::acceptor(ctx, ip::tcp::endpoint(ip::tcp::v4(), port));

        global_logger.debug("logging in debug mode");

        std::stringstream msg;
        msg << "listening on port " << port;
        global_logger.info(msg.view());

        accept(acceptor, &global_logger);

        ctx.run();
    } catch(std::exception& e) {
        global_logger.fatal(e.what());
        return 2;
    }

    return 0;
}
