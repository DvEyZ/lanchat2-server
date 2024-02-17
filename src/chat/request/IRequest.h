#pragma once

class IRequestVisitor;

class IRequest {
public:
    virtual ~IRequest() {};
    virtual void accept_visitor(IRequestVisitor& visitor) = 0;
};