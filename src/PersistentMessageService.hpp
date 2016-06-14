
#pragma once

#include "ChatEnums.hpp"
#include "PersistentMessage.hpp"

#include <boost/optional.hpp>

#include <cstdint>
#include <vector>

struct sqlite3;

class PersistentMessageService {
public:
    explicit PersistentMessageService(sqlite3* db);
    ~PersistentMessageService();

    ChatResultCode PersistNewMessage(PersistentMessage& message);

    std::vector<PersistentHeader> GetMessageHeaders(uint32_t avatarId);

    std::pair<ChatResultCode, boost::optional<PersistentMessage>> GetPersistentMessage(uint32_t avatarId, uint32_t messageId);

    ChatResultCode UpdateMessageStatus(
        uint32_t avatarId, uint32_t messageId, PersistentState status);

private:
    sqlite3* db_;
};
