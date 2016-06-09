#include "ChatRoomService.hpp"

ChatRoomService::ChatRoomService(sqlite3 * db)
    : db_{db} {
    LoadRoomsFromStorage();
}

ChatRoomService::~ChatRoomService() {}

void ChatRoomService::LoadRoomsFromStorage() {}

std::pair<ChatResultCode, ChatRoom*> ChatRoomService::CreateRoom(const std::wstring & roomName, const std::wstring & roomTopic, const std::wstring & roomPassword, uint32_t roomAttributes, uint32_t maxRoomSize, const std::wstring & roomAddress, const std::wstring & srcAddress) {
    return std::pair<ChatResultCode, ChatRoom*>();
}

std::vector<ChatRoom*> ChatRoomService::GetRoomSummaries(const std::wstring & startNode, const std::wstring & filter) {
    std::vector<ChatRoom*> rooms;

    for (auto& room : rooms_) {
        auto& roomAddress = room.GetRoomAddress();
        if (roomAddress.compare(0, startNode.length(), startNode) == 0) {
            rooms.push_back(&room);
        }
    }

    return rooms;
}

std::pair<ChatResultCode, ChatRoom*> ChatRoomService::GetRoom() {
    return std::pair<ChatResultCode, ChatRoom*>();
}
