
#include "RegistrarNode.hpp"

#include "SwgChatConfig.hpp"

RegistrarNode::RegistrarNode(SwgChatConfig& config)
    : Node(this, config.registrarAddress, config.registrarPort)
    , config_{config} {}

RegistrarNode::~RegistrarNode() {}

SwgChatConfig& RegistrarNode::GetConfig() {
    return config_;
}

void RegistrarNode::OnTick() {}

