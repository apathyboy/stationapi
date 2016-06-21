
#pragma once

#include "NodeClient.hpp"

class GatewayNode;
class UdpConnection;

struct ReqLoginAvatar;
struct ReqLogoutAvatar;
struct ReqCreateRoom;
struct ReqAddFriend;
struct ReqRemoveFriend;
struct ReqFriendStatus;
struct ReqAddIgnore;
struct ReqRemoveIgnore;
struct ReqEnterRoom;
struct ReqGetRoom;
struct ReqGetRoomSummaries;
struct ReqSendPersistentMessage;
struct ReqGetPersistentHeaders;
struct ReqGetPersistentMessage;
struct ReqUpdatePersistentMessage;
struct ReqIgnoreStatus;
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
    void HandleAddFriend(const ReqAddFriend& request);
    void HandleRemoveFriend(const ReqRemoveFriend& request);
    void HandleFriendStatus(const ReqFriendStatus& request);
    void HandleAddIgnore(const ReqAddIgnore& request);
    void HandleRemoveIgnore(const ReqRemoveIgnore& request);
    void HandleEnterRoom(const ReqEnterRoom& request);
    void HandleGetRoom(const ReqGetRoom& request);
    void HandleGetRoomSummaries(const ReqGetRoomSummaries& request);
    void HandleSendPersistentMessage(const ReqSendPersistentMessage& request);
    void HandleGetPersistentHeaders(const ReqGetPersistentHeaders& request);
    void HandleGetPersistentMessage(const ReqGetPersistentMessage& request);
    void HandleUpdatePersistentMessage(const ReqUpdatePersistentMessage& request);
    void HandleIgnoreStatus(const ReqIgnoreStatus& request);
    void HandleSetApiVersion(const ReqSetApiVersion& request);
    void HandleSetAvatarAttributes(const ReqSetAvatarAttributes& request);
    void HandleGetAnyAvatar(const ReqGetAnyAvatar& request);
    
    GatewayNode* node_;
};
