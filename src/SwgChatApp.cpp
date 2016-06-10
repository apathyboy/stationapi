#include "SwgChatApp.hpp"

#include <iostream>

SwgChatApp::SwgChatApp(SwgChatConfig config) 
    : config_{std::move(config)} {
    registrarNode_ = std::make_unique<RegistrarNode>(config_);
    std::cout << "Registrar listening @" << config_.registrarAddress << ":" << config_.registrarPort << "\n";

    gatewayNode_ = std::make_unique<GatewayNode>(config_);
    std::cout << "Gateway listening @" << config_.gatewayAddress << ":" << config_.gatewayPort << "\n";
}

void SwgChatApp::Tick() {
    registrarNode_->Tick();
    gatewayNode_->Tick();
}
