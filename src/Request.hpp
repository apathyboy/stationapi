
#pragma once

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
