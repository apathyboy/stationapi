
#pragma once

#include "BinaryStream.hpp"
#include "NodeClient.hpp"
#include "UdpLibrary.hpp"

class ServiceContainer;

class RegistrarClient : public UdpConnectionHandler, public NodeClient<2048> {
public:
    RegistrarClient(UdpConnection* connection, ServiceContainer* services);
    virtual ~RegistrarClient();

private:
    void OnRoutePacket(UdpConnection* connection, const uchar* data, int length) override;

    void HandleGetChatServer(BinarySourceStream& istream);

    ServiceContainer* services_;
};
