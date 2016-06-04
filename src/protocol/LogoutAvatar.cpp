#include "LogoutAvatar.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"

#include "easylogging++.h"

LogoutAvatar::LogoutAvatar(GatewayClient * client, const RequestType & request, ResponseType & response)
    : avatarService_{client->GetNode()->GetAvatarService()}
    , roomService_{client->GetNode()->GetRoomService()}
{
    LOG(INFO) << "LOGOUTAVATAR request received - avatar id:" << request.avatarId;

    auto avatar = avatarService_->GetAvatar(request.avatarId);

    for (auto room : avatar->GetJoinedRooms()) {
        auto addresses = room->GetConnectedAddresses();
        room->LeaveRoom(avatar);
    
        client->SendLeaveRoomUpdate(addresses, avatar->GetAvatarId(), room->GetRoomId());
    }

    client->SendFriendLogoutUpdates(avatar);

    avatarService_->LogoutAvatar(avatar);
}
