#pragma once
#include "request/Message.h"

class IChatHandler
{
public:
    virtual ~IChatHandler() {};
    virtual void handle_message(Message message) = 0;
};