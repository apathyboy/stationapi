#include "ChatAvatarService.hpp"

#include "ServiceContainer.hpp"

ChatAvatarService::ChatAvatarService(SwgChatConfig* config)
    : config_{config} {}

ChatAvatar* ChatAvatarService::GetAvatarByNameAndAddress(
    const std::wstring& name, const std::wstring& address) {
    return nullptr;
}
