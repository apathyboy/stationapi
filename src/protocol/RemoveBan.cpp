#include "RemoveBan.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

RemoveBan::RemoveBan(GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()}
    , roomService_{client->GetNode()->GetRoomService()} {
    LOG(INFO) << "REMOVEBAN request received - removing ban for: "
              << FromWideString(request.destAvatarName) << "@"
              << FromWideString(request.destAvatarAddress) << " from "
              << FromWideString(request.destRoomAddress);

    auto srcAvatar = avatarService_->GetAvatar(request.srcAvatarId);
    if (!srcAvatar) {
        throw ChatResultException{ChatResultCode::SRCAVATARDOESNTEXIST};
    }

    auto bannedAvatar
        = avatarService_->GetAvatar(request.destAvatarName, request.destAvatarAddress);
    if (!bannedAvatar) {
        throw ChatResultException{ChatResultCode::DESTAVATARDOESNTEXIST};
    }

    auto room = roomService_->GetRoom(request.destRoomAddress);
    if (!room) {
        throw ChatResultException{ChatResultCode::ADDRESSNOTROOM};
    }

    response.destRoomId = room->GetRoomId();

    room->RemoveBanned(srcAvatar->GetAvatarId(), bannedAvatar->GetAvatarId());
}
