#include "RegistrarClient.hpp"

#include "Request.hpp"
#include "Response.hpp"
#include "ServiceContainer.hpp"

RegistrarClient::RegistrarClient(UdpConnection* connection, ServiceContainer* services)
    : connection_{connection}
    , services_{services} {
    connection_->AddRef();
    connection_->SetHandler(this);
}

RegistrarClient::~RegistrarClient() {
    connection_->SetHandler(nullptr);
    connection_->Disconnect();
    connection_->Release();
}

void RegistrarClient::OnRoutePacket(UdpConnection* connection, const uchar* data, int length) {

    BinarySourceStream istream{reinterpret_cast<const char*>(data), length};
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

    SendMessage(connection_, response);
}
