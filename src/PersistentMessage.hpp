
#pragma once

#include <cstdint>
#include <string>

enum class PersistentState : uint32_t {
    NEW = 1,
    UNREAD,
    READ,
    TRASH,
    DELETED
};

struct PersistentHeader {
    uint32_t messageId = 0;
    uint32_t avatarId;
    std::wstring fromName;
    std::wstring fromAddress;
    std::wstring subject;
    uint32_t sentTime = 0;
    PersistentState status = PersistentState::NEW;
    std::wstring folder = L"";
    std::wstring category = L"";
};

struct PersistentMessage {
    PersistentHeader header;
    std::wstring message;
    std::wstring oob;
};


template <typename StreamT>
void write(StreamT& ar, const PersistentHeader& data) {
    write(ar, data.messageId);
    write(ar, data.avatarId);
    write(ar, data.fromName);
    write(ar, data.fromAddress);
    write(ar, data.subject);
    write(ar, data.sentTime);
    write(ar, data.status);
}


template <typename StreamT>
void write(StreamT& ar, const PersistentMessage& data) {
    write(ar, data.header);
    write(ar, data.message);
    write(ar, data.oob);
}
