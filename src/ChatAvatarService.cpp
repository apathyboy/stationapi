#include "ChatAvatarService.hpp"
#include "ChatAvatar.hpp"

#include "ServiceContainer.hpp"

ChatAvatarService::ChatAvatarService(SwgChatConfig* config)
    : config_{config} {}

ChatAvatarService::~ChatAvatarService() {}

ChatAvatar* ChatAvatarService::GetAvatarByNameAndAddress(
    const std::wstring& name, const std::wstring& address) {
    ChatAvatar* avatar = GetOnlineAvatarByNameAndAddress(name, address);

    if (!avatar) {
        avatar = GetPersistedAvatarByNameAndAddress(name, address);
    }

    return avatar;
}

ChatAvatar* ChatAvatarService::GetOnlineAvatarByNameAndAddress(
    const std::wstring& name, const std::wstring& address) {
    ChatAvatar* avatar = nullptr;

    auto find_iter = avatarMap_.find(name + L"+" + address);
    if (find_iter != std::end(avatarMap_)) {
        avatar = find_iter->second.get();
    }

    return avatar;
}

ChatAvatar* ChatAvatarService::GetPersistedAvatarByNameAndAddress(
    const std::wstring& name, const std::wstring& address) {
    return nullptr;
}
