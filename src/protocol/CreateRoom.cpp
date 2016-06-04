#include "CreateRoom.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

CreateRoom::CreateRoom(GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()}
    , roomService_{client->GetNode()->GetRoomService()} {
    LOG(INFO) << "CREATEROOM request received - creator: " << request.creatorId << "@"
              << FromWideString(request.srcAddress)
              << " room: " << FromWideString(request.roomAddress);

    response.room = roomService_->CreateRoom(avatarService_->GetAvatar(request.creatorId),
        request.roomName, request.roomTopic, request.roomPassword, request.roomAttributes,
        request.roomMaxSize, request.roomAddress, request.srcAddress);
}
