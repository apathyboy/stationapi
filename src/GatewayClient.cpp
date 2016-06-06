
#include "GatewayClient.hpp"

#include "ChatAvatarService.hpp"
#include "GatewayNode.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "SwgChatConfig.hpp"
#include "UdpLibrary.hpp"

GatewayClient::GatewayClient(UdpConnection* connection, GatewayNode* node)
    : NodeClient<2048>(connection)
    , node_{node} {
    connection->SetHandler(this);
}

GatewayClient::~GatewayClient() {}

void GatewayClient::OnIncoming(BinarySourceStream& istream) {
    ChatRequestType request_type = ::read<ChatRequestType>(istream);

    switch (request_type) {
    case ChatRequestType::SETAPIVERSION:
        HandleSetApiVersion(istream);
        break;
    case ChatRequestType::GETANYAVATAR:
        HandleGetAnyAvatar(istream);
        break;
    }
}

void GatewayClient::HandleSetApiVersion(BinarySourceStream& istream) {
    ReqSetApiVersion request;
    read(istream, request);

    uint32_t version = node_->GetConfig().version;
    ChatResultCode result = (version == request.version)
        ? ChatResultCode::SUCCESS
        : ChatResultCode::WRONGCHATSERVERFORREQUEST;

    SendMessage(ResSetApiVersion{request.track, result, version});
}

void GatewayClient::HandleGetAnyAvatar(BinarySourceStream& istream) {
    ReqGetAnyAvatar request;
    read(istream, request);

    auto avatar
        = node_->GetAvatarService()->GetAvatarByNameAndAddress(request.name, request.address);
    ChatResultCode result
        = (avatar) ? ChatResultCode::SUCCESS : ChatResultCode::DESTAVATARDOESNTEXIST;
    bool isOnline = (avatar != nullptr) ? avatar->isOnline : false;

    SendMessage(ResGetAnyAvatar{request.track, result, isOnline, avatar});
}
