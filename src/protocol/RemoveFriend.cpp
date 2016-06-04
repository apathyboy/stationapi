#include "RemoveFriend.hpp"

#include "ChatAvatarService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

RemoveFriend::RemoveFriend(
    GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()} {
    LOG(INFO) << "REMOVEFRIEND request received - removing: " << FromWideString(request.destName)
              << "@" << FromWideString(request.destAddress) << " from " << request.srcAvatarId
              << "@" << FromWideString(request.srcAddress);

    auto srcAvatar = avatarService_->GetAvatar(request.srcAvatarId);
    if (!srcAvatar) {
        throw ChatResultException{ChatResultCode::SRCAVATARDOESNTEXIST};
    }

    auto destAvatar = avatarService_->GetAvatar(request.destName, request.destAddress);
    if (!destAvatar) {
        throw ChatResultException{ChatResultCode::DESTAVATARDOESNTEXIST};
    }

    srcAvatar->RemoveFriend(destAvatar);
}
