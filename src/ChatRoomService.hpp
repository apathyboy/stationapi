
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

    std::pair<ChatResultCode, ChatRoom*> CreateRoom(uint32_t creatorId,
        const std::wstring& creatorName, const std::wstring& creatorAddress,
        const std::wstring& roomName, const std::wstring& roomTopic,
        const std::wstring& roomPassword, uint32_t roomAttributes, uint32_t maxRoomSize,
        const std::wstring& roomAddress, const std::wstring& srcAddress);

    ChatResultCode PersistNewRoom(ChatRoom& avatar);

    std::vector<ChatRoom*> GetRoomSummaries(
        const std::wstring& startNode, const std::wstring& filter = L"");

    bool RoomExists(const std::wstring& roomName, const std::wstring& roomAddress) const;
    ChatRoom* GetRoom(const std::wstring& roomName, const std::wstring& roomAddress);

private:
    std::vector<ChatRoom> rooms_;
    sqlite3* db_;
};
