#include "AddModerator.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

AddModerator::AddModerator(
    GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()}
    , roomService_{client->GetNode()->GetRoomService()} {
    LOG(INFO) << "ADDMODERATOR request recieved - adding: "
              << FromWideString(request.destAvatarName) << "@"
              << FromWideString(request.destAvatarAddress) << " to "
              << FromWideString(request.destRoomAddress);

    auto srcAvatar = avatarService_->GetAvatar(request.srcAvatarId);
    if (!srcAvatar) {
        throw ChatResultException{ChatResultCode::SRCAVATARDOESNTEXIST};
    }

    auto moderatorAvatar
        = avatarService_->GetAvatar(request.destAvatarName, request.destAvatarAddress);
    if (!moderatorAvatar) {
        throw ChatResultException{ChatResultCode::DESTAVATARDOESNTEXIST};
    }

    auto room = roomService_->GetRoom(request.destRoomAddress);
    if (!room) {
        throw ChatResultException{ChatResultCode::ADDRESSNOTROOM};
    }

    response.destRoomId = room->GetRoomId();

    room->AddModerator(srcAvatar->GetAvatarId(), moderatorAvatar);
}
