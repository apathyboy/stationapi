#include "UpdatePersistentMessage.hpp"

#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "PersistentMessageService.hpp"

#include "easylogging++.h"

UpdatePersistentMessage::UpdatePersistentMessage(GatewayClient * client, const RequestType & request, ResponseType & response)
    : messageService_{client->GetNode()->GetMessageService()} {
    LOG(INFO) << "UPDATEPERSISTENTMESSAGE request received";
    messageService_->UpdateMessageStatus(
        request.srcAvatarId, request.messageId, request.status);
}
