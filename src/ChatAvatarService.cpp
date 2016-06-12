#include "ChatAvatarService.hpp"
#include "ChatAvatar.hpp"
#include "StringUtils.hpp"

#include <sqlite3.h>

ChatAvatarService::ChatAvatarService(sqlite3* db)
    : db_{db} {}

ChatAvatarService::~ChatAvatarService() {}

void ChatAvatarService::ClearOnlineAvatars() {
    onlineAvatars_.clear();
}

std::pair<ChatResultCode, boost::optional<ChatAvatar>> ChatAvatarService::GetAvatar(
    const std::wstring& name, const std::wstring& address) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    boost::optional<ChatAvatar> avatar;

    std::tie(result, avatar) = GetOnlineAvatar(name, address);

    if (result != ChatResultCode::SUCCESS) {
        std::tie(result, avatar) = GetPersistedAvatar(name, address);
    }

    return std::make_pair(result, avatar);
}

ChatAvatar* ChatAvatarService::GetOnlineAvatar(
    uint32_t avatarId) {
    ChatAvatar* avatar;

    auto find_iter = std::find_if(std::begin(onlineAvatars_), std::end(onlineAvatars_),
        [avatarId](auto& avatar) { return avatar.second.avatarId == avatarId; });
    if (find_iter != std::end(onlineAvatars_)) {
        avatar = &find_iter->second;
    }

    return avatar;
}

bool ChatAvatarService::IsAvatarOnline(const std::wstring& name, const std::wstring& address) {
    return onlineAvatars_.find(name + L"+" + address) != std::end(onlineAvatars_);
}

std::pair<ChatResultCode, boost::optional<ChatAvatar>> ChatAvatarService::GetOnlineAvatar(
    const std::wstring& name, const std::wstring& address) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    boost::optional<ChatAvatar> avatar;

    auto find_iter = onlineAvatars_.find(name + L"+" + address);
    if (find_iter != std::end(onlineAvatars_)) {
        avatar = find_iter->second;
    } else {
        result = ChatResultCode::DESTAVATARDOESNTEXIST;
    }

    return std::make_pair(result, avatar);
}

std::pair<ChatResultCode, boost::optional<ChatAvatar>> ChatAvatarService::GetPersistedAvatar(
    const std::wstring& name, const std::wstring& address) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    boost::optional<ChatAvatar> avatar;
    sqlite3_stmt* stmt;

    char sql[] = "SELECT id, user_id, name, address, attributes FROM avatar WHERE name = @name AND "
                 "address = @address";

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
        result = ChatResultCode::DBFAIL;
    } else {
        std::string nameStr = FromWideString(name);
        std::string addressStr = FromWideString(address);

        int nameIdx = sqlite3_bind_parameter_index(stmt, "@name");
        int addressIdx = sqlite3_bind_parameter_index(stmt, "@address");

        sqlite3_bind_text(stmt, nameIdx, nameStr.c_str(), -1, 0);
        sqlite3_bind_text(stmt, addressIdx, addressStr.c_str(), -1, 0);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            avatar = ChatAvatar{};
            avatar->avatarId = sqlite3_column_int(stmt, 0);
            avatar->userId = sqlite3_column_int(stmt, 1);

            auto tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            avatar->name = std::wstring{std::begin(tmp), std::end(tmp)};

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            avatar->address = std::wstring(std::begin(tmp), std::end(tmp));

            avatar->attributes = sqlite3_column_int(stmt, 4);
        } else {
            result = ChatResultCode::DESTAVATARDOESNTEXIST;
        }
    }

    sqlite3_finalize(stmt);

    return std::make_pair(result, avatar);
}

ChatResultCode ChatAvatarService::PersistNewAvatar(ChatAvatar& avatar) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    sqlite3_stmt* stmt;

    char sql[] = "INSERT INTO avatar (user_id, name, address, attributes) VALUES (@user_id, @name, "
                 "@address, @attributes)";

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
        result = ChatResultCode::DBFAIL;
    } else {
        std::string nameStr = FromWideString(avatar.name);
        std::string addressStr = FromWideString(avatar.address);

        int userIdIdx = sqlite3_bind_parameter_index(stmt, "@user_id");
        int nameIdx = sqlite3_bind_parameter_index(stmt, "@name");
        int addressIdx = sqlite3_bind_parameter_index(stmt, "@address");
        int attributesIdx = sqlite3_bind_parameter_index(stmt, "@attributes");

        sqlite3_bind_int(stmt, userIdIdx, avatar.userId);
        sqlite3_bind_text(stmt, nameIdx, nameStr.c_str(), -1, 0);
        sqlite3_bind_text(stmt, addressIdx, addressStr.c_str(), -1, 0);
        sqlite3_bind_int(stmt, attributesIdx, avatar.attributes);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            result = ChatResultCode::DBFAIL;
        } else {
            avatar.avatarId = static_cast<uint32_t>(sqlite3_last_insert_rowid(db_));
        }
    }

    return result;
}

ChatResultCode ChatAvatarService::PersistAvatar(ChatAvatar & avatar) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    sqlite3_stmt* stmt;

    char sql[] = "UPDATE avatar SET user_id = @user_id, name = @name, address = @address, attributes = @attributes "
                 "WHERE id = @avatar_id";

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
        result = ChatResultCode::DBFAIL;
    } else {
        std::string nameStr = FromWideString(avatar.name);
        std::string addressStr = FromWideString(avatar.address);

        int userIdIdx = sqlite3_bind_parameter_index(stmt, "@user_id");
        int nameIdx = sqlite3_bind_parameter_index(stmt, "@name");
        int addressIdx = sqlite3_bind_parameter_index(stmt, "@address");
        int attributesIdx = sqlite3_bind_parameter_index(stmt, "@attributes");
        int avatarIdIdx = sqlite3_bind_parameter_index(stmt, "@avatar_id");

        sqlite3_bind_int(stmt, userIdIdx, avatar.userId);
        sqlite3_bind_text(stmt, nameIdx, nameStr.c_str(), -1, 0);
        sqlite3_bind_text(stmt, addressIdx, addressStr.c_str(), -1, 0);
        sqlite3_bind_int(stmt, attributesIdx, avatar.attributes);
        sqlite3_bind_int(stmt, avatarIdIdx, avatar.avatarId);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            result = ChatResultCode::DBFAIL;
        }
    }

    return result;
}

std::pair<ChatResultCode, boost::optional<ChatAvatar>> ChatAvatarService::CreateAvatar(
    const std::wstring& name, const std::wstring& address, uint32_t userId,
    uint32_t loginAttributes, const std::wstring& loginLocation) {
    ChatAvatar avatar{name, address, userId, loginAttributes, loginLocation};

    auto result = PersistNewAvatar(avatar);

    return std::make_pair(result, avatar);
}

ChatResultCode ChatAvatarService::LoginAvatar(ChatAvatar& avatar) {
    ChatResultCode result = ChatResultCode::SUCCESS;

    if (!IsAvatarOnline(avatar.name, avatar.address)) {
        avatar.isOnline = true;
        onlineAvatars_.insert(std::make_pair(avatar.name + L"+" + avatar.address, avatar));
    } else {
        result = ChatResultCode::DUPLICATELOGIN;
    }

    return result;
}

void ChatAvatarService::LogoutAvatar(uint32_t avatarId) {
    auto find_iter = std::find_if(std::begin(onlineAvatars_), std::end(onlineAvatars_), [avatarId](auto& avatarIter) {
        return avatarIter.second.avatarId == avatarId;
    });

    if (find_iter != std::end(onlineAvatars_)) {
        onlineAvatars_.erase(find_iter);
    }
}
