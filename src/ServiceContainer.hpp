
#pragma once

#include "SwgChatConfig.hpp"

#include <memory>

class ServiceContainer {
public:
    ServiceContainer(SwgChatConfig config) {
        config_ = std::make_unique<SwgChatConfig>(std::move(config));
    }

    const SwgChatConfig* GetConfig() const { return config_.get(); }

private:
    std::unique_ptr<SwgChatConfig> config_;
};