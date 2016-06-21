
#pragma once

#include <string>

struct FriendStatus {
    std::wstring name;
    std::wstring address;
    std::wstring commment = L"";
    uint16_t status;
};

template <typename StreamT>
void write(StreamT& ar, const FriendStatus& data) {
    write(ar, data.name);
    write(ar, data.address);
    write(ar, data.commment);
    write(ar, data.status);
}

struct IgnoreStatus {
    std::wstring name;
    std::wstring address;
};

template <typename StreamT>
void write(StreamT& ar, const IgnoreStatus& data) {
    write(ar, data.name);
    write(ar, data.address);
}
