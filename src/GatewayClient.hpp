
#pragma once

#include "NodeClient.hpp"

class GatewayNode;
class UdpConnection;

struct ReqLoginAvatar;
struct ReqCreateRoom;
struct ReqGetRoom;
struct ReqGetRoomSummaries;
struct ReqSetApiVersion;
struct ReqGetAnyAvatar;

class GatewayClient : public NodeClient<2048> {
public:
    GatewayClient(UdpConnection* connection, GatewayNode* node);
    virtual ~GatewayClient();

private:
    void OnIncoming(BinarySourceStream& istream) override;

    void HandleLoginAvatar(const ReqLoginAvatar& request);
    void HandleCreateRoom(const ReqCreateRoom& request);
    void HandleGetRoom(const ReqGetRoom& request);
    void HandleGetRoomSummaries(const ReqGetRoomSummaries& request);
    void HandleSetApiVersion(const ReqSetApiVersion& request);
    void HandleGetAnyAvatar(const ReqGetAnyAvatar& request);
    
    GatewayNode* node_;
};
