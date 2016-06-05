#include "SwgChatApp.hpp"

SwgChatApp::SwgChatApp(SwgChatConfig config) {
    services_ = std::make_unique<ServiceContainer>(std::move(config));
    gatewayNode_ = std::make_unique<GatewayNode>(services_.get());
    registrarNode_ = std::make_unique<RegistrarNode>(services_.get());
}

void SwgChatApp::Tick() { 
    gatewayNode_->Tick();
    registrarNode_->Tick();
}
