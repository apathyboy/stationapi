
#pragma once

#include "Node.hpp"
#include "GatewayClient.hpp"

#include <memory>

class ChatAvatarService;
class ChatRoomService;
class PersistentMessageService;
struct SwgChatConfig;
struct sqlite3;

class GatewayNode : public Node<GatewayNode, GatewayClient> {
public:
    explicit GatewayNode(SwgChatConfig& config);
    ~GatewayNode();

    ChatAvatarService* GetAvatarService();
    ChatRoomService* GetRoomService();
    PersistentMessageService* GetMessageService();
    SwgChatConfig& GetConfig();

private:
    void OnTick() override;

    std::unique_ptr<ChatAvatarService> avatarService_;
    std::unique_ptr<ChatRoomService> roomService_;
    std::unique_ptr<PersistentMessageService> messageService_;
    SwgChatConfig& config_;
    sqlite3* db_;
};
