
#include "GatewayClient.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "GatewayNode.hpp"
#include "PersistentMessageService.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "SwgChatConfig.hpp"
#include "UdpLibrary.hpp"

#include "easylogging++.h"

#include <ctime>

GatewayClient::GatewayClient(UdpConnection* connection, GatewayNode* node)
    : NodeClient<8192>(connection)
    , node_{node} {
    connection->SetHandler(this);
}

GatewayClient::~GatewayClient() {}

void GatewayClient::OnIncoming(BinarySourceStream& istream) {
    ChatRequestType request_type = ::read<ChatRequestType>(istream);

    switch (request_type) {
    case ChatRequestType::LOGINAVATAR:
        HandleLoginAvatar(::read<ReqLoginAvatar>(istream));
        break;
    case ChatRequestType::LOGOUTAVATAR:
        HandleLogoutAvatar(::read<ReqLogoutAvatar>(istream));
        break;
    case ChatRequestType::CREATEROOM:
        HandleCreateRoom(::read<ReqCreateRoom>(istream));
        break;
    case ChatRequestType::ENTERROOM:
        HandleEnterRoom(::read<ReqEnterRoom>(istream));
        break;
    case ChatRequestType::GETROOM:
        HandleGetRoom(::read<ReqGetRoom>(istream));
        break;
    case ChatRequestType::GETROOMSUMMARIES:
        HandleGetRoomSummaries(::read<ReqGetRoomSummaries>(istream));
        break;
    case ChatRequestType::SENDPERSISTENTMESSAGE:
        HandleSendPersistentMessage(::read<ReqSendPersistentMessage>(istream));
        break;
    case ChatRequestType::GETPERSISTENTHEADERS:
        HandleGetPersistentHeaders(::read<ReqGetPersistentHeaders>(istream));
        break;
    case ChatRequestType::GETPERSISTENTMESSAGE:
        HandleGetPersistentMessage(::read<ReqGetPersistentMessage>(istream));
        break;
    case ChatRequestType::UPDATEPERSISTENTMESSAGE:
        HandleUpdatePersistentMessage(::read<ReqUpdatePersistentMessage>(istream));
        break;
    case ChatRequestType::SETAPIVERSION:
        HandleSetApiVersion(::read<ReqSetApiVersion>(istream));
        break;
    case ChatRequestType::SETAVATARATTRIBUTES:
        HandleSetAvatarAttributes(::read<ReqSetAvatarAttributes>(istream));
        break;
    case ChatRequestType::GETANYAVATAR:
        HandleGetAnyAvatar(::read<ReqGetAnyAvatar>(istream));
        break;
    default:
        LOG(INFO) << "Unknown request type received: " << static_cast<uint16_t>(request_type);
        break;
    }
}

void GatewayClient::HandleLoginAvatar(const ReqLoginAvatar& request) {
    auto avatarService = node_->GetAvatarService();

    ChatResultCode result = ChatResultCode::SUCCESS;
    boost::optional<ChatAvatar> avatar;

    // Check to see if this avatar is already logged in.
    if (avatarService->IsAvatarOnline(request.name, request.address)) {
        result = ChatResultCode::DUPLICATELOGIN;
    } else {
        // If the avatar already exists grab it from persistent storage.
        std::tie(result, avatar) = avatarService->GetPersistedAvatar(request.name, request.address);
        if (result != ChatResultCode::SUCCESS) {
            // Otherwise, create a new avatar.
            std::tie(result, avatar) = avatarService->CreateAvatar(request.name, request.address,
                request.userId, request.loginAttributes, request.loginLocation);
        }

        // Log in the avatar if it was successfully created or loaded from storage
        if (result == ChatResultCode::SUCCESS) {
            result = avatarService->LoginAvatar(avatar.get());
        }
    }

    Send(ResLoginAvatar{request.track, result, avatar});
}

void GatewayClient::HandleLogoutAvatar(const ReqLogoutAvatar& request) {
    node_->GetAvatarService()->LogoutAvatar(request.avatarId);
    node_->GetRoomService()->LogoutFromAllRooms(request.avatarId);

    Send(ResLogoutAvatar{request.track, ChatResultCode::SUCCESS});
}

void GatewayClient::HandleCreateRoom(const ReqCreateRoom& request) {
    auto as = node_->GetAvatarService();
    auto rs = node_->GetRoomService();

    ChatResultCode result;
    ChatRoom* room;

    auto avatar = as->GetOnlineAvatar(request.creatorId);
    if (avatar) {
        std::tie(result, room) = rs->CreateRoom(avatar->avatarId, avatar->name, avatar->address,
            request.roomName, request.roomTopic, request.roomPassword, request.roomAttributes,
            request.roomMaxSize, request.roomAddress, request.srcAddress);
    }

    Send(ResCreateRoom{request.track, result, room});
}

void GatewayClient::HandleEnterRoom(const ReqEnterRoom& request) {
    auto as = node_->GetAvatarService();
    auto rs = node_->GetRoomService();
    ChatResultCode result = ChatResultCode::SUCCESS;
    ChatRoom* room{nullptr};

    auto avatar = as->GetOnlineAvatar(request.srcAvatarId);
    if (!avatar) {
        result = ChatResultCode::SRCAVATARDOESNTEXIST;
    } else {
        room = rs->GetRoom(request.roomAddress);
        if (!room) {
            result = ChatResultCode::ADDRESSNOTROOM;
        } else {
            result = room->EnterRoom(avatar, request.roomPassword);
        }
    }

    Send(ResEnterRoom{request.track, result, room});
}

void GatewayClient::HandleGetRoom(const ReqGetRoom& request) {
    auto room = node_->GetRoomService()->GetRoom(request.roomAddress);
    ChatResultCode result
        = (room != nullptr) ? ChatResultCode::SUCCESS : ChatResultCode::ADDRESSDOESNTEXIST;
    Send(ResGetRoom{request.track, result, room});
}

void GatewayClient::HandleGetRoomSummaries(const ReqGetRoomSummaries& request) {
    auto roomService = node_->GetRoomService();

    auto rooms = roomService->GetRoomSummaries(request.startNodeAddress, request.roomFilter);

    Send(ResGetRoomSummaries{request.track, ChatResultCode::SUCCESS, rooms});
}

void GatewayClient::HandleSendPersistentMessage(const ReqSendPersistentMessage& request) {
    ChatResultCode result = ChatResultCode::SUCCESS;

    auto avatarService = node_->GetAvatarService();
    auto messageService = node_->GetMessageService();
    
    PersistentMessage message;

    boost::optional<ChatAvatar> destAvatar;

    std::tie(result, destAvatar) = avatarService->GetAvatar(request.destName, request.destAddress);

    if (destAvatar != boost::none) {
        if (request.avatarPresence) {
            auto avatar = avatarService->GetOnlineAvatar(request.srcAvatarId);

            message.header.fromName = avatar->name;
            message.header.fromAddress = avatar->address;
        } else {
            message.header.fromName = request.srcName;
        }

        message.header.sentTime = static_cast<uint32_t>(std::time(nullptr));
        message.header.avatarId = destAvatar->avatarId;
        message.header.subject = request.subject;
        message.header.category = request.category;
        message.message = request.msg;
        message.oob = request.oob;

        messageService->PersistNewMessage(message);
    }

    Send(ResSendPeristentMessage{request.track, result, message.header.messageId});
}

void GatewayClient::HandleGetPersistentHeaders(const ReqGetPersistentHeaders& request) {
    auto headers = node_->GetMessageService()->GetMessageHeaders(request.avatarId);

    Send(ResGetPersistentHeaders{request.track, ChatResultCode::SUCCESS, std::move(headers)});
}

void GatewayClient::HandleGetPersistentMessage(const ReqGetPersistentMessage& request) {
    ChatResultCode result;
    boost::optional<PersistentMessage> message;

    std::tie(result, message)
        = node_->GetMessageService()->GetPersistentMessage(request.srcAvatarId, request.messageId);

    Send(ResGetPersistentMessage{request.track, result, message});
}

void GatewayClient::HandleUpdatePersistentMessage(const ReqUpdatePersistentMessage& request) {
    node_->GetMessageService()->UpdateMessageStatus(
        request.srcAvatarId, request.messageId, request.status);

    Send(ResUpdatePersistentMessage{request.track, ChatResultCode::SUCCESS});
}

void GatewayClient::HandleSetApiVersion(const ReqSetApiVersion& request) {
    uint32_t version = node_->GetConfig().version;
    ChatResultCode result = (version == request.version)
        ? ChatResultCode::SUCCESS
        : ChatResultCode::WRONGCHATSERVERFORREQUEST;

    node_->GetAvatarService()->ClearOnlineAvatars();
    node_->GetRoomService()->LoadRoomsFromStorage();

    Send(ResSetApiVersion{request.track, result, version});
}

void GatewayClient::HandleSetAvatarAttributes(const ReqSetAvatarAttributes& request) {
    auto avatarService = node_->GetAvatarService();

    ChatResultCode result = ChatResultCode::SUCCESS;
    ChatAvatar* avatar = avatarService->GetOnlineAvatar(request.avatarId);

    if (avatar) {
        if (avatar->attributes != request.avatarAttributes) {
            avatar->attributes = request.avatarAttributes;

            if (request.persistent != 0) {
                avatarService->PersistAvatar(*avatar);
            }
        }
    } else {
        result = ChatResultCode::SRCAVATARDOESNTEXIST;
    }

    Send(ResSetAvatarAttributes{request.track, result, avatar});
}

void GatewayClient::HandleGetAnyAvatar(const ReqGetAnyAvatar& request) {
    auto avatarService = node_->GetAvatarService();

    ChatResultCode result;
    boost::optional<ChatAvatar> avatar;

    std::tie(result, avatar) = avatarService->GetAvatar(request.name, request.address);
    bool isOnline = (avatar) ? avatar->isOnline : false;

    Send(ResGetAnyAvatar{request.track, result, isOnline, avatar});
}
