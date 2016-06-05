
#pragma once

#include "NodeClient.hpp"

class ServiceContainer;
class UdpConnection;

class RegistrarClient : public NodeClient<2048> {
public:
    RegistrarClient(UdpConnection* connection, ServiceContainer* services);
    virtual ~RegistrarClient();

private:
    void OnIncoming(BinarySourceStream& istream) override;

    void HandleGetChatServer(BinarySourceStream& istream);

    ServiceContainer* services_;
};
