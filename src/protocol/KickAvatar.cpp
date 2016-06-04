#include "KickAvatar.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

KickAvatar::KickAvatar(GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()}
    , roomService_{client->GetNode()->GetRoomService()} {
    LOG(INFO) << "KICKAVATAR request received - kicking: " << FromWideString(request.destAvatarName)
              << "@" << FromWideString(request.destAvatarAddress) << " from "
              << FromWideString(request.destRoomAddress);

    auto srcAvatar = avatarService_->GetAvatar(request.srcAvatarId);
    if (!srcAvatar) {
        throw ChatResultException{ChatResultCode::SRCAVATARDOESNTEXIST};
    }

    auto destAvatar = avatarService_->GetAvatar(request.destAvatarName, request.destAvatarAddress);
    if (!destAvatar) {
        throw ChatResultException{ChatResultCode::DESTAVATARDOESNTEXIST};
    }

    auto room = roomService_->GetRoom(request.destRoomAddress);
    if (!room) {
        throw ChatResultException{ChatResultCode::ADDRESSNOTROOM};
    }

    response.destRoomId = room->GetRoomId();

    auto addresses = room->GetConnectedAddresses();
    room->KickAvatar(srcAvatar->GetAvatarId(), destAvatar);

    client->SendKickAvatarUpdate(addresses, srcAvatar, destAvatar, room);
}
