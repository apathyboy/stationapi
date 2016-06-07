
#pragma once

#include "NodeClient.hpp"

class GatewayNode;
class UdpConnection;

struct ReqLoginAvatar;
struct ReqSetApiVersion;
struct ReqGetAnyAvatar;

class GatewayClient : public NodeClient<2048> {
public:
    GatewayClient(UdpConnection* connection, GatewayNode* node);
    virtual ~GatewayClient();

private:
    void OnIncoming(BinarySourceStream& istream) override;

    void HandleLoginAvatar(const ReqLoginAvatar& request);
    void HandleSetApiVersion(const ReqSetApiVersion& istream);
    void HandleGetAnyAvatar(const ReqGetAnyAvatar& istream);
    
    GatewayNode* node_;
};
