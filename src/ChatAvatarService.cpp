#include "ChatAvatarService.hpp"
#include "ChatAvatar.hpp"

ChatAvatarService::ChatAvatarService(sqlite3* db)
    : db_{db} {}

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

    auto find_iter = onlineAvatars_.find(name + L"+" + address);
    if (find_iter != std::end(onlineAvatars_)) {
        avatar = find_iter->second.get();
    }

    return avatar;
}

ChatAvatar* ChatAvatarService::GetPersistedAvatarByNameAndAddress(
    const std::wstring& name, const std::wstring& address) {
    ChatAvatar* avatar = nullptr;
    return avatar;
}
