
#include "GatewayClient.hpp"

#include "ChatAvatarService.hpp"
#include "ChatRoomService.hpp"
#include "GatewayNode.hpp"
#include "Message.hpp"
#include "PersistentMessageService.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "SQLite3.hpp"
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
    case ChatRequestType::ADDFRIEND:
        HandleAddFriend(::read<ReqAddFriend>(istream));
        break;
    case ChatRequestType::REMOVEFRIEND:
        HandleRemoveFriend(::read<ReqRemoveFriend>(istream));
        break;
    case ChatRequestType::FRIENDSTATUS:
        HandleFriendStatus(::read<ReqFriendStatus>(istream));
        break;
    case ChatRequestType::ADDIGNORE:
        HandleAddIgnore(::read<ReqAddIgnore>(istream));
        break;
    case ChatRequestType::REMOVEIGNORE:
        HandleRemoveIgnore(::read<ReqRemoveIgnore>(istream));
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
    case ChatRequestType::IGNORESTATUS:
        HandleIgnoreStatus(::read<ReqIgnoreStatus>(istream));
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
    auto as = node_->GetAvatarService();

    ChatResultCode result{ChatResultCode::SUCCESS};
    ChatAvatar* avatar{nullptr};

    try {
        avatar = as->GetAvatar(request.name, request.address);
        if (!avatar) {
            avatar = as->CreateAvatar(request.name, request.address, request.userId,
                request.loginAttributes, request.loginLocation);
        }

        as->LoginAvatar(CHECK_NOTNULL(avatar));
    } catch (const SQLite3Exception& e) {
        result = ChatResultCode::DBFAIL;
        LOG(ERROR) << e.message;
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

    auto avatar = as->GetAvatar(request.creatorId);
    if (avatar) {
        std::tie(result, room) = rs->CreateRoom(avatar->GetAvatarId(), avatar->GetName(),
            avatar->GetAddress(), request.roomName, request.roomTopic, request.roomPassword,
            request.roomAttributes, request.roomMaxSize, request.roomAddress, request.srcAddress);
    }

    Send(ResCreateRoom{request.track, result, room});
}

void GatewayClient::HandleAddFriend(const ReqAddFriend& request) {
    ChatResultCode result{ChatResultCode::SUCCESS};
    auto as = node_->GetAvatarService();

    auto srcAvatar = as->GetAvatar(request.srcAvatarId);
    auto destAvatar = as->GetAvatar(request.destName, request.destAddress);

    srcAvatar->AddFriend(destAvatar);

    Send(ResAddFriend{request.track, result});
}

void GatewayClient::HandleRemoveFriend(const ReqRemoveFriend& request) {
    ChatResultCode result{ChatResultCode::SUCCESS};
    auto as = node_->GetAvatarService();

    auto srcAvatar = as->GetAvatar(request.srcAvatarId);
    auto destAvatar = as->GetAvatar(request.destName, request.destAddress);

    srcAvatar->RemoveFriend(destAvatar);

    Send(ResRemoveFriend{request.track, result});
}

void GatewayClient::HandleFriendStatus(const ReqFriendStatus& request) {
    ChatResultCode result{ChatResultCode::SUCCESS};
    auto as = node_->GetAvatarService();

    auto avatar = as->GetAvatar(request.srcAvatarId);

    CHECK_NOTNULL(avatar);
    
    Send(ResFriendStatus{request.track, result, avatar->GetFriendList()});
}

void GatewayClient::HandleAddIgnore(const ReqAddIgnore& request) {
    ChatResultCode result{ChatResultCode::SUCCESS};
    auto as = node_->GetAvatarService();

    auto srcAvatar = as->GetAvatar(request.srcAvatarId);
    auto destAvatar = as->GetAvatar(request.destName, request.destAddress);

    srcAvatar->AddIgnore(destAvatar);

    Send(ResAddIgnore{request.track, result});
}

void GatewayClient::HandleRemoveIgnore(const ReqRemoveIgnore& request) {
    ChatResultCode result{ChatResultCode::SUCCESS};
    auto as = node_->GetAvatarService();

    auto srcAvatar = as->GetAvatar(request.srcAvatarId);
    auto destAvatar = as->GetAvatar(request.destName, request.destAddress);

    srcAvatar->RemoveIgnore(destAvatar);

    Send(ResRemoveIgnore{request.track, result});
}

void GatewayClient::HandleEnterRoom(const ReqEnterRoom& request) {
    auto as = node_->GetAvatarService();
    auto rs = node_->GetRoomService();
    ChatResultCode result = ChatResultCode::SUCCESS;
    ChatRoom* room{nullptr};

    auto avatar = as->GetAvatar(request.srcAvatarId);
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

    auto destAvatar = avatarService->GetAvatar(request.destName, request.destAddress);

    if (destAvatar) {
        if (request.avatarPresence) {
            auto srcAvatar = avatarService->GetAvatar(request.srcAvatarId);

            message.header.fromName = srcAvatar->GetName();
            message.header.fromAddress = srcAvatar->GetAddress();
        } else {
            message.header.fromName = request.srcName;
        }

        message.header.sentTime = static_cast<uint32_t>(std::time(nullptr));
        message.header.avatarId = destAvatar->GetAvatarId();
        message.header.subject = request.subject;
        message.header.category = request.category;
        message.message = request.msg;
        message.oob = request.oob;

        messageService->PersistNewMessage(message);
    }

    Send(ResSendPeristentMessage{request.track, result, message.header.messageId});

    if (destAvatar) {
        Send(MPersistentMessage{destAvatar->GetAvatarId(), message.header});
    }
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

void GatewayClient::HandleIgnoreStatus(const ReqIgnoreStatus& request) {
    ChatResultCode result{ChatResultCode::SUCCESS};
    auto as = node_->GetAvatarService();

    auto avatar = as->GetAvatar(request.srcAvatarId);

    CHECK_NOTNULL(avatar);

    Send(ResIgnoreStatus{request.track, result, avatar->GetIgnoreList()});
}

void GatewayClient::HandleSetApiVersion(const ReqSetApiVersion& request) {
    uint32_t version = node_->GetConfig().version;
    ChatResultCode result = (version == request.version)
        ? ChatResultCode::SUCCESS
        : ChatResultCode::WRONGCHATSERVERFORREQUEST;

    // node_->GetAvatarService()->ClearOnlineAvatars();
    node_->GetRoomService()->LoadRoomsFromStorage();

    Send(ResSetApiVersion{request.track, result, version});
}

void GatewayClient::HandleSetAvatarAttributes(const ReqSetAvatarAttributes& request) {
    auto as = node_->GetAvatarService();

    ChatResultCode result = ChatResultCode::SUCCESS;
    ChatAvatar* avatar = as->GetAvatar(request.avatarId);

    if (avatar) {
        if (avatar->GetAttributes() != request.avatarAttributes) {
            avatar->SetAttributes(request.avatarAttributes);

            if (request.persistent != 0)
                as->PersistAvatar(avatar);
        }
    } else {
        result = ChatResultCode::SRCAVATARDOESNTEXIST;
    }

    Send(ResSetAvatarAttributes{request.track, result, avatar});
}

void GatewayClient::HandleGetAnyAvatar(const ReqGetAnyAvatar& request) {
    auto as = node_->GetAvatarService();

    ChatResultCode result = ChatResultCode::SUCCESS;

    auto avatar = as->GetAvatar(request.name, request.address);

    if (!avatar) {
        result = ChatResultCode::SRCAVATARDOESNTEXIST;
    }

    Send(ResGetAnyAvatar{request.track, result, avatar->IsOnline(), avatar});
}
