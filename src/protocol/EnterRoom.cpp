#include "EnterRoom.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoom.hpp"
#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

EnterRoom::EnterRoom(GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()}
    , roomService_{client->GetNode()->GetRoomService()} {
    LOG(INFO) << "ENTERROOM request received - avatar: " << request.srcAvatarId << "@"
              << FromWideString(request.srcAddress)
              << " room: " << FromWideString(request.roomAddress);

    auto srcAvatar = avatarService_->GetAvatar(request.srcAvatarId);
    if (!srcAvatar) {
        throw ChatResultException{ChatResultCode::SRCAVATARDOESNTEXIST};
    }

    response.room = roomService_->GetRoom(request.roomAddress);
    if (!response.room) {
        throw ChatResultException{ChatResultCode::ADDRESSNOTROOM};
    }

    response.roomId = response.room->GetRoomId();
    response.room->EnterRoom(srcAvatar, request.roomPassword);

    client->SendEnterRoomUpdate(srcAvatar, response.room);
}
