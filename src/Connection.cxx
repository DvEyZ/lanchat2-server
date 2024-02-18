#include "Connection.h"
#include "chat/request/request_factory.h"
#include "utils/uuid.h"
#include "chat/request/visitors/RequestRoutingVisitor.h"

void Connection::read() {
    auto self = shared_from_this();
    self->socket.async_read_some(
        asio::buffer(self->read_chunk.end() - Connection::CHUNK_SIZE, Connection::CHUNK_SIZE), 
        [self] (const std::error_code e, size_t bytes_transferred) {
            self->on_read(e, bytes_transferred);
        }
    );
}

void Connection::on_read(const std::error_code e, size_t bytes_transferred) {
    if(e) {
        std::stringstream msg;
        msg << "error " << e.value() << ": " << e.message();
        this->logger->debug(msg.view());
        this->shutdown();
        return;
    }
    
    std::stringstream msg;
    msg << "received " << bytes_transferred << " bytes";
    this->logger->debug(msg.view());

    try {
        if(this->parser.feed(std::string_view(this->read_chunk.begin(), bytes_transferred))) {
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
    try {
        auto req = request_factory(json, this->handle);
        auto visitor = RequestRoutingVisitor(this->chat, this->shared_from_this());
        req->accept_visitor(visitor);
    } catch(std::exception& e) {
        this->logger->err(e.what());
        this->shutdown();
        return;
    }
}

void Connection::run() {
    ChatHandle handle = { 
        generate_uuidv4(), 
        ChatHandle::Type::Internal 
    };
    this->handle = handle;

    auto req = SubscribeRequest();
    req.handle_as = handle;
    req.handle_to = handle;

    this->chat->subscribe(req, this->shared_from_this());
    this->logger->debug("connection handle: " + handle.to_descriptor());
    this->read();
}

void Connection::handle_message(Message msg) {
    this->logger->debug("received message");
    auto self = shared_from_this();
    auto buffer = std::make_shared<std::string>(msg.to_json().dump());
    this->logger->debug(buffer.get()->c_str());

    self->socket.async_write_some(asio::buffer(buffer.get()->c_str(), buffer->length()), [self, buffer] (auto e, auto bt) {
        self->on_write(e, bt, buffer);
    });
}

void Connection::on_write(const asio::error_code e, size_t bytes_transferred, std::shared_ptr<std::string> buf) {
    if(e) {
        std::stringstream msg;
        msg << "error " << e.value() << ": " << e.message();
        this->logger->debug(msg.view());
        this->shutdown();
        return;
    }

    std::stringstream msg;
    msg << "wrote " << bytes_transferred << " bytes";
    this->logger->debug(msg.view());

    if(buf->empty()) return;

    auto buffer = std::make_shared<std::string>(buf->substr(bytes_transferred, buf->length() - 1));
    auto self = shared_from_this();

    self->socket.async_write_some(asio::buffer(buffer.get()->c_str(), buffer->length()), [self, buffer] (auto e, auto bt) {
        self->on_write(e, bt, buffer);
    });
}