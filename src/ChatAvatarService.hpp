
#pragma once

#include <string>

struct ChatAvatar;
struct SwgChatConfig;

class ChatAvatarService {
public:
    explicit ChatAvatarService(SwgChatConfig* config);

    ChatAvatar* GetAvatarByNameAndAddress(const std::wstring& name, const std::wstring& address);

private:
    SwgChatConfig* config_;
};