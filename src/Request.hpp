
#pragma once

#include "PersistentMessage.hpp"
#include "Serialization.hpp"

#include <cstdint>
#include <string>

enum class ChatRequestType : uint16_t {
    LOGINAVATAR = 0,
    LOGOUTAVATAR,
    DESTROYAVATAR,
    GETAVATAR,
    CREATEROOM,
    DESTROYROOM, // 5
    SENDINSTANTMESSAGE,
    SENDROOMMESSAGE,
    SENDBROADCASTMESSAGE,
    ADDFRIEND,
    REMOVEFRIEND, // 10
    FRIENDSTATUS,
    ADDIGNORE,
    REMOVEIGNORE,
    ENTERROOM,
    LEAVEROOM, // 15
    ADDMODERATOR,
    REMOVEMODERATOR,
    ADDBAN,
    REMOVEBAN,
    ADDINVITE, // 20
    REMOVEINVITE,
    KICKAVATAR,
    SETROOMPARAMS,
    GETROOM,
    GETROOMSUMMARIES, // 25
    SENDPERSISTENTMESSAGE,
    GETPERSISTENTHEADERS,
    GETPERSISTENTMESSAGE,
    UPDATEPERSISTENTMESSAGE,
    UNREGISTERROOM, // 30
    IGNORESTATUS,
    FAILOVER_RELOGINAVATAR,
    FAILOVER_RECREATEROOM,
    CONFIRMFRIEND,
    GETAVATARKEYWORDS, // 35
    SETAVATARKEYWORDS,
    SEARCHAVATARKEYWORDS,
    GETFANCLUBHANDLE,
    UPDATEPERSISTENTMESSAGES,
    FINDAVATARBYUID, // 40
    CHANGEROOMOWNER,
    SETAPIVERSION,
    ADDTEMPORARYMODERATOR,
    REMOVETEMPORARYMODERATOR,
    GRANTVOICE, // 45
    REVOKEVOICE,
    SETAVATARATTRIBUTES,
    ADDSNOOPAVATAR,
    REMOVESNOOPAVATAR,
    ADDSNOOPROOM, // 50
    REMOVESNOOPROOM,
    GETSNOOPLIST,
    PARTIALPERSISTENTHEADERS,
    COUNTPERSISTENTMESSAGES,
    PURGEPERSISTENTMESSAGES, // 55
    SETFRIENDCOMMENT,
    TRANSFERAVATAR,
    CHANGEPERSISTENTFOLDER,
    ALLOWROOMENTRY,
    SETAVATAREMAIL, // 60
    SETAVATARINBOXLIMIT,
    SENDMULTIPLEPERSISTENTMESSAGES,
    GETMULTIPLEPERSISTENTMESSAGES,
    ALTERPERISTENTMESSAGE,
    GETANYAVATAR, // 65
    TEMPORARYAVATAR,
    AVATARLIST,
    SETAVATARSTATUSMESSAGE,
    CONFIRMFRIEND_RECIPROCATE,
    ADDFRIEND_RECIPROCATE, // 70
    REMOVEFRIEND_RECIPROCATE,
    FILTERMESSAGE,
    FILTERMESSAGE_EX,
    REGISTRAR_GETCHATSERVER = 20001,
};

/** Begin LOGINAVATAR */

struct ReqLoginAvatar {
    const ChatRequestType type = ChatRequestType::LOGINAVATAR;
    uint32_t track;
    uint32_t userId;
    std::wstring name;
    std::wstring address;
    std::wstring loginLocation;
    int32_t loginPriority;
    int32_t loginAttributes;
};

template <typename StreamT>
void read(StreamT& ar, ReqLoginAvatar& data) {
    read(ar, data.track);
    read(ar, data.userId);
    read(ar, data.name);
    read(ar, data.address);
    read(ar, data.loginLocation);
    read(ar, data.loginPriority);
    read(ar, data.loginAttributes);
}

/** Begin LOGOUTAVATAR */

struct ReqLogoutAvatar {
    const ChatRequestType type = ChatRequestType::LOGOUTAVATAR;
    uint32_t track;
    uint32_t avatarId;
};

template <typename StreamT>
void read(StreamT& ar, ReqLogoutAvatar& data) {
    read(ar, data.track);
    read(ar, data.avatarId);
}

/** Begin CREATEROOM */

struct ReqCreateRoom {
    const ChatRequestType type = ChatRequestType::CREATEROOM;
    uint32_t track;
    uint32_t creatorId;
    std::wstring roomName;
    std::wstring roomTopic;
    std::wstring roomPassword;
    uint32_t roomAttributes;
    uint32_t roomMaxSize;
    std::wstring roomAddress;
    std::wstring srcAddress;
};

template <typename StreamT>
void read(StreamT& ar, ReqCreateRoom& data) {
    read(ar, data.track);
    read(ar, data.creatorId);
    read(ar, data.roomName);
    read(ar, data.roomTopic);
    read(ar, data.roomPassword);
    read(ar, data.roomAttributes);
    read(ar, data.roomMaxSize);
    read(ar, data.roomAddress);
    read(ar, data.srcAddress);
}

/** Begin ADDFRIEND */

struct ReqAddFriend {
    const ChatRequestType type = ChatRequestType::ADDFRIEND;
    uint32_t track;
    uint32_t srcAvatarId;
    std::wstring destName;
    std::wstring destAddress;
    std::wstring comment;
    bool confirm;
    std::wstring srcAddress;
};

template <typename StreamT>
void read(StreamT& ar, ReqAddFriend& data) {
    read(ar, data.track);
    read(ar, data.srcAvatarId);
    read(ar, data.destName);
    read(ar, data.destAddress);
    read(ar, data.comment);
    read(ar, data.confirm);
    read(ar, data.srcAddress);
}

/** Begin REMOVEFRIEND */

struct ReqRemoveFriend {
    const ChatRequestType type = ChatRequestType::REMOVEFRIEND;
    uint32_t track;
    uint32_t srcAvatarId;
    std::wstring destName;
    std::wstring destAddress;
    std::wstring srcAddress;
};

template <typename StreamT>
void read(StreamT& ar, ReqRemoveFriend& data) {
    read(ar, data.track);
    read(ar, data.srcAvatarId);
    read(ar, data.destName);
    read(ar, data.destAddress);
    read(ar, data.srcAddress);
}

/** Begin FRIENDSTATUS */

struct ReqFriendStatus {
    const ChatRequestType type = ChatRequestType::FRIENDSTATUS;
    uint32_t track;
    uint32_t srcAvatarId;
    std::wstring srcAddress;
};

template <typename StreamT>
void read(StreamT& ar, ReqFriendStatus& data) {
    read(ar, data.track);
    read(ar, data.srcAvatarId);
    read(ar, data.srcAddress);
}

/** Begin ADDIGNORE */

struct ReqAddIgnore {
    const ChatRequestType type = ChatRequestType::ADDIGNORE;
    uint32_t track;
    uint32_t srcAvatarId;
    std::wstring destName;
    std::wstring destAddress;
    std::wstring srcAddress;
};

template <typename StreamT>
void read(StreamT& ar, ReqAddIgnore& data) {
    read(ar, data.track);
    read(ar, data.srcAvatarId);
    read(ar, data.destName);
    read(ar, data.destAddress);
    read(ar, data.srcAddress);
}

/** Begin REMOVEIGNORE */

struct ReqRemoveIgnore {
    const ChatRequestType type = ChatRequestType::REMOVEIGNORE;
    uint32_t track;
    uint32_t srcAvatarId;
    std::wstring destName;
    std::wstring destAddress;
    std::wstring srcAddress;
};

template <typename StreamT>
void read(StreamT& ar, ReqRemoveIgnore& data) {
    read(ar, data.track);
    read(ar, data.srcAvatarId);
    read(ar, data.destName);
    read(ar, data.destAddress);
    read(ar, data.srcAddress);
}

/** Begin ENTERROOM */

struct ReqEnterRoom {
    const ChatRequestType type = ChatRequestType::ENTERROOM;
    uint32_t track;
    uint32_t srcAvatarId;
    std::wstring roomAddress;
    std::wstring roomPassword;
    bool passiveCreate;
    std::wstring paramRoomTopic;
    uint32_t paramRoomAttributes;
    uint32_t paramRoomMaxSize;
    bool requestingEntry;
    std::wstring srcAddress;
};

template <typename StreamT>
void read(StreamT& ar, ReqEnterRoom& data) {
    read(ar, data.track);
    read(ar, data.srcAvatarId);
    read(ar, data.roomAddress);
    read(ar, data.roomPassword);
    read(ar, data.passiveCreate);

    if (data.passiveCreate) {
        read(ar, data.paramRoomTopic);
        read(ar, data.paramRoomAttributes);
        read(ar, data.paramRoomMaxSize);
    }

    read(ar, data.requestingEntry);
    read(ar, data.srcAddress);
}

/** Begin GETROOM */

struct ReqGetRoom {
    const ChatRequestType type = ChatRequestType::GETROOMSUMMARIES;
    uint32_t track;
    std::wstring roomAddress;
};

template <typename StreamT>
void read(StreamT& ar, ReqGetRoom& data) {
    read(ar, data.track);
    read(ar, data.roomAddress);
}

/** Begin GETROOMSUMMARIES */

struct ReqGetRoomSummaries {
    const ChatRequestType type = ChatRequestType::GETROOMSUMMARIES;
    uint32_t track;
    std::wstring startNodeAddress;
    std::wstring roomFilter;
};

template <typename StreamT>
void read(StreamT& ar, ReqGetRoomSummaries& data) {
    read(ar, data.track);
    read(ar, data.startNodeAddress);
    read(ar, data.roomFilter);
}

