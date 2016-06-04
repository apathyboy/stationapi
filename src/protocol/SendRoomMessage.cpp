#include "SendRoomMessage.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

SendRoomMessage::SendRoomMessage(
    GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()}
    , roomService_{client->GetNode()->GetRoomService()} {
    LOG(INFO) << "SENDROOMMESSAGE request received "
              << " - from " << request.srcAvatarId << "@" << FromWideString(request.srcAddress)
              << " to " << FromWideString(request.destRoomAddress);

    auto srcAvatar = avatarService_->GetAvatar(request.srcAvatarId);
    if (!srcAvatar) {
        throw ChatResultException(ChatResultCode::SRCAVATARDOESNTEXIST);
    }

    auto room = roomService_->GetRoom(request.destRoomAddress);
    if (!room) {
        throw ChatResultException(ChatResultCode::ADDRESSNOTROOM);
    }

    response.roomId = room->GetRoomId();

    client->SendRoomMessageUpdate(
        srcAvatar, room, room->GetNextMessageId(), request.message, request.oob);
}
