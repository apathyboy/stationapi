#include "ChatRoomService.hpp"

#include <iostream>

#include <sqlite3.h>

ChatRoomService::ChatRoomService(sqlite3* db)
    : db_{db} {
    LoadRoomsFromStorage();
}

ChatRoomService::~ChatRoomService() {}

void ChatRoomService::LoadRoomsFromStorage() {
    sqlite3_stmt* stmt;

    char sql[] = "SELECT id, creator_id, creator_name, creator_address, room_name, room_topic, "
                 "room_password, room_prefix, room_address, room_attributes, room_max_size, "
                 "room_message_id, created_at, node_level FROM room";

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
        throw std::runtime_error("Error preparing SQL statement");
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        ChatRoom room;
        std::string tmp;
        room.roomId_ = sqlite3_column_int(stmt, 0);
        room.creatorId_ = sqlite3_column_int(stmt, 1);

        tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        room.creatorName_ = std::wstring{std::begin(tmp), std::end(tmp)};

        tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        room.creatorAddress_ = std::wstring{std::begin(tmp), std::end(tmp)};

        tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        room.roomName_ = std::wstring{std::begin(tmp), std::end(tmp)};

        tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        room.roomTopic_ = std::wstring{std::begin(tmp), std::end(tmp)};

        tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        room.roomPassword_ = std::wstring{std::begin(tmp), std::end(tmp)};

        tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        room.roomPrefix_ = std::wstring{std::begin(tmp), std::end(tmp)};

        tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        room.roomAddress_ = std::wstring{std::begin(tmp), std::end(tmp)};

        room.roomAttributes_ = sqlite3_column_int(stmt, 9);
        room.maxRoomSize_ = sqlite3_column_int(stmt, 10);
        room.roomMessageId_ = sqlite3_column_int(stmt, 11);
        room.createTime_ = sqlite3_column_int(stmt, 12);
        room.nodeLevel_ = sqlite3_column_int(stmt, 13);

        rooms_.emplace_back(std::move(room));
    }

    if (_DEBUG) {
        std::cout << "Rooms Loaded: " << rooms_.size();
    }
}

std::pair<ChatResultCode, ChatRoom*> ChatRoomService::CreateRoom(const std::wstring& roomName,
    const std::wstring& roomTopic, const std::wstring& roomPassword, uint32_t roomAttributes,
    uint32_t maxRoomSize, const std::wstring& roomAddress, const std::wstring& srcAddress) {
    return std::pair<ChatResultCode, ChatRoom*>();
}

std::vector<ChatRoom*> ChatRoomService::GetRoomSummaries(
    const std::wstring& startNode, const std::wstring& filter) {
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
