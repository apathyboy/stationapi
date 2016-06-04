#include "GetPersistentMessage.hpp"

#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "PersistentMessageService.hpp"

#include "easylogging++.h"

GetPersistentMessage::GetPersistentMessage(
    GatewayClient* client, const RequestType& request, ResponseType& response)
    : messageService_{client->GetNode()->GetMessageService()} {
    LOG(INFO) << "GETPERSISTENTMESSAGE request received - avatar: " << request.srcAvatarId
              << " message: " << request.messageId;

    response.message
        = messageService_->GetPersistentMessage(request.srcAvatarId, request.messageId);
}
