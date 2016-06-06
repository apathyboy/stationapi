
#pragma once

#include <cstdint>
#include <string>

enum class AvatarAttribute : uint32_t {
    INVISIBLE = 1 << 0,
    GM = 1 << 1,
    SUPERGM = 1 << 2,
    SUPERSNOOP = 1 << 3,
    EXTENDED = 1 << 4
};

struct ChatAvatar {
    uint32_t avatarId = 0;
    uint32_t userId = 0;
    std::wstring name = L"";
    std::wstring address = L"";
    uint32_t attributes = 0;
    std::wstring loginLocation = L"";
    std::wstring server = L"";
    std::wstring gateway = L"";
    uint32_t serverId = 0;
    uint32_t gatewayId = 0;
    std::wstring email = L"";
    uint32_t inboxLimit = 0;
    std::wstring statusMessage = L"";
    bool isOnline = false;
};

template <typename StreamT>
void write(StreamT& ar, const ChatAvatar& data) {
    write(ar, data.avatarId);
    write(ar, data.userId);
    write(ar, data.name);
    write(ar, data.address);
    write(ar, data.attributes);
    write(ar, data.loginLocation);
    write(ar, data.server);
    write(ar, data.gateway);
    write(ar, data.serverId);
    write(ar, data.gatewayId);
}