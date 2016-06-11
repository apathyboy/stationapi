#include "SwgChatApp.hpp"

#include "easylogging++.h"

SwgChatApp::SwgChatApp(SwgChatConfig config) 
    : config_{std::move(config)} {
    registrarNode_ = std::make_unique<RegistrarNode>(config_);
    LOG(INFO) << "Registrar listening @" << config_.registrarAddress << ":" << config_.registrarPort;

    gatewayNode_ = std::make_unique<GatewayNode>(config_);
    LOG(INFO) << "Gateway listening @" << config_.gatewayAddress << ":" << config_.gatewayPort;
}

void SwgChatApp::Tick() {
    registrarNode_->Tick();
    gatewayNode_->Tick();
}
