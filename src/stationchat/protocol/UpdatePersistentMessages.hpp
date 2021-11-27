/**
 * UpdatePersistentMessages.hpp
 * Specific handling for bulk-message update requests
 * e.g. for use with /emptyMail command
 *
 * SWG Source Addition - 2021
 * Authors: Aconite
 */

#pragma once

#include "ChatEnums.hpp"
#include "PersistentMessage.hpp"

class PersistentMessageService;
class GatewayClient;

/** Begin UpdatePersistentMessages Request */

struct ReqUpdatePersistentMessages {
    const ChatRequestType type = ChatRequestType::UPDATEPERSISTENTMESSAGES;
    uint32_t track;
    uint32_t srcAvatarId;
    PersistentState currentStatus;
    PersistentState newStatus;
    std::u16string category;
};

template <typename StreamT>
void read(StreamT& ar, ReqUpdatePersistentMessages& data) {
    read(ar, data.track);
    read(ar, data.srcAvatarId);
    read(ar, data.currentStatus);
    read(ar, data.newStatus);
    read(ar, data.category);
}

/** Begin UpdatePersistentMessages Response */

struct ResUpdatePersistentMessages {
    ResUpdatePersistentMessages(uint32_t track_)
            : track{track_}
            , result{ChatResultCode::SUCCESS} {}

    const ChatResponseType type = ChatResponseType::UPDATEPERSISTENTMESSAGES;
    uint32_t track;
    ChatResultCode result;
};

template <typename StreamT>
void write(StreamT& ar, const ResUpdatePersistentMessages& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
}

class UpdatePersistentMessages {
public:
    using RequestType = ReqUpdatePersistentMessages;
    using ResponseType = ResUpdatePersistentMessages;

    UpdatePersistentMessages(GatewayClient* client, const RequestType& request, ResponseType& response);

private:
    PersistentMessageService* messageService_;
};

