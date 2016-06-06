#include "SwgChatApp.hpp"

SwgChatApp::SwgChatApp(SwgChatConfig config) 
    : config_{std::move(config)} {
    gatewayNode_ = std::make_unique<GatewayNode>(config_);
    registrarNode_ = std::make_unique<RegistrarNode>(config_);
}

void SwgChatApp::Tick() { 
    gatewayNode_->Tick();
    registrarNode_->Tick();
}
