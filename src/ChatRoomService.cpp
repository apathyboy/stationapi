#include "ChatRoomService.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

#include <sqlite3.h>

ChatRoomService::ChatRoomService(sqlite3* db)
    : db_{db} {}

ChatRoomService::~ChatRoomService() {}

void ChatRoomService::LoadRoomsFromStorage() {
    rooms_.clear();

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

    LOG(INFO) << "Rooms loaded: " << rooms_.size();
}

std::pair<ChatResultCode, ChatRoom*> ChatRoomService::CreateRoom(uint32_t creatorId,
    const std::wstring& creatorName, const std::wstring& creatorAddress,
    const std::wstring& roomName, const std::wstring& roomTopic, const std::wstring& roomPassword,
    uint32_t roomAttributes, uint32_t maxRoomSize, const std::wstring& roomAddress,
    const std::wstring& srcAddress) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    ChatRoom* roomPtr = nullptr;

    if (!RoomExists(roomAddress + L"+" + roomName)) {
        rooms_.emplace_back(creatorId, creatorName, creatorAddress, roomName, roomTopic,
            roomPassword, roomAttributes, maxRoomSize, roomAddress, srcAddress);
        roomPtr = &rooms_.back();
        PersistNewRoom(*roomPtr);
    } else {
        result = ChatResultCode::ROOM_ALREADYEXISTS;
    }

    return std::make_pair(result, roomPtr);
}

ChatResultCode ChatRoomService::PersistNewRoom(ChatRoom& room) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    sqlite3_stmt* stmt;

    char sql[] = "INSERT INTO room (creator_id, creator_name, creator_address, room_name, "
                 "room_topic, room_password, room_prefix, room_address, room_attributes, "
                 "room_max_size, room_message_id, created_at, node_level) VALUES (@creator_id, "
                 "@creator_name, @creator_address, @room_name, @room_topic, @room_password, "
                 "@room_prefix, @room_address, @room_attributes, @room_max_size, @room_message_id, "
                 "@created_at, @node_level)";

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
        result = ChatResultCode::DBFAIL;
    } else {
        int creatorIdIdx = sqlite3_bind_parameter_index(stmt, "@creator_id");
        int creatorNameIdx = sqlite3_bind_parameter_index(stmt, "@creator_name");
        int creatorAddressIdx = sqlite3_bind_parameter_index(stmt, "@creator_address");
        int roomNameIdx = sqlite3_bind_parameter_index(stmt, "@room_name");
        int roomTopicIdx = sqlite3_bind_parameter_index(stmt, "@room_topic");
        int roomPasswordIdx = sqlite3_bind_parameter_index(stmt, "@room_password");
        int roomPrefixIdx = sqlite3_bind_parameter_index(stmt, "@room_prefix");
        int roomAddressIdx = sqlite3_bind_parameter_index(stmt, "@room_address");
        int roomAttributesIdx = sqlite3_bind_parameter_index(stmt, "@room_attributes");
        int roomMaxSizeIdx = sqlite3_bind_parameter_index(stmt, "@room_max_size");
        int roomMessageIdIdx = sqlite3_bind_parameter_index(stmt, "@room_message_id");
        int createdAtIdx = sqlite3_bind_parameter_index(stmt, "@created_at");
        int nodeLevelIdx = sqlite3_bind_parameter_index(stmt, "@node_level");

        sqlite3_bind_int(stmt, creatorIdIdx, room.creatorId_);

        auto creatorName = FromWideString(room.creatorName_);
        sqlite3_bind_text(stmt, creatorNameIdx, creatorName.c_str(), -1, 0);

        auto creatorAddress = FromWideString(room.creatorAddress_);
        sqlite3_bind_text(stmt, creatorAddressIdx, creatorAddress.c_str(), -1, 0);

        auto roomName = FromWideString(room.roomName_);
        sqlite3_bind_text(stmt, roomNameIdx, roomName.c_str(), -1, 0);

        auto roomTopic = FromWideString(room.roomTopic_);
        sqlite3_bind_text(stmt, roomTopicIdx, roomTopic.c_str(), -1, 0);

        auto roomPassword = FromWideString(room.roomPassword_);
        sqlite3_bind_text(stmt, roomPasswordIdx, roomPassword.c_str(), -1, 0);

        auto roomPrefix = FromWideString(room.roomPrefix_);
        sqlite3_bind_text(stmt, roomPrefixIdx, roomPrefix.c_str(), -1, 0);

        auto roomAddress = FromWideString(room.roomAddress_);
        sqlite3_bind_text(stmt, roomAddressIdx, roomAddress.c_str(), -1, 0);

        sqlite3_bind_int(stmt, roomAttributesIdx, room.roomAttributes_);
        sqlite3_bind_int(stmt, roomMaxSizeIdx, room.maxRoomSize_);
        sqlite3_bind_int(stmt, roomMessageIdIdx, room.roomMessageId_);
        sqlite3_bind_int(stmt, createdAtIdx, room.createTime_);
        sqlite3_bind_int(stmt, nodeLevelIdx, room.nodeLevel_);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            result = ChatResultCode::DBFAIL;
        } else {
            room.roomId_ = static_cast<uint32_t>(sqlite3_last_insert_rowid(db_));
        }
    }

    return result;
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

bool ChatRoomService::RoomExists(const std::wstring& roomAddress) const {
    return std::find_if(std::begin(rooms_), std::end(rooms_), [roomAddress](auto& room) {
        return roomAddress.compare(room.GetRoomAddress()) == 0;
    }) != std::end(rooms_);
}

ChatRoom* ChatRoomService::GetRoom(const std::wstring& roomAddress) {
    ChatRoom* room = nullptr;

    auto find_iter = std::find_if(std::begin(rooms_), std::end(rooms_),
        [roomAddress](auto& room) { return roomAddress.compare(room.GetRoomAddress()) == 0; });

    if (find_iter != std::end(rooms_)) {
        room = &(*find_iter);
    }

    return room;
}

void ChatRoomService::LogoutFromAllRooms(uint32_t avatarId) {
    for (auto& room : rooms_) {
        room.ExitRoom(avatarId);
    }
}
