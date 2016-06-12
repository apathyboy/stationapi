
#pragma once

#include "NodeClient.hpp"

class GatewayNode;
class UdpConnection;

struct ReqLoginAvatar;
struct ReqLogoutAvatar;
struct ReqCreateRoom;
struct ReqEnterRoom;
struct ReqGetRoom;
struct ReqGetRoomSummaries;
struct ReqSetApiVersion;
struct ReqSetAvatarAttributes;
struct ReqGetAnyAvatar;

class GatewayClient : public NodeClient<8192> {
public:
    GatewayClient(UdpConnection* connection, GatewayNode* node);
    virtual ~GatewayClient();

private:
    void OnIncoming(BinarySourceStream& istream) override;

    void HandleLoginAvatar(const ReqLoginAvatar& request);
    void HandleLogoutAvatar(const ReqLogoutAvatar& request);
    void HandleCreateRoom(const ReqCreateRoom& request);
    void HandleEnterRoom(const ReqEnterRoom& request);
    void HandleGetRoom(const ReqGetRoom& request);
    void HandleGetRoomSummaries(const ReqGetRoomSummaries& request);
    void HandleSetApiVersion(const ReqSetApiVersion& request);
    void HandleSetAvatarAttributes(const ReqSetAvatarAttributes& request);
    void HandleGetAnyAvatar(const ReqGetAnyAvatar& request);
    
    GatewayNode* node_;
};
