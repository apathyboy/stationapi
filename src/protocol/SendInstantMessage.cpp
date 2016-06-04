#include "SendInstantMessage.hpp"

#include "ChatAvatarService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

SendInstantMessage::SendInstantMessage(
    GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()} {
    LOG(INFO) << "SENDINSTANTMESSAGE request received "
              << " - from " << request.srcAvatarId << "@" << FromWideString(request.srcAddress) << " to "
              << FromWideString(request.destName) << "@" << FromWideString(request.destAddress);

    auto srcAvatar = avatarService_->GetAvatar(request.srcAvatarId);
    if (!srcAvatar) {
        throw ChatResultException(ChatResultCode::SRCAVATARDOESNTEXIST);
    }

    auto destAvatar = avatarService_->GetAvatar(request.destName, request.destAddress);
    if (!destAvatar) {
        throw ChatResultException(ChatResultCode::DESTAVATARDOESNTEXIST);
    }

    client->SendInstantMessageUpdate(srcAvatar, destAvatar, request.message, request.oob);
}
