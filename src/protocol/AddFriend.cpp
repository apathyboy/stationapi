#include "AddFriend.hpp"

#include "ChatAvatarService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

AddFriend::AddFriend(GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()} {
    LOG(INFO) << "ADDFRIEND request received - adding: " << FromWideString(request.destName) << "@"
              << FromWideString(request.destAddress) << " to " << request.srcAvatarId << "@"
              << FromWideString(request.srcAddress);
    auto srcAvatar = avatarService_->GetAvatar(request.srcAvatarId);
    if (!srcAvatar) {
        throw ChatResultException{ChatResultCode::SRCAVATARDOESNTEXIST};
    }

    auto destAvatar = avatarService_->GetAvatar(request.destName, request.destAddress);
    if (!destAvatar) {
        throw ChatResultException{ChatResultCode::DESTAVATARDOESNTEXIST};
    }

    srcAvatar->AddFriend(destAvatar);

    if (destAvatar->IsOnline()) {
        client->SendFriendLoginUpdate(srcAvatar, destAvatar);
    }
}
