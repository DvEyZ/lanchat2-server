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
            e.value() != static_cast<int>(std::errc::connection_reset) &&
            e.value() != static_cast<int>(std::errc::no_such_file_or_directory)
        ) {
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
            this->logger->info("message received");
            this->on_message(this->parser.get_json().value());
            this->parser.reset();
        }
    } catch(std::exception& e) {
        this->logger->err(e.what());
        this->shutdown();
        return;
    }
    
    this->read();
}

void Connection::shutdown() {
    if(socket.is_open()) {
        socket.shutdown(asio::socket_base::shutdown_type::shutdown_both);
        socket.close();
    }
}

void Connection::on_message(json json) {
    
}

void Connection::run() {
    this->read();
}