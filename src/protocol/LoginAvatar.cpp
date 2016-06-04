
#include "LoginAvatar.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "GatewayClient.hpp"
#include "GatewayNode.hpp"
#include "StringUtils.hpp"

#include "easylogging++.h"

LoginAvatar::LoginAvatar(GatewayClient* client, const RequestType& request, ResponseType& response)
    : avatarService_{client->GetNode()->GetAvatarService()}
    , roomService_{client->GetNode()->GetRoomService()} {
    LOG(INFO) << "LOGINAVATAR request received " << FromWideString(request.name) << "@"
              << FromWideString(request.address);

    auto avatar = avatarService_->GetAvatar(request.name, request.address);
    if (!avatar) {
        LOG(INFO) << "Login avatar does not exist, creating a new one "
                  << FromWideString(request.name) << "@" << FromWideString(request.address);
        avatar = avatarService_->CreateAvatar(request.name, request.address, request.userId,
            request.loginAttributes, request.loginLocation);
    }

    avatarService_->LoginAvatar(CHECK_NOTNULL(avatar));

    if (avatar->GetName().compare(u"SYSTEM") == 0) {
        client->GetNode()->RegisterClientAddress(avatar->GetAddress(), client);
        roomService_->LoadRoomsFromStorage(request.address);
    } else {
        client->SendFriendLoginUpdates(avatar);
    }

    response.avatar = avatar;
}
