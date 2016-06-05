
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

struct InvalidRequestType : public std::runtime_error {
    InvalidRequestType(uint16_t real_type, uint16_t request_type)
        : std::runtime_error("Invalid request data. Expected " + std::to_string(real_type)
              + " Given: " + std::to_string(request_type)) {}
};

/** Begin SETAPIVERSION */

struct ReqSetApiVersion {
    const uint16_t type = static_cast<uint16_t>(ChatRequestType::SETAPIVERSION);
    uint32_t track;
    uint32_t version;
};

template <typename StreamT>
void read(StreamT& ar, ReqSetApiVersion& data) {
    read(ar, data.track);
    read(ar, data.version);
}

/** Begin REGISTRAR_GETCHATSERVER */

struct ReqRegistrarGetChatServer {
    const uint16_t type = static_cast<uint16_t>(ChatRequestType::REGISTRAR_GETCHATSERVER);
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
