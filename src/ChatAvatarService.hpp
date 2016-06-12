
#pragma once

#include "ChatAvatar.hpp"
#include "ChatEnums.hpp"

#include <boost/optional.hpp>

#include <string>
#include <unordered_map>

struct sqlite3;

class ChatAvatarService {
public:
    explicit ChatAvatarService(sqlite3* db);
    ~ChatAvatarService();

    void ClearOnlineAvatars();

    std::pair<ChatResultCode, boost::optional<ChatAvatar>> GetAvatar(
        const std::wstring& name, const std::wstring& address);

    ChatAvatar* GetOnlineAvatar(uint32_t avatarId);

    bool IsAvatarOnline(const std::wstring& name, const std::wstring& address);

    std::pair<ChatResultCode, boost::optional<ChatAvatar>> GetOnlineAvatar(
        const std::wstring& name, const std::wstring& address);

    std::pair<ChatResultCode, boost::optional<ChatAvatar>> GetPersistedAvatar(
        const std::wstring& name, const std::wstring& address);

    ChatResultCode PersistNewAvatar(ChatAvatar& avatar);

    ChatResultCode PersistAvatar(ChatAvatar& avatar);

    std::pair<ChatResultCode, boost::optional<ChatAvatar>> CreateAvatar(const std::wstring& name,
        const std::wstring& address, uint32_t userId, uint32_t loginAttributes,
        const std::wstring& loginLocation);

    ChatResultCode LoginAvatar(ChatAvatar& avatar);

    void LogoutAvatar(uint32_t avatarId);

private:
    std::unordered_map<std::wstring, ChatAvatar> onlineAvatars_;
    sqlite3* db_;
};
