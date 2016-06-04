#include "GetAnyAvatar.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

GetAnyAvatar::GetAnyAvatar(
    GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()} {
    LOG(INFO) << "GETANYAVATAR request received - avatar: " << FromWideString(request.name) << "@"
              << FromWideString(request.address);

    auto avatar = avatarService_->GetAvatar(request.name, request.address);
    if (!avatar) {
        throw ChatResultException{ChatResultCode::SRCAVATARDOESNTEXIST};
    }

    response.isOnline = avatar->IsOnline();
    response.avatar = avatar;
}
