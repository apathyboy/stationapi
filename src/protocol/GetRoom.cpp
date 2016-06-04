#include "GetRoom.hpp"

#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

GetRoom::GetRoom(GatewayClient* client, const RequestType& request, ResponseType& response)
    : roomService_{client->GetNode()->GetRoomService()} {
    LOG(INFO) << "GETROOM request received - room: " << FromWideString(request.roomAddress);

    auto room = roomService_->GetRoom(request.roomAddress);
    if (!room) {
        throw ChatResultException{ChatResultCode::ADDRESSDOESNTEXIST};
    }

    response.room = room;
}
