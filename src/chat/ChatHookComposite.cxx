#include "ChatHookComposite.h"

void ChatHookComposite::on_message_pushed(
    Message message, 
    std::function<void(Message)> proceed,
    std::function<void(Rejection, Message)> reject
) {
    proceed(message);
}

void ChatHookComposite::on_handler_subscribed(
    SubscribeRequest req,
    std::function<void(SubscribeRequest)> proceed,
    std::function<void(Rejection, SubscribeRequest)> reject
) {
    proceed(req);
}

void ChatHookComposite::on_handler_matched(
    Message message, 
    ChatHandle handle, 
    std::function<void(Message, ChatHandle)> proceed,
    std::function<void(Rejection, Message, ChatHandle)> reject
) {
    proceed(message, handle);
}

void ChatHookComposite::on_handler_expired(
    Message message, 
    ChatHandle handle
) {
    
}