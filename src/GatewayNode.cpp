
#include "GatewayNode.hpp"

#include "ChatAvatarService.hpp"
#include "SwgChatConfig.hpp"

GatewayNode::GatewayNode(SwgChatConfig& config)
    : Node(this, config.gatewayAddress, config.gatewayPort)
    , config_{config} {
    avatarService_ = std::make_unique<ChatAvatarService>();
}

GatewayNode::~GatewayNode() {}

ChatAvatarService* GatewayNode::GetAvatarService() {
    return avatarService_.get();
}

SwgChatConfig& GatewayNode::GetConfig() {
    return config_;
}

void GatewayNode::OnTick() {}
