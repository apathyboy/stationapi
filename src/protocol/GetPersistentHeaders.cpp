#include "GetPersistentHeaders.hpp"

#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "PersistentMessageService.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

GetPersistentHeaders::GetPersistentHeaders(
    GatewayClient* client, const RequestType& request, ResponseType& response)
    : messageService_{client->GetNode()->GetMessageService()} {
    LOG(INFO) << "GETPERSISTENTHEADERS request recieved - avatar: " << request.avatarId
              << " category: " << FromWideString(request.category);

    response.headers = messageService_->GetMessageHeaders(request.avatarId);
}
