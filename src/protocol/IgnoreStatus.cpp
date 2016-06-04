#include "IgnoreStatus.hpp"

#include "ChatAvatarService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

IgnoreStatus::IgnoreStatus(
    GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()} {
    LOG(INFO) << "IGNORESTATUS request received - for " << request.srcAvatarId << "@"
              << FromWideString(request.srcAddress);

    auto srcAvatar = avatarService_->GetAvatar(request.srcAvatarId);
    if (!srcAvatar) {
        throw ChatResultException{ChatResultCode::SRCAVATARDOESNTEXIST};
    }

    response.srcAvatar = srcAvatar;
}
