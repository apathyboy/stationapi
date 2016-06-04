#include "DestroyRoom.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

DestroyRoom::DestroyRoom(GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()}
    , roomService_{client->GetNode()->GetRoomService()} {
    LOG(INFO) << "DESTROYROOM request received " << request.srcAvatarId << "@"
              << FromWideString(request.srcAddress)
              << " room: " << FromWideString(request.roomAddress);

    auto srcAvatar = avatarService_->GetAvatar(request.srcAvatarId);
    if (!srcAvatar) {
        throw ChatResultException(ChatResultCode::SRCAVATARDOESNTEXIST);
    }

    auto room = roomService_->GetRoom(request.roomAddress);
    if (!room) {
        throw ChatResultException(ChatResultCode::ADDRESSNOTROOM);
    }

    auto addresses = room->GetRemoteAddresses();
    auto roomId = room->GetRoomId();

    response.roomId = roomId;

    for (auto roomAvatar : room->GetAvatars()) {
        auto roomAddresses = room->GetConnectedAddresses();
        room->LeaveRoom(roomAvatar);
        client->SendLeaveRoomUpdate(roomAddresses, roomAvatar->GetAvatarId(), roomId);
    }

    roomService_->DestroyRoom(room);

    client->SendDestroyRoomUpdate(srcAvatar, roomId, addresses);
}
