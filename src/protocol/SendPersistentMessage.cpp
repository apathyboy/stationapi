#include "SendPersistentMessage.hpp"

#include "ChatAvatarService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "PersistentMessageService.hpp"
#include "StreamUtils.hpp"

#include "easylogging++.h"

SendPersistentMessage::SendPersistentMessage(GatewayClient * client, const RequestType & request, ResponseType & response)
    : avatarService_{client->GetNode()->GetAvatarService()}
    , messageService_{client->GetNode()->GetMessageService()} {
    LOG(INFO) << "SENDPERSISTENTMESSAGE request received:";

    auto destAvatar = avatarService_->GetAvatar(request.destName, request.destAddress);
    if (!destAvatar) {
        throw ChatResultException{ChatResultCode::DESTAVATARDOESNTEXIST};
    }

    PersistentMessage message;

    if (request.avatarPresence) {
        auto srcAvatar = avatarService_->GetAvatar(request.srcAvatarId);
        if (!srcAvatar) {
            throw ChatResultException{ChatResultCode::SRCAVATARDOESNTEXIST};
        }

        if (destAvatar->IsIgnored(srcAvatar)) {
            throw ChatResultException(ChatResultCode::IGNORING);
        }

        message.header.fromName = srcAvatar->GetName();
        message.header.fromAddress = srcAvatar->GetAddress();
    } else {
        message.header.fromName = request.srcName;
        message.header.fromAddress = destAvatar->GetAddress();
    }

    message.header.sentTime = static_cast<uint32_t>(std::time(nullptr));
    message.header.avatarId = destAvatar->GetAvatarId();
    message.header.subject = request.subject;
    message.header.category = request.category;
    message.message = request.msg;
    message.oob = request.oob;

    messageService_->StoreMessage(message);

    response.messageId = message.header.messageId;

    client->SendPersistentMessageUpdate(destAvatar, message.header);
}
