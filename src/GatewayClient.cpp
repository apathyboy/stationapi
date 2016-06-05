
#include "GatewayClient.hpp"

#include "Request.hpp"
#include "Response.hpp"
#include "ServiceContainer.hpp"
#include "UdpLibrary.hpp"

GatewayClient::GatewayClient(UdpConnection* connection, ServiceContainer* services)
    : NodeClient<2048>(connection)
    , services_{ services } {
    connection->SetHandler(this);
}

GatewayClient::~GatewayClient() {}

void GatewayClient::OnIncoming(BinarySourceStream& istream) {
    ChatRequestType request_type = static_cast<ChatRequestType>(read<uint16_t>(istream));

//    switch (request_type) {}
}
