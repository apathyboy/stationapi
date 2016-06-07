#include "ChatAvatarService.hpp"
#include "ChatAvatar.hpp"
#include "StringUtils.hpp"

#include <sqlite3.h>

#include <iostream>

ChatAvatarService::ChatAvatarService(sqlite3* db)
    : db_{db} {}

ChatAvatarService::~ChatAvatarService() {}

boost::optional<ChatAvatar> ChatAvatarService::GetAvatarByNameAndAddress(
    const std::wstring& name, const std::wstring& address) {
    auto avatar = GetOnlineAvatarByNameAndAddress(name, address);

    if (!avatar) {
        avatar = GetPersistedAvatarByNameAndAddress(name, address);
    }

    return avatar;
}

boost::optional<ChatAvatar> ChatAvatarService::GetOnlineAvatarByNameAndAddress(
    const std::wstring& name, const std::wstring& address) {
    boost::optional<ChatAvatar> avatar;

    auto find_iter = onlineAvatars_.find(name + L"+" + address);
    if (find_iter != std::end(onlineAvatars_)) {
        avatar = find_iter->second;
    }

    return avatar;
}

boost::optional<ChatAvatar> ChatAvatarService::GetPersistedAvatarByNameAndAddress(
    const std::wstring& name, const std::wstring& address) {
    boost::optional<ChatAvatar> avatar;
    sqlite3_stmt* res;

    char* sql = "SELECT id, user_id, name, address, attributes FROM avatar WHERE name = @name AND address = @address";
    auto rc = sqlite3_prepare_v2(db_, sql, -1, &res, 0);

    if (rc != SQLITE_OK) {
        throw std::runtime_error("Error preparing statement");
    }

    std::string nameStr = FromWideString(name);
    std::string addressStr = FromWideString(address);

    int nameIdx = sqlite3_bind_parameter_index(res, "@name");
    int addressIdx = sqlite3_bind_parameter_index(res, "@address");

    sqlite3_bind_text(res, nameIdx, nameStr.c_str(), -1, 0);
    sqlite3_bind_text(res, addressIdx, addressStr.c_str(), -1, 0);

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW) {
        avatar = ChatAvatar{};
        avatar->avatarId = sqlite3_column_int(res, 0);
        avatar->userId = sqlite3_column_int(res, 1);

        auto tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
        avatar->name = std::wstring{std::begin(tmp), std::end(tmp)};

        tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
        avatar->address = std::wstring(std::begin(tmp), std::end(tmp));

        avatar->attributes = sqlite3_column_int(res, 4);
    }

    sqlite3_finalize(res);

    return avatar;
}
