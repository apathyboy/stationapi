
#pragma once

#include "NodeClient.hpp"

class GatewayNode;
class UdpConnection;

class GatewayClient : public NodeClient<2048> {
public:
    GatewayClient(UdpConnection* connection, GatewayNode* node);
    virtual ~GatewayClient();

private:
    void OnIncoming(BinarySourceStream& istream) override;

    void HandleLoginAvatar(BinarySourceStream& istream);
    void HandleSetApiVersion(BinarySourceStream& istream);
    void HandleGetAnyAvatar(BinarySourceStream& istream);
    
    GatewayNode* node_;
};
