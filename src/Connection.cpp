#include "Connection.h"

void Connection::read() {
    auto self = shared_from_this();
    self->socket.async_read_some(
        asio::buffer(self->chunk.end() - Connection::CHUNK_SIZE, Connection::CHUNK_SIZE), 
        [self] (const std::error_code e, size_t bytes_transferred) {
            self->on_read(e, bytes_transferred);
        }
    );
}

void Connection::on_read(const std::error_code e, size_t bytes_transferred) {
    if(e) {
        if(
            e.value() == static_cast<int>(std::errc::connection_reset)
        ) {
            this->logger->info("connection closed");
        } else {
            std::stringstream msg;
            msg << "error " << e.value() << ": " << e.message();
            this->logger->err(msg.view());
        }
        this->shutdown();
        return;
    }
    
    std::stringstream msg;
    msg << "received " << bytes_transferred << " bytes";
    this->logger->debug(msg.view());

    try {
        if(this->parser.feed(std::string_view(this->chunk.begin(), bytes_transferred))) {
            std::stringstream msg;
            msg << "message received: " << this->parser.get_json().value();
            this->logger->info(msg.view());
        } else {
            this->read();
        }
    } catch(std::exception& e) {
        this->logger->err(e.what());
        this->shutdown();
    }
}

void Connection::shutdown() {
    if(socket.is_open()) {
        socket.shutdown(asio::socket_base::shutdown_type::shutdown_both);
        socket.close();
    }
}

void Connection::run() {
    this->read();
}