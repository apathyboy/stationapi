#include "LeaveRoom.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"

#include "easylogging++.h"

LeaveRoom::LeaveRoom(GatewayClient * client, const RequestType & request, ResponseType & response)
    : avatarService_{client->GetNode()->GetAvatarService()}
    , roomService_{client->GetNode()->GetRoomService()} {
    auto srcAvatar = avatarService_->GetAvatar(request.srcAvatarId);
    if (!srcAvatar) {
        throw ChatResultException{ChatResultCode::SRCAVATARDOESNTEXIST};
    }

    auto room = roomService_->GetRoom(request.roomAddress);
    if (!room) {
        throw ChatResultException{ChatResultCode::ADDRESSNOTROOM};
    }

    response.roomId = room->GetRoomId();

    // Cache the addresses before leaving the room in case this avatar was the
    // last on their server, to ensure the update messages goes out.
    auto addresses = room->GetConnectedAddresses();
    room->LeaveRoom(srcAvatar);

    client->SendLeaveRoomUpdate(addresses, srcAvatar->GetAvatarId(), room->GetRoomId());
}
