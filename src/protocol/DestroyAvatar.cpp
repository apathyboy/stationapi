#include "DestroyAvatar.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"

#include "easylogging++.h"

DestroyAvatar::DestroyAvatar(
    GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()}
    , roomService_{client->GetNode()->GetRoomService()} {
    auto avatar = avatarService_->GetAvatar(request.avatarId);
    if (!avatar) {
        throw ChatResultException{ChatResultCode::SRCAVATARDOESNTEXIST};
    }

    // Remove From All Rooms
    for (auto room : avatar->GetJoinedRooms()) {
        auto addresses = room->GetConnectedAddresses();
        room->LeaveRoom(avatar);

        client->SendLeaveRoomUpdate(addresses, avatar->GetAvatarId(), room->GetRoomId());
    }

    // Destroy avatar
    avatarService_->DestroyAvatar(avatar);
}
