#include "RegistrarClient.hpp"

RegistrarClient::RegistrarClient(UdpConnection* connection)
    : connection_{connection} {
    connection_->AddRef();
    connection_->SetHandler(this);
}

void RegistrarClient::OnRoutePacket(UdpConnection* connection, const uchar* data, int length) {}
