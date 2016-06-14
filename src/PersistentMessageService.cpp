#include "PersistentMessageService.hpp"

#include "StringUtils.hpp"

#include <sqlite3.h>

PersistentMessageService::PersistentMessageService(sqlite3* db)
    : db_{db} {}

PersistentMessageService::~PersistentMessageService() {}

ChatResultCode PersistentMessageService::PersistNewMessage(PersistentMessage& message) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    sqlite3_stmt* stmt;

    char sql[] = "INSERT INTO persistent_message (avatar_id, from_name, from_address, subject, "
                 "sent_time, status, "
                 "folder, category, message, oob) VALUES (@avatar_id, @from_name, @from_address, "
                 "@subject, @sent_time, @status, @folder, @category, @message, @oob)";

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
        result = ChatResultCode::DBFAIL;
    } else {
        int avatarIdIdx = sqlite3_bind_parameter_index(stmt, "@avatar_id");
        int fromNameIdx = sqlite3_bind_parameter_index(stmt, "@from_name");
        int fromAddressIdx = sqlite3_bind_parameter_index(stmt, "@from_address");
        int subjectIdx = sqlite3_bind_parameter_index(stmt, "@subject");
        int sentTimeIdx = sqlite3_bind_parameter_index(stmt, "@sent_time");
        int statusIdx = sqlite3_bind_parameter_index(stmt, "@status");
        int folderIdx = sqlite3_bind_parameter_index(stmt, "@folder");
        int categoryIdx = sqlite3_bind_parameter_index(stmt, "@category");
        int messageIdx = sqlite3_bind_parameter_index(stmt, "@message");
        int oobIdx = sqlite3_bind_parameter_index(stmt, "@oob");

        sqlite3_bind_int(stmt, avatarIdIdx, message.header.avatarId);

        std::string fromName = FromWideString(message.header.fromName);
        sqlite3_bind_text(stmt, fromNameIdx, fromName.c_str(), -1, 0);

        std::string fromAddress = FromWideString(message.header.fromAddress);
        sqlite3_bind_text(stmt, fromAddressIdx, fromAddress.c_str(), -1, 0);

        std::string subject = FromWideString(message.header.subject);
        sqlite3_bind_text(stmt, subjectIdx, subject.c_str(), -1, 0);

        sqlite3_bind_int(stmt, sentTimeIdx, message.header.sentTime);
        sqlite3_bind_int(stmt, statusIdx, static_cast<uint32_t>(message.header.status));

        std::string folder = FromWideString(message.header.folder);
        sqlite3_bind_text(stmt, folderIdx, folder.c_str(), -1, 0);

        std::string category = FromWideString(message.header.category);
        sqlite3_bind_text(stmt, categoryIdx, category.c_str(), -1, 0);

        std::string msg = FromWideString(message.message);
        sqlite3_bind_text(stmt, messageIdx, msg.c_str(), -1, 0);

        std::string oob = FromWideString(message.oob);
        sqlite3_bind_text(stmt, oobIdx, oob.c_str(), -1, 0);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            result = ChatResultCode::DBFAIL;
        } else {
            message.header.messageId = static_cast<uint32_t>(sqlite3_last_insert_rowid(db_));
        }
    }

    return result;
}

std::vector<PersistentHeader> PersistentMessageService::GetMessageHeaders(uint32_t avatarId) {
    std::vector<PersistentHeader> headers;
    sqlite3_stmt* stmt;

    char sql[]
        = "SELECT id, avatar_id, from_name, from_address, subject, sent_time, status, "
          "folder, category, message, oob FROM persistent_message WHERE avatar_id = @avatar_id";

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
        throw std::runtime_error("Error preparing SQL statement");
    } else {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            PersistentHeader header;

            header.messageId = sqlite3_column_int(stmt, 0);
            header.avatarId = sqlite3_column_int(stmt, 1);

            auto tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            header.fromName = std::wstring(std::begin(tmp), std::end(tmp));

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            header.fromAddress = std::wstring(std::begin(tmp), std::end(tmp));

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            header.subject = std::wstring(std::begin(tmp), std::end(tmp));

            header.sentTime = sqlite3_column_int(stmt, 5);
            header.status = static_cast<PersistentState>(sqlite3_column_int(stmt, 6));

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
            header.folder = std::wstring(std::begin(tmp), std::end(tmp));

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
            header.category = std::wstring(std::begin(tmp), std::end(tmp));

            headers.push_back(std::move(header));
        }
    }

    return headers;
}

std::pair<ChatResultCode, boost::optional<PersistentMessage>>
PersistentMessageService::GetPersistentMessage(uint32_t avatarId, uint32_t messageId) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    boost::optional<PersistentMessage> message;
    sqlite3_stmt* stmt;

    char sql[] = "SELECT id, avatar_id, from_name, from_address, subject, sent_time, status, "
                 "folder, category, message, oob FROM persistent_message WHERE id = @message_id "
                 "AND avatar_id = @avatar_id";

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
        result = ChatResultCode::DBFAIL;
    } else {
        int messageIdIdx = sqlite3_bind_parameter_index(stmt, "@message_id");
        int avatarIdIdx = sqlite3_bind_parameter_index(stmt, "@avatar_id");

        sqlite3_bind_int(stmt, messageIdIdx, messageId);
        sqlite3_bind_int(stmt, avatarIdIdx, avatarId);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string tmp;
            message = PersistentMessage{};
            message->header.messageId = messageId;
            message->header.avatarId = avatarId;

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            message->header.fromName = std::wstring(std::begin(tmp), std::end(tmp));

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            message->header.fromAddress = std::wstring(std::begin(tmp), std::end(tmp));

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            message->header.subject = std::wstring(std::begin(tmp), std::end(tmp));

            message->header.sentTime = sqlite3_column_int(stmt, 5);
            message->header.status = static_cast<PersistentState>(sqlite3_column_int(stmt, 6));

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
            message->header.folder = std::wstring(std::begin(tmp), std::end(tmp));

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
            message->header.category = std::wstring(std::begin(tmp), std::end(tmp));

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
            message->message = std::wstring(std::begin(tmp), std::end(tmp));

            tmp = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
            message->oob = std::wstring(std::begin(tmp), std::end(tmp));
        } else {
            result = ChatResultCode::DESTAVATARDOESNTEXIST;
        }
    }

    sqlite3_finalize(stmt);

    return std::make_pair(result, message);
}

ChatResultCode PersistentMessageService::UpdateMessageStatus(
    uint32_t avatarId, uint32_t messageId, PersistentState status) {
    ChatResultCode result = ChatResultCode::SUCCESS;
    sqlite3_stmt* stmt;

    char sql[] = "UPDATE persistent_message SET status = @status WHERE id = @message_id AND "
                 "avatar_id = @avatar_id";

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, 0) != SQLITE_OK) {
        result = ChatResultCode::DBFAIL;
    } else {
        int statusIdx = sqlite3_bind_parameter_index(stmt, "@status");
        int messageIdIdx = sqlite3_bind_parameter_index(stmt, "@message_id");
        int avatarIdIdx = sqlite3_bind_parameter_index(stmt, "@avatar_id");

        sqlite3_bind_int(stmt, statusIdx, static_cast<uint32_t>(status));
        sqlite3_bind_int(stmt, messageIdIdx, messageId);
        sqlite3_bind_int(stmt, avatarIdIdx, avatarId);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            result = ChatResultCode::DBFAIL;
        }
    }

    sqlite3_finalize(stmt);

    return result;
}
