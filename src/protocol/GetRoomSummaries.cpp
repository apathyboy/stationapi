#include "GetRoomSummaries.hpp"

#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

GetRoomSummaries::GetRoomSummaries(
    GatewayClient* client, const RequestType& request, ResponseType& response)
    : roomService_{client->GetNode()->GetRoomService()} {
    LOG(INFO) << "GETROOMSUMMARIES request received - start node: "
              << FromWideString(request.startNodeAddress)
              << " filter: " << FromWideString(request.roomFilter);

    response.rooms = roomService_->GetRoomSummaries(request.startNodeAddress, request.roomFilter);
}
