
#pragma once

#include <memory>
#include <string>
#include <unordered_map>

struct ChatAvatar;
struct SwgChatConfig;

class ChatAvatarService {
public:
    explicit ChatAvatarService(SwgChatConfig* config);
    ~ChatAvatarService();

    ChatAvatar* GetAvatarByNameAndAddress(const std::wstring& name, const std::wstring& address);
    ChatAvatar* GetOnlineAvatarByNameAndAddress(const std::wstring& name, const std::wstring& address);
    ChatAvatar* GetPersistedAvatarByNameAndAddress(const std::wstring& name, const std::wstring& address);

private:
    SwgChatConfig* config_;

    std::unordered_map<std::wstring, std::unique_ptr<ChatAvatar>> onlineAvatars_;
};
