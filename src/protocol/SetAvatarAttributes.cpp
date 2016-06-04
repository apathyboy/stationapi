#include "SetAvatarAttributes.hpp"

#include "ChatAvatarService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"

#include "easylogging++.h"

SetAvatarAttributes::SetAvatarAttributes(GatewayClient * client, const RequestType & request, ResponseType & response)
    : avatarService_{client->GetNode()->GetAvatarService()} {
    LOG(INFO) << "SETAVATARATTRIBUTES request received - avatar: " << request.avatarId;

    auto avatar = avatarService_->GetAvatar(request.avatarId);
    if (!avatar) {
        throw ChatResultException{ChatResultCode::SRCAVATARDOESNTEXIST};
    }

    response.avatar = avatar;

    if (avatar->GetAttributes() != request.avatarAttributes) {
        avatar->SetAttributes(request.avatarAttributes);
        
        if (request.persistent != 0) {
            avatarService_->PersistAvatar(avatar);
        }
    }
}
