
#pragma once

#include "Contact.hpp"
#include "ChatEnums.hpp"

#include <vector>

class ChatAvatarService;
struct sqlite3;

class ContactService {
public:
    ContactService(ChatAvatarService* avatarService, sqlite3* db);
    ~ContactService();

    ChatResultCode AddFriend(uint32_t srcAvatarId, const std::wstring& srcAddress, const std::wstring& destName, const std::wstring& destAddress, const std::wstring& comment);

    ChatResultCode RemoveFriend(uint32_t srcAvatarId, const std::wstring& srcAddress, const std::wstring& destName, const std::wstring& destAddress);

    std::pair<ChatResultCode, std::vector<FriendStatus>> GetFriendStatus(uint32_t srcAvatarId, const std::wstring& srcAddress);

    ChatResultCode AddIgnore(uint32_t srcAvatarId, const std::wstring& srcAddress, const std::wstring& destName, const std::wstring& destAddress);

    ChatResultCode RemoveIgnore(uint32_t srcAvatarId, const std::wstring& srcAddress, const std::wstring& destName, const std::wstring& destAddress);
    
    std::pair<ChatResultCode, std::vector<IgnoreStatus>> GetIgnoreStatus(uint32_t srcAvatarId, const std::wstring& srcAddress);

private:
    ChatAvatarService* avatarService_;
    sqlite3* db_;
};