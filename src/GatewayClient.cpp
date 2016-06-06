
#include "GatewayClient.hpp"

#include "Request.hpp"
#include "Response.hpp"
#include "ServiceContainer.hpp"
#include "UdpLibrary.hpp"

GatewayClient::GatewayClient(UdpConnection* connection, ServiceContainer* services)
    : NodeClient<2048>(connection)
    , services_{services} {
    connection->SetHandler(this);
}

GatewayClient::~GatewayClient() {}

void GatewayClient::OnIncoming(BinarySourceStream& istream) {
    ChatRequestType request_type = ::read<ChatRequestType>(istream);

    switch (request_type) {
    case ChatRequestType::SETAPIVERSION:
        HandleSetApiVersion(istream);
        break;
    //case ChatRequestType::GETANYAVATAR:
    //    HandleGetAnyAvatar(istream);
    //    break;
    }
}

void GatewayClient::HandleSetApiVersion(BinarySourceStream& istream) {
    ReqSetApiVersion request;
    read(istream, request);

    uint32_t version = services_->GetConfig()->version;
    ChatResultCode result = (version == request.version)
        ? ChatResultCode::SUCCESS
        : ChatResultCode::WRONGCHATSERVERFORREQUEST;

    ResSetApiVersion response{request.track, result, version};

    SendMessage(response);
}

void GatewayClient::HandleGetAnyAvatar(BinarySourceStream& istream) {
    ReqGetAnyAvatar request;
    read(istream, request);

    auto avatar
        = services_->GetAvatarService()->GetAvatarByNameAndAddress(request.name, request.address);
    ChatResultCode result
        = (avatar) ? ChatResultCode::SUCCESS : ChatResultCode::DESTAVATARDOESNTEXIST;

    bool isOnline = (avatar != nullptr) ? avatar->isOnline : false;

    ResGetAnyAvatar response{request.track, result, isOnline, avatar};

    SendMessage(response);
}
