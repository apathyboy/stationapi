
#pragma once

#include "BinaryStream.hpp"
#include "NodeClient.hpp"
#include "UdpLibrary.hpp"

class ServiceContainer;

class RegistrarClient : public UdpConnectionHandler, NodeClient<4096> {
public:
    RegistrarClient(UdpConnection* connection, ServiceContainer* services);
    ~RegistrarClient();

    UdpConnection* GetConnection() { return connection_; }

private:
    void OnRoutePacket(UdpConnection* connection, const uchar* data, int length) override;

    void HandleGetChatServer(BinarySourceStream& istream);

    ServiceContainer* services_;
    UdpConnection* connection_;
};