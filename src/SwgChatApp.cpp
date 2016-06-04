#include "SwgChatApp.hpp"

SwgChatApp::SwgChatApp(const std::string& gatewayAddress, uint16_t gatewayPort,
    const std::string& registrarAddress, uint16_t registrarPort) {
    registrarService_ = std::make_unique<RegistrarService>(registrarAddress, registrarPort);
}

void SwgChatApp::Tick() { registrarService_->Tick(); }
