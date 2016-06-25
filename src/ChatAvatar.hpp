
#pragma once

#include "Contact.hpp"
#include "Serialization.hpp"

#include <cstdint>
#include <string>
#include <vector>

class ChatAvatarService;

enum class AvatarAttribute : uint32_t {
    INVISIBLE = 1 << 0,
    GM = 1 << 1,
    SUPERGM = 1 << 2,
    SUPERSNOOP = 1 << 3,
    EXTENDED = 1 << 4
};

class ChatAvatar {
public:
    explicit ChatAvatar(ChatAvatarService* avatarService);
    ChatAvatar(ChatAvatarService* avatarService, const std::wstring& name, const std::wstring& address, uint32_t userId,
               uint32_t attributes, const std::wstring& loginLocation);

    const uint32_t GetAvatarId() const { return avatarId_; }
    const uint32_t GetUserId() const { return userId_; }
    const std::wstring& GetName() const { return name_; }
    const std::wstring& GetAddress() const { return address_; }
    const uint32_t GetAttributes() const { return attributes_; }
    void SetAttributes(const uint32_t attributes);
    const std::wstring& GetLoginLocation() const { return loginLocation_; }
    const std::wstring& GetServer() const { return server_; }
    const std::wstring& GetGateway() const { return gateway_; }
    const uint32_t GetServerId() const { return serverId_; }
    const uint32_t GetGatewayId() const { return gatewayId_; }
    const std::wstring& GetEmail() const { return email_; }
    const uint32_t GetInboxLimit() const { return inboxLimit_; }
    const std::wstring& GetStatusMessage() const { return statusMessage_; }
    const bool IsOnline() const { return isOnline_; }

    void AddFriend(ChatAvatar* avatar, const std::wstring& comment = L"");
    void RemoveFriend(ChatAvatar* avatar);
    void UpdateFriendComment(const ChatAvatar* avatar, const std::wstring& comment);
    bool IsFriend(const ChatAvatar* avatar);

    const std::vector<FriendContact> GetFriendList() const { return friendList_; }

    void AddIgnore(ChatAvatar* avatar);
    void RemoveIgnore(ChatAvatar* avatar);
    bool IsIgnored(const ChatAvatar* avatar);

    const std::vector<IgnoreContact> GetIgnoreList() const { return ignoreList_; }

private:
    friend class ChatAvatarService;

    ChatAvatarService* avatarService_;

    uint32_t avatarId_ = 0;
    uint32_t userId_ = 0;
    std::wstring name_ = L"";
    std::wstring address_ = L"";
    uint32_t attributes_ = 0;
    std::wstring loginLocation_ = L"";
    std::wstring server_ = L"";
    std::wstring gateway_ = L"";
    uint32_t serverId_ = 0;
    uint32_t gatewayId_ = 0;
    std::wstring email_ = L"";
    uint32_t inboxLimit_ = 0;
    std::wstring statusMessage_ = L"";
    bool isOnline_ = false;

    std::vector<FriendContact> friendList_;
    std::vector<IgnoreContact> ignoreList_;
};

template <typename StreamT>
void write(StreamT& ar, const ChatAvatar* data) {
    write(ar, data->GetAvatarId());
    write(ar, data->GetUserId());
    write(ar, data->GetName());
    write(ar, data->GetAddress());
    write(ar, data->GetAttributes());
    write(ar, data->GetLoginLocation());
    write(ar, data->GetServer());
    write(ar, data->GetGateway());
    write(ar, data->GetServerId());
    write(ar, data->GetGatewayId());
}
