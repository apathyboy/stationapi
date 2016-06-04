
#pragma once

#include <cstdint>
#include <string>

struct SwgChatConfig {
    std::string gatewayAddress;
    uint16_t gatewayPort;
    std::string registrarAddress;
    uint16_t registrarPort;
};
