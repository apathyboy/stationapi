
#pragma once

#include "Node.hpp"
#include "GatewayClient.hpp"

#include <memory>

class ChatAvatarService;
struct SwgChatConfig;

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
};
