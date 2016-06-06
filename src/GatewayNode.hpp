
#pragma once

#include "Node.hpp"
#include "GatewayClient.hpp"

#include <memory>

class ChatAvatarService;
struct SwgChatConfig;
struct sqlite3;

class GatewayNode : public Node<GatewayNode, GatewayClient> {
public:
    explicit GatewayNode(SwgChatConfig& config);
    ~GatewayNode();

    ChatAvatarService* GetAvatarService();
    SwgChatConfig& GetConfig();

private:
    void OnTick() override;

    std::unique_ptr<ChatAvatarService> avatarService_;
    SwgChatConfig& config_;
    sqlite3* db_;
};
