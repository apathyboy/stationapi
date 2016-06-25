
#pragma once

#include "ChatAvatar.hpp"
#include "ChatEnums.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <unordered_map>

struct sqlite3;

class ChatAvatarService {
public:
    explicit ChatAvatarService(sqlite3* db);
    ~ChatAvatarService();
    
    ChatAvatar* GetAvatar(const std::wstring& name, const std::wstring& address);
    ChatAvatar* GetAvatar(uint32_t avatarId);

    ChatAvatar* CreateAvatar(const std::wstring& name,
                             const std::wstring& address, uint32_t userId, uint32_t loginAttributes,
                             const std::wstring& loginLocation);

    void LoginAvatar(ChatAvatar* avatar);
    void LogoutAvatar(uint32_t avatarId);

    void PersistAvatar(const ChatAvatar* avatar);
    void PersistFriend(uint32_t srcAvatarId, uint32_t destAvatarId, const std::wstring& comment);
    void PersistIgnore(uint32_t srcAvatarId, uint32_t destAvatarId);

    void RemoveFriend(uint32_t srcAvatarId, uint32_t destAvatarId);
    void RemoveIgnore(uint32_t srcAvatarId, uint32_t destAvatarId);

    void UpdateFriendComment(uint32_t srcAvatarId, uint32_t destAvatarId, const std::wstring& comment);

    const std::vector<ChatAvatar*>& GetOnlineAvatars() const { return onlineAvatars_; }
    
private:
    ChatAvatar* GetCachedAvatar(const std::wstring& name, const std::wstring& address);
    ChatAvatar* GetCachedAvatar(uint32_t avatarId);

    std::unique_ptr<ChatAvatar> LoadStoredAvatar(const std::wstring& name, const std::wstring& address);
    std::unique_ptr<ChatAvatar> LoadStoredAvatar(uint32_t avatarId);

    void InsertAvatar(ChatAvatar* avatar);
    void UpdateAvatar(const ChatAvatar* avatar);
    void DeleteAvatar(ChatAvatar* avatar);

    void LoadFriendList(ChatAvatar* avatar);
    void LoadIgnoreList(ChatAvatar* avatar);

    std::vector<std::unique_ptr<ChatAvatar>> avatarCache_;
    std::vector<ChatAvatar*> onlineAvatars_;
    sqlite3* db_;
};
