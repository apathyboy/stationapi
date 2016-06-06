
#pragma once

#include "Node.hpp"
#include "RegistrarClient.hpp"

struct SwgChatConfig;

class RegistrarNode : public Node<RegistrarNode, RegistrarClient> {
public:
    explicit RegistrarNode(SwgChatConfig& config);
    ~RegistrarNode();

    SwgChatConfig& GetConfig();

private:
    void OnTick() override;

    SwgChatConfig& config_;
};
