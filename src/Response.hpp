
#pragma once

#include "ChatAvatar.hpp"
#include "Serialization.hpp"

#include <cstdint>
#include <string>

enum class ChatResponseType : uint16_t {
    LOGINAVATAR = 0,
    LOGOUTAVATAR,
    DESTROYAVATAR,
    GETAVATAR,
    CREATEROOM,
    DESTROYROOM,
    SENDINSTANTMESSAGE,
    SENDROOMMESSAGE,
    SENDBROADCASTMESSAGE,
    ADDFRIEND,
    REMOVEFRIEND,
    FRIENDSTATUS,
    ADDIGNORE,
    REMOVEIGNORE,
    ENTERROOM,
    LEAVEROOM,
    ADDMODERATOR,
    REMOVEMODERATOR,
    ADDBAN,
    REMOVEBAN,
    ADDINVITE,
    REMOVEINVITE,
    KICKAVATAR,
    SETROOMPARAMS,
    GETROOM,
    GETROOMSUMMARIES,
    SENDPERSISTENTMESSAGE,
    GETPERSISTENTHEADERS,
    GETPERSISTENTMESSAGE,
    UPDATEPERSISTENTMESSAGE,
    UNREGISTERROOM,
    IGNORESTATUS,
    FAILOVER_RELOGINAVATAR,
    FAILOVER_RECREATEROOM,
    CONFIRMFRIEND,
    GETAVATARKEYWORDS,
    SETAVATARKEYWORDS,
    SEARCHAVATARKEYWORDS,
    GETFANCLUBHANDLE,
    UPDATEPERSISTENTMESSAGES,
    FINDAVATARBYUID,
    CHANGEROOMOWNER,
    SETAPIVERSION,
    ADDTEMPORARYMODERATOR,
    REMOVETEMPORARYMODERATOR,
    GRANTVOICE,
    REVOKEVOICE,
    SETAVATARATTRIBUTES,
    ADDSNOOPAVATAR,
    REMOVESNOOPAVATAR,
    ADDSNOOPROOM,
    REMOVESNOOPROOM,
    GETSNOOPLIST,
    PARTIALPERSISTENTHEADERS,
    COUNTPERSISTENTMESSAGES,
    PURGEPERSISTENTMESSAGES,
    SETFRIENDCOMMENT,
    TRANSFERAVATAR,
    CHANGEPERSISTENTFOLDER,
    ALLOWROOMENTRY,
    SETAVATAREMAIL,
    SETAVATARINBOXLIMIT,
    SENDMULTIPLEPERSISTENTMESSAGES,
    GETMULTIPLEPERSISTENTMESSAGES,
    ALTERPERSISTENTMESSAGE,
    GETANYAVATAR,
    TEMPORARYAVATAR,
    AVATARLIST,
    SETSTATUSMESSAGE,
    CONFIRMFRIEND_RECIPROCATE,
    ADDFRIEND_RECIPROCATE,
    REMOVEFRIEND_RECIPROCATE,
    FILTERMESSAGE,
    FILTERMESSAGE_EX,

    REGISTRAR_GETCHATSERVER = 20001,
};

