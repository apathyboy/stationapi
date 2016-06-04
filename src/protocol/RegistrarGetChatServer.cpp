#include "RegistrarGetChatServer.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "RegistrarClient.hpp"
#include "RegistrarNode.hpp"
#include "StationChatConfig.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"


RegistrarGetChatServer::RegistrarGetChatServer(RegistrarClient* client, const RequestType & request, ResponseType & response) {
    auto& config = client->GetNode()->GetConfig();

    response.hostname = ToWideString(config.gatewayAddress);
    response.port = config.gatewayPort;
}
