
#pragma once

#include "NodeClient.hpp"

class ServiceContainer;
class UdpConnection;

class GatewayClient : public NodeClient<2048> {
public:
    GatewayClient(UdpConnection* connection, ServiceContainer* services);
    virtual ~GatewayClient();

private:
    void OnIncoming(BinarySourceStream& istream) override;
    
    ServiceContainer* services_;
};
