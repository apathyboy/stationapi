#include "RegistrarClient.hpp"

#include "Request.hpp"
#include "Response.hpp"
#include "ServiceContainer.hpp"
#include "StringUtils.hpp"

RegistrarClient::RegistrarClient(UdpConnection* connection, ServiceContainer* services)
    : NodeClient<2048>(connection)
    , services_{services} {
    connection->SetHandler(this);
}

RegistrarClient::~RegistrarClient() {}

void RegistrarClient::OnIncoming(BinarySourceStream& istream) {
    ChatRequestType request_type = ::read<ChatRequestType>(istream);

    switch (request_type) {
    case ChatRequestType::REGISTRAR_GETCHATSERVER:
        HandleGetChatServer(istream);
        break;
    default:
        break;
    }
}

void RegistrarClient::HandleGetChatServer(BinarySourceStream& istream) {
    auto config = services_->GetConfig();

    ReqRegistrarGetChatServer request;
    read(istream, request);

    ResRegistrarGetChatServer response{request.track, ChatResultCode::SUCCESS,
        ToWideString(config->gatewayAddress), config->gatewayPort};

    SendMessage(response);
}
