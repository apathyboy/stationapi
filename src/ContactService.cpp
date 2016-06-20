#include "ContactService.hpp"
#include "ChatAvatarService.hpp"

#include <sqlite3.h>

ContactService::ContactService(ChatAvatarService* avatarService, sqlite3* db)
    : avatarService_{avatarService}
    , db_{db} {}

ContactService::~ContactService() {}

ChatResultCode ContactService::AddFriend(uint32_t srcAvatarId, const std::wstring& srcAddress,
    const std::wstring& destName, const std::wstring& destAddress, const std::wstring& comment) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    boost::optional<ChatAvatar> destAvatar;

    std::tie(result, destAvatar) = avatarService_->GetAvatar(destName, destAddress);

    if (result == ChatResultCode::SUCCESS) {
        sqlite3_stmt* stmt;

        char sql[] = "INSERT INTO friend (avatar_id, friend_avatar_id) VALUES (@avatar_id, @friend_avatar_id)";

        if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
            result = ChatResultCode::DBFAIL;
        } else {
            int avatarIdIdx = sqlite3_bind_parameter_index(stmt, "@avatar_id");
            int friendAvatarIdIdx = sqlite3_bind_parameter_index(stmt, "@friend_avatar_id");

            sqlite3_bind_int(stmt, avatarIdIdx, srcAvatarId);
            sqlite3_bind_int(stmt, friendAvatarIdIdx, destAvatar->avatarId);

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                result = ChatResultCode::DBFAIL;
            }
        }
    } else {
        result = ChatResultCode::DESTAVATARDOESNTEXIST;
    }

    return result;
}

ChatResultCode ContactService::RemoveFriend(uint32_t srcAvatarId, const std::wstring& srcAddress,
    const std::wstring& destName, const std::wstring& destAddress) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    boost::optional<ChatAvatar> destAvatar;

    std::tie(result, destAvatar) = avatarService_->GetAvatar(destName, destAddress);

    if (result == ChatResultCode::SUCCESS) {
        sqlite3_stmt* stmt;

        char sql[] = "DELETE FROM friend WHERE avatar_id = @avatar_id AND friend_avatar_id = @friend_avatar_id";

        if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
            result = ChatResultCode::DBFAIL;
        } else {
            int avatarIdIdx = sqlite3_bind_parameter_index(stmt, "@avatar_id");
            int friendAvatarIdIdx = sqlite3_bind_parameter_index(stmt, "@friend_avatar_id");

            sqlite3_bind_int(stmt, avatarIdIdx, srcAvatarId);
            sqlite3_bind_int(stmt, friendAvatarIdIdx, destAvatar->avatarId);

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                result = ChatResultCode::DBFAIL;
            }
        }
    } else {
        result = ChatResultCode::DESTAVATARDOESNTEXIST;
    }

    return result;
}

std::pair<ChatResultCode, std::vector<FriendStatus>> ContactService::GetFriendStatus(
    uint32_t srcAvatarId, const std::wstring& srcAddress) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    std::vector<FriendStatus> friendList;
    sqlite3_stmt* stmt;

    char sql[] = "SELECT avatar.name, avatar.address FROM avatar INNER JOIN friend ON avatar.id = "
                 "friend.friend_avatar_id WHERE friend.avatar_id = @avatar_id";

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
        result = ChatResultCode::DBFAIL;
    } else {
        int avatarIdIdx = sqlite3_bind_parameter_index(stmt, "@avatar_id");
        sqlite3_bind_int(stmt, avatarIdIdx, srcAvatarId);

        FriendStatus status;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string tmp;

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
            status.name = std::wstring{std::begin(tmp), std::end(tmp)};

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            status.address = std::wstring{std::begin(tmp), std::end(tmp)};

            status.status = avatarService_->IsAvatarOnline(status.name, status.address) ? 1 : 0;

            friendList.push_back(status);
        }
    }

    return std::make_pair(result, friendList);
}

ChatResultCode ContactService::AddIgnore(uint32_t srcAvatarId, const std::wstring& srcAddress,
    const std::wstring& destName, const std::wstring& destAddress) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    boost::optional<ChatAvatar> destAvatar;

    std::tie(result, destAvatar) = avatarService_->GetAvatar(destName, destAddress);

    if (result == ChatResultCode::SUCCESS) {
        sqlite3_stmt* stmt;

        char sql[] = "INSERT INTO ignore (avatar_id, ignore_avatar_id) VALUES (@avatar_id, @ignore_avatar_id)";

        if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
            result = ChatResultCode::DBFAIL;
        } else {
            int avatarIdIdx = sqlite3_bind_parameter_index(stmt, "@avatar_id");
            int ignoreAvatarIdIdx = sqlite3_bind_parameter_index(stmt, "@ignore_avatar_id");

            sqlite3_bind_int(stmt, avatarIdIdx, srcAvatarId);
            sqlite3_bind_int(stmt, ignoreAvatarIdIdx, destAvatar->avatarId);

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                result = ChatResultCode::DBFAIL;
            }
        }
    } else {
        result = ChatResultCode::DESTAVATARDOESNTEXIST;
    }

    return result;
}

ChatResultCode ContactService::RemoveIgnore(uint32_t srcAvatarId, const std::wstring& srcAddress,
    const std::wstring& destName, const std::wstring& destAddress) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    boost::optional<ChatAvatar> destAvatar;

    std::tie(result, destAvatar) = avatarService_->GetAvatar(destName, destAddress);

    if (result == ChatResultCode::SUCCESS) {
        sqlite3_stmt* stmt;

        char sql[] = "DELETE FROM ignore WHERE avatar_id = @avatar_id AND ignore_avatar_id = @ignore_avatar_id";

        if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
            result = ChatResultCode::DBFAIL;
        } else {
            int avatarIdIdx = sqlite3_bind_parameter_index(stmt, "@avatar_id");
            int ignoreAvatarIdIdx = sqlite3_bind_parameter_index(stmt, "@ignore_avatar_id");

            sqlite3_bind_int(stmt, avatarIdIdx, srcAvatarId);
            sqlite3_bind_int(stmt, ignoreAvatarIdIdx, destAvatar->avatarId);

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                result = ChatResultCode::DBFAIL;
            }
        }
    } else {
        result = ChatResultCode::DESTAVATARDOESNTEXIST;
    }

    return result;
}

std::pair<ChatResultCode, std::vector<IgnoreStatus>> ContactService::GetIgnoreStatus(
    uint32_t srcAvatarId, const std::wstring& srcAddress) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    std::vector<IgnoreStatus> ignoreList;
    sqlite3_stmt* stmt;

    char sql[] = "SELECT avatar.name, avatar.address FROM avatar INNER JOIN ignore ON avatar.id = "
                 "ignore.ignore_avatar_id WHERE ignore.avatar_id = @avatar_id";

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
        result = ChatResultCode::DBFAIL;
    } else {
        int avatarIdIdx = sqlite3_bind_parameter_index(stmt, "@avatar_id");
        sqlite3_bind_int(stmt, avatarIdIdx, srcAvatarId);

        IgnoreStatus status;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string tmp;

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
            status.name = std::wstring{std::begin(tmp), std::end(tmp)};

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
            status.address = std::wstring{std::begin(tmp), std::end(tmp)};

            ignoreList.push_back(status);
        }
    }

    return std::make_pair(result, ignoreList);
}