/** Begin SENDPERSISTENTMESSAGE */

struct ReqSendPersistentMessage {
    const ChatRequestType type = ChatRequestType::SENDPERSISTENTMESSAGE;
    uint32_t track;
    uint16_t avatarPresence;
    uint32_t srcAvatarId;
    std::wstring srcName;
    std::wstring destName;
    std::wstring destAddress;
    std::wstring subject;
    std::wstring msg;
    std::wstring oob;
    std::wstring category;
    bool enforceInboxLimit;
    uint32_t categoryLimit;
};

template <typename StreamT>
void read(StreamT& ar, ReqSendPersistentMessage& data) {
    read(ar, data.track);
    read(ar, data.avatarPresence);

    if (data.avatarPresence) {
        read(ar, data.srcAvatarId);
    } else {
        read(ar, data.srcName);
    }

    read(ar, data.destName);
    read(ar, data.destAddress);
    read(ar, data.subject);
    read(ar, data.msg);
    read(ar, data.oob);
    read(ar, data.category);
    read(ar, data.enforceInboxLimit);
    read(ar, data.categoryLimit);
}

/** Begin GETPERSISTENTHEADERS */

struct ReqGetPersistentHeaders {
    const ChatRequestType type = ChatRequestType::GETPERSISTENTHEADERS;
    uint32_t track;
    uint32_t avatarId;
    std::wstring category;
};

template <typename StreamT>
void read(StreamT& ar, ReqGetPersistentHeaders& data) {
    read(ar, data.track);
    read(ar, data.avatarId);
    read(ar, data.category);
}

/** Begin GETPERSISTENTMESSAGE */

struct ReqGetPersistentMessage {
    const ChatRequestType type = ChatRequestType::GETPERSISTENTMESSAGE;
    uint32_t track;
    uint32_t srcAvatarId;
    uint32_t messageId;
};

template <typename StreamT>
void read(StreamT& ar, ReqGetPersistentMessage& data) {
    read(ar, data.track);
    read(ar, data.srcAvatarId);
    read(ar, data.messageId);
}

/** Begin UPDATEPERSISTENTMESSAGE */

struct ReqUpdatePersistentMessage {
    const ChatRequestType type = ChatRequestType::UPDATEPERSISTENTMESSAGE;
    uint32_t track;
    uint32_t srcAvatarId;
    uint32_t messageId;
    PersistentState status;
};

template <typename StreamT>
void read(StreamT& ar, ReqUpdatePersistentMessage& data) {
    read(ar, data.track);
    read(ar, data.srcAvatarId);
    read(ar, data.messageId);
    read(ar, data.status);
}

/** Begin IGNORESTATUS */

struct ReqIgnoreStatus {
    const ChatRequestType type = ChatRequestType::IGNORESTATUS;
    uint32_t track;
    uint32_t srcAvatarId;
    std::wstring srcAddress;
};

template <typename StreamT>
void read(StreamT& ar, ReqIgnoreStatus& data) {
    read(ar, data.track);
    read(ar, data.srcAvatarId);
    read(ar, data.srcAddress);
}

/** Begin SETAPIVERSION */

struct ReqSetApiVersion {
    const ChatRequestType type = ChatRequestType::SETAPIVERSION;
    uint32_t track;
    uint32_t version;
};

template <typename StreamT>
void read(StreamT& ar, ReqSetApiVersion& data) {
    read(ar, data.track);
    read(ar, data.version);
}

/** Begin SETAVATARATTRIBUTES */

struct ReqSetAvatarAttributes {
    const ChatRequestType type = ChatRequestType::SETAVATARATTRIBUTES;
    uint32_t track;
    uint32_t avatarId;
    uint32_t avatarAttributes;
    uint32_t persistent;
    std::wstring srcAddress;
};

template <typename StreamT>
void read(StreamT& ar, ReqSetAvatarAttributes& data) {
    read(ar, data.track);
    read(ar, data.avatarId);
    read(ar, data.avatarAttributes);
    read(ar, data.persistent);
    read(ar, data.srcAddress);
}

/** Begin GETANYAVATAR */

struct ReqGetAnyAvatar {
    const ChatRequestType type = ChatRequestType::GETANYAVATAR;
    uint32_t track;
    std::wstring name;
    std::wstring address;
};

template <typename StreamT>
void read(StreamT& ar, ReqGetAnyAvatar& data) {
    read(ar, data.track);
    read(ar, data.name);
    read(ar, data.address);
}

/** Begin REGISTRAR_GETCHATSERVER */

struct ReqRegistrarGetChatServer {
    const ChatRequestType type = ChatRequestType::REGISTRAR_GETCHATSERVER;
    uint32_t track;
    std::wstring hostname;
    uint16_t port;
};

template <typename StreamT>
void read(StreamT& ar, ReqRegistrarGetChatServer& data) {
    read(ar, data.track);
    read(ar, data.hostname);
    read(ar, data.port);
}
