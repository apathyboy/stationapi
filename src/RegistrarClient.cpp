#include "RegistrarClient.hpp"

#include "RegistrarNode.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "StringUtils.hpp"
#include "SwgChatConfig.hpp"

RegistrarClient::RegistrarClient(UdpConnection* connection, RegistrarNode* node)
    : NodeClient<2048>(connection)
    , node_{node} {
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
    auto& config = node_->GetConfig();

    ReqRegistrarGetChatServer request;
    read(istream, request);

    ResRegistrarGetChatServer response{request.track, ChatResultCode::SUCCESS,
        ToWideString(config.gatewayAddress), config.gatewayPort};

    SendMessage(response);
}
