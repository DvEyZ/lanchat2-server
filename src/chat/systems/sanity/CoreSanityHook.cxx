#include "./CoreSanityHook.h"

ChatHookResult CoreSanityHook::on_message_push(
    Message message
) {
    if(this->config.reject_to_internal) {
        if(message.handle_to.type == ChatHandle::Type::Internal && message.handle_from.type != ChatHandle::Type::System) 
            return ChatHookResult::rejected(Rejection {
                .hook = this->handle.to_descriptor(),
                .what = "direct messages to internal handles are not allowed"
            });
    }
    if(this->config.reject_from_group_handle) {
        if(message.handle_from.type == ChatHandle::Type::Group)
            return ChatHookResult::rejected(Rejection {
                .hook = this->handle.to_descriptor(),
                .what = "messages are not allowed to be sent from group handles"
            });
    }
    return ChatHookResult::accepted();
}