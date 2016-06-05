#include "RegistrarClient.hpp"

#include "Request.hpp"
#include "Response.hpp"
#include "ServiceContainer.hpp"
#include "StreamUtils.hpp"

#include <iostream>

RegistrarClient::RegistrarClient(UdpConnection* connection, ServiceContainer* services)
    : NodeClient<2048>(connection)
    , services_{services} {
    connection->SetHandler(this);
}

RegistrarClient::~RegistrarClient() {}

void RegistrarClient::OnIncoming(BinarySourceStream & istream)
{
    ChatRequestType request_type = static_cast<ChatRequestType>(read<uint16_t>(istream));

    switch (request_type) {
    case ChatRequestType::REGISTRAR_GETCHATSERVER:
        HandleGetChatServer(istream);
        break;
    }
}

void RegistrarClient::HandleGetChatServer(BinarySourceStream& istream) {
    auto config = services_->GetConfig();

    ReqRegistrarGetChatServer request;
    read(istream, request);

    ResRegistrarGetChatServer response{request.track, ChatResultCode::SUCCESS,
        std::wstring(std::begin(config->gatewayAddress), std::end(config->gatewayAddress)),
        config->gatewayPort};

    SendMessage(response);
}
