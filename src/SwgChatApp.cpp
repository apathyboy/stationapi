#include "SwgChatApp.hpp"

SwgChatApp::SwgChatApp(SwgChatConfig config) {
    services_ = std::make_unique<ServiceContainer>(std::move(config));
    registrarNode_ = std::make_unique<RegistrarNode>(services_.get());
}

void SwgChatApp::Tick() { registrarNode_->Tick(); }
