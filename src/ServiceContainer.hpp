
#pragma once

#include "ChatAvatarService.hpp"
#include "SwgChatConfig.hpp"

#include <memory>

class ServiceContainer {
public:
    ServiceContainer(SwgChatConfig config) {
        config_ = std::make_unique<SwgChatConfig>(std::move(config));
        avatarService_ = std::make_unique<ChatAvatarService>(config_.get());
    }

    SwgChatConfig* GetConfig() { return config_.get(); }

    ChatAvatarService* GetAvatarService() { return avatarService_.get(); }

private:
    std::unique_ptr<SwgChatConfig> config_;
    std::unique_ptr<ChatAvatarService> avatarService_;
};
