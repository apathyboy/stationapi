
#pragma once

#include "GatewayNode.hpp"
#include "RegistrarNode.hpp"
#include "SwgChatConfig.hpp"

#include <cstdint>
#include <memory>
#include <string>

class SwgChatApp {
public:
    explicit SwgChatApp(SwgChatConfig config);

    bool IsRunning() const { return isRunning_; }

    void Tick();

private:
    SwgChatConfig config_;
    bool isRunning_ = true;
    std::unique_ptr<GatewayNode> gatewayNode_;
    std::unique_ptr<RegistrarNode> registrarNode_;    
};