enum class ChatResultCode : uint32_t {
    SUCCESS = 0,
    TIMEOUT = 1,
    DUPLICATELOGIN,
    SRCAVATARDOESNTEXIST,
    DESTAVATARDOESNTEXIST,
    ADDRESSDOESNTEXIST, // 5
    ADDRESSNOTROOM,
    ADDRESSNOTAID,
    FRIENDNOTFOUND,
    ROOM_UNKNOWNFAILURE,
    ROOM_SRCNOTINROOM, // 10
    ROOM_DESTNOTINROOM,
    ROOM_BANNEDAVATAR,
    ROOM_PRIVATEROOM,
    ROOM_MODERATEDROOM,
    ROOM_NOTINROOM, // 15
    ROOM_NOPRIVILEGES,
    DATABASE,
    CANNOTGETAVATARID,
    CANNOTGETNODEID,
    CANNOTGETPMSGID, // 20
    PMSGNOTFOUND,
    ROOMMAXAVATARSREACHED,
    IGNORING,
    ROOM_ALREADYEXISTS,
    NOTHINGTOCONFIRM, // 25
    DUPLICATEFRIEND,
    IGNORENOTFOUND,
    DUPLICATEIGNORE,
    DBFAIL,
    ROOM_DESTAVATARNOTMODERATOR, // 30
    ROOM_DESTAVATARNOTINVITED,
    ROOM_DESTAVATARNOTBANNED,
    ROOM_DUPLICATEBAN,
    ROOM_DUPLICATEMODERATOR,
    ROOM_DUPLICATEINVITE, // 35
    ROOM_ALREADYINROOM,
    ROOM_PARENTNONPERSISTENT,
    ROOM_PARENTBADNODETYPE,
    NOFANCLUBHANDLE,
    AIDALREADYEXISTS, // 40
    UIDALREADYEXISTS,
    WRONGCHATSERVERFORREQUEST,
    SUCCESSBADDATA,
    NULLNAMELOGIN,
    SERVER_IDENTITY_EMPTY, // 45
    SERVER_IDENTITY_TAKEN,
    REMOTESERVERDOWN,
    NODEIDCONFLICT,
    INVALIDNODENAME,
    INSUFFICIENTGMPRIVS, // 50
    SNOOPALREADYADDED,
    NOTSNOOPING,
    ROOM_DESTAVATARNOTTEMPORARYMODERATOR,
    ROOM_DESTAVATARNOTVOICE,
    ROOM_DUPLICATETEMPORARYMODERATOR, // 55
    ROOM_DUPLICATEVOICE,
    AVATARMUSTBELOGGEDOUT,
    NOTHINGTODO,
    TRANSFERNAMENULL,
    TRANSFERUSERIDZERO, // 60
    TRANSFERADDRESSNULL,
    OUTOFIDS,
    ROOM_LOCALROOM,
    ROOM_GAMEROOM,
    ROOM_DESTAVATARNOTENTERING, // 65
    INSUFFICIENTPRIORITY,
    ROOM_WAITINGFORENTRY,
    INBOXLIMITEXCEEDED,
    DUPLICATEDESTINATION,
    CATEGORYLIMITEXCEEDED, // 70
    MESSAGE_FILTER_FAILURE,
    INVALID_INPUT,
};

/** Begin SETAPIVERSION */

struct ResSetApiVersion {
    ResSetApiVersion(uint32_t track_, ChatResultCode result_, uint32_t version_)
        : track{track_}
        , result{result_}
        , version{version_} {}

    const ChatResponseType type = ChatResponseType::SETAPIVERSION;
    uint32_t track;
    ChatResultCode result;
    uint32_t version;
};

template <typename StreamT>
void write(StreamT& ar, const ResSetApiVersion& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
    write(ar, data.version);
}

/** Begin GETANYAVATAR */

struct ResGetAnyAvatar {
    ResGetAnyAvatar(uint32_t track_, ChatResultCode result_, bool isOnline_, ChatAvatar* avatar_)
        : track{track_}
        , result{result_}
        , isOnline{isOnline_}
        , avatar{avatar_} {}

    const ChatResponseType type = ChatResponseType::GETANYAVATAR;
    uint32_t track;
    ChatResultCode result;
    bool isOnline;
    ChatAvatar* avatar;
};

template <typename StreamT>
void write(StreamT& ar, const ResGetAnyAvatar& data) {
    write(ar, static_cast<uint32_t>(data.type));
    write(ar, data.track);
    write(ar, static_cast<uint32_t>(data.result));
    write(ar, data.isOnline);

    if (data.result == ChatResultCode::SUCCESS) {
        write(ar, *data.avatar);
    }
}

/** Begin REGISTRAR_GETCHATSERVER */

struct ResRegistrarGetChatServer {
    ResRegistrarGetChatServer(
        uint32_t track_, ChatResultCode result_, std::wstring hostname_, uint16_t port_)
        : track{track_}
        , result{result_}
        , hostname{hostname_}
        , port{port_} {}

    const ChatResponseType type = ChatResponseType::REGISTRAR_GETCHATSERVER;
    uint32_t track;
    ChatResultCode result;
    std::wstring hostname;
    uint16_t port;
};

template <typename StreamT>
void write(StreamT& ar, const ResRegistrarGetChatServer& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
    write(ar, data.hostname);
    write(ar, data.port);
}
