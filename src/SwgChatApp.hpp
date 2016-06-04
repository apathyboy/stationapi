
#pragma once

#include "RegistrarService.hpp"

#include <cstdint>
#include <memory>
#include <string>

class SwgChatApp {
public:
    SwgChatApp(const std::string& gatewayAddress, uint16_t gatewayPort,
        const std::string& registrarAddress, uint16_t registrarPort);

    bool IsRunning() const { return isRunning_; }

    void Tick();

private:
    bool isRunning_ = true;
    std::unique_ptr<RegistrarService> registrarService_;
};
