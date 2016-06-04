#include "SetApiVersion.hpp"

#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StationChatConfig.hpp"

#include "easylogging++.h"

SetApiVersion::SetApiVersion(
    GatewayClient* client, const RequestType& request, ResponseType& response) {
    LOG(INFO) << "SETAPIVERSION request received - version: " << request.version;
    response.version = client->GetNode()->GetConfig().version;
    response.result = (response.version == request.version)
        ? ChatResultCode::SUCCESS
        : ChatResultCode::WRONGCHATSERVERFORREQUEST;
}
