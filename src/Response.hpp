
#pragma once

#include "ChatAvatar.hpp"
#include "ChatEnums.hpp"
#include "ChatRoom.hpp"
#include "Serialization.hpp"

#include <boost/optional.hpp>

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

/** Begin LOGINAVATAR */

struct ResLoginAvatar {
    ResLoginAvatar(uint32_t track_, ChatResultCode result_, boost::optional<ChatAvatar>& avatar_)
        : track{track_}
        , result{result_}
        , avatar{avatar_} {}

    const ChatResponseType type = ChatResponseType::LOGINAVATAR;
    uint32_t track;
    ChatResultCode result;
    const boost::optional<ChatAvatar>& avatar;
};

template <typename StreamT>
void write(StreamT& ar, const ResLoginAvatar& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);

    if (data.result == ChatResultCode::SUCCESS) {
        write(ar, data.avatar.get());
    }
}

/** Begin GETROOMSUMMARIES */

struct ResGetRoomSummaries {
    ResGetRoomSummaries(uint32_t track_, ChatResultCode result_, std::vector<ChatRoom*> rooms_)
        : track{track_}
        , result{result_}
        , rooms{rooms_} {}

    const uint16_t type = static_cast<uint16_t>(ChatResponseType::GETROOMSUMMARIES);
    uint32_t track;
    ChatResultCode result;
    std::vector<ChatRoom*> rooms;
};


template <typename StreamT>
void write(StreamT& ar, const ResGetRoomSummaries& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);

    write(ar, static_cast<uint32_t>(data.rooms.size()));
    for (auto room : data.rooms) {
        write(ar, room->GetRoomAddress());
        write(ar, room->GetRoomTopic());
        write(ar, room->GetRoomAttributes());
        write(ar, room->GetCurrentRoomSize());
        write(ar, room->GetMaxRoomSize());
    }
}

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
    ResGetAnyAvatar(uint32_t track_, ChatResultCode result_, bool isOnline_, boost::optional<ChatAvatar>& avatar_)
        : track{track_}
        , result{result_}
        , isOnline{isOnline_}
        , avatar{avatar_} {}

    const ChatResponseType type = ChatResponseType::GETANYAVATAR;
    uint32_t track;
    ChatResultCode result;
    bool isOnline;
    boost::optional<ChatAvatar>& avatar;
};

template <typename StreamT>
void write(StreamT& ar, const ResGetAnyAvatar& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
    write(ar, data.isOnline);

    if (data.result == ChatResultCode::SUCCESS) {
        write(ar, data.avatar.get());
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
