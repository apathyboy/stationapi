
#pragma once

#include "ChatEnums.hpp"
#include "ChatRoom.hpp"

#include <boost/optional.hpp>

#include <cstdint>
#include <set>
#include <vector>

struct sqlite3;

class ChatRoomService {
public:
    explicit ChatRoomService(sqlite3* db);
    ~ChatRoomService();

    void LoadRoomsFromStorage();

    std::pair<ChatResultCode, ChatRoom*> CreateRoom(const std::wstring& roomName,
        const std::wstring& roomTopic, const std::wstring& roomPassword, uint32_t roomAttributes,
        uint32_t maxRoomSize, const std::wstring& roomAddress, const std::wstring& srcAddress);

    std::vector<ChatRoom*> GetRoomSummaries(const std::wstring& startNode, const std::wstring& filter = L"");

    std::pair<ChatResultCode, ChatRoom*> GetRoom();

private:
    std::vector<ChatRoom> rooms_;
    sqlite3* db_;
};
