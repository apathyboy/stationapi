
#pragma once

#include "ChatAvatar.hpp"

#include <boost/optional.hpp>

#include <string>
#include <unordered_map>

struct sqlite3;

class ChatAvatarService {
public:
    explicit ChatAvatarService(sqlite3* db);
    ~ChatAvatarService();

    boost::optional<ChatAvatar> GetAvatarByNameAndAddress(const std::wstring& name, const std::wstring& address);

private:
    boost::optional<ChatAvatar> GetOnlineAvatarByNameAndAddress(const std::wstring& name, const std::wstring& address);
    boost::optional<ChatAvatar> GetPersistedAvatarByNameAndAddress(const std::wstring& name, const std::wstring& address);

    std::unordered_map<std::wstring, ChatAvatar> onlineAvatars_;
    sqlite3* db_;
};
