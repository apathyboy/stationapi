
#pragma once

#include "ChatAvatar.hpp"
#include "ChatEnums.hpp"
#include "ChatRoom.hpp"
#include "Contact.hpp"
#include "PersistentMessage.hpp"
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
    ResLoginAvatar(uint32_t track_, ChatResultCode result_, const ChatAvatar* const avatar_)
        : track{track_}
        , result{result_}
        , avatar{avatar_} {}

    const ChatResponseType type = ChatResponseType::LOGINAVATAR;
    uint32_t track;
    ChatResultCode result;
    const ChatAvatar* const avatar;
};

template <typename StreamT>
void write(StreamT& ar, const ResLoginAvatar& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);

    if (data.result == ChatResultCode::SUCCESS) {
        write(ar, data.avatar);
    }
}

/** Begin LOGOUTAVATAR */

struct ResLogoutAvatar {
    ResLogoutAvatar(uint32_t track_, ChatResultCode result_)
        : track{track_}
        , result{result_} {}

    const ChatResponseType type = ChatResponseType::LOGOUTAVATAR;
    uint32_t track;
    ChatResultCode result;
};

template <typename StreamT>
void write(StreamT& ar, const ResLogoutAvatar& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
}

/** Begin CREATEROOM */

struct ResCreateRoom {
    ResCreateRoom(uint32_t track_, ChatResultCode result_, ChatRoom* room_)
        : track{track_}
        , result{result_}
        , room{room_} {}

    const ChatResponseType type = ChatResponseType::CREATEROOM;
    uint32_t track;
    ChatResultCode result;
    ChatRoom* room;
    std::vector<ChatRoom*> extraRooms;
};

template <typename StreamT>
void write(StreamT& ar, const ResCreateRoom& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);

    if (data.result == ChatResultCode::SUCCESS) {
        write(ar, *data.room);

        write(ar, static_cast<uint32_t>(data.extraRooms.size()));
        for (auto room : data.extraRooms) {
            write(ar, *room);
        }
    }
}

/** Begin ADDFRIEND */

struct ResAddFriend {
    ResAddFriend(uint32_t track_, ChatResultCode result_)
        : track{track_}
        , result{result_} {}

    const ChatResponseType type = ChatResponseType::ADDFRIEND;
    uint32_t track;
    ChatResultCode result;
};

template <typename StreamT>
void write(StreamT& ar, const ResAddFriend& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
}

/** Begin REMOVEFRIEND */

struct ResRemoveFriend {
    ResRemoveFriend(uint32_t track_, ChatResultCode result_)
        : track{track_}
        , result{result_} {}

    const ChatResponseType type = ChatResponseType::REMOVEFRIEND;
    uint32_t track;
    ChatResultCode result;
};

template <typename StreamT>
void write(StreamT& ar, const ResRemoveFriend& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
}

/** Begin FRIENDSTATUS */

struct ResFriendStatus {
    ResFriendStatus(uint32_t track_, ChatResultCode result_, const std::vector<FriendContact>& friends_)
        : track{track_}
        , result{result_}
        , friends{friends_} {}

    const ChatResponseType type = ChatResponseType::FRIENDSTATUS;
    uint32_t track;
    ChatResultCode result;
    const std::vector<FriendContact>& friends;
};

template <typename StreamT>
void write(StreamT& ar, const ResFriendStatus& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);

    write(ar, static_cast<uint32_t>(data.friends.size()));

    for (auto& friendContact : data.friends) {
        write(ar, friendContact);
    }
}

/** Begin ADDIGNORE */

struct ResAddIgnore {
    ResAddIgnore(uint32_t track_, ChatResultCode result_)
        : track{track_}
        , result{result_} {}

    const ChatResponseType type = ChatResponseType::ADDIGNORE;
    uint32_t track;
    ChatResultCode result;
};

template <typename StreamT>
void write(StreamT& ar, const ResAddIgnore& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
}

/** Begin REMOVEIGNORE */

struct ResRemoveIgnore {
    ResRemoveIgnore(uint32_t track_, ChatResultCode result_)
        : track{track_}
        , result{result_} {}

    const ChatResponseType type = ChatResponseType::REMOVEIGNORE;
    uint32_t track;
    ChatResultCode result;
};

template <typename StreamT>
void write(StreamT& ar, const ResRemoveIgnore& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
}

/** Begin ENTERROOM */

struct ResEnterRoom {
    ResEnterRoom(uint32_t track_, ChatResultCode result_)
        : track{track_}
        , result{result_} {}

    ResEnterRoom(uint32_t track_, ChatResultCode result_, ChatRoom* room_,
        std::vector<ChatRoom*> extraRooms_ = {})
        : track{track_}
        , result{result_}
        , gotRoomObj{room_ != nullptr}
        , room{room_}
        , extraRooms{extraRooms_} {
        if (gotRoomObj) {
            roomId = room_->GetRoomId();
        }
    }

    const ChatResponseType type = ChatResponseType::ENTERROOM;
    uint32_t track;
    ChatResultCode result;
    uint32_t roomId;
    bool gotRoomObj = false;
    ChatRoom* room = nullptr;
    std::vector<ChatRoom*> extraRooms;
};

template <typename StreamT>
void write(StreamT& ar, const ResEnterRoom& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
    write(ar, data.roomId);
    write(ar, data.gotRoomObj);

    if (data.gotRoomObj) {
        write(ar, *data.room);

        write(ar, static_cast<uint32_t>(data.extraRooms.size()));
        for (auto room : data.extraRooms) {
            write(ar, *room);
        }
    }
}

/** Begin GETROOM */

struct ResGetRoom {
    ResGetRoom(uint32_t track_, ChatResultCode result_, ChatRoom* room_)
        : track{track_}
        , result{result_}
        , room{room_} {}

    const ChatResponseType type = ChatResponseType::GETROOM;
    uint32_t track;
    ChatResultCode result;
    ChatRoom* room;
    std::vector<ChatRoom*> extraRooms;
};

template <typename StreamT>
void write(StreamT& ar, const ResGetRoom& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);

    if (data.result == ChatResultCode::SUCCESS) {
        write(ar, *data.room);

        write(ar, static_cast<uint32_t>(data.extraRooms.size()));
        for (auto room : data.extraRooms) {
            write(ar, *room);
        }
    }
}

/** Begin GETROOMSUMMARIES */

struct ResGetRoomSummaries {
    ResGetRoomSummaries(uint32_t track_, ChatResultCode result_, std::vector<ChatRoom*> rooms_)
        : track{track_}
        , result{result_}
        , rooms{rooms_} {}

    const ChatResponseType type = ChatResponseType::GETROOMSUMMARIES;
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

/** Begin SENDPERSISTENTMESSAGE */

struct ResSendPeristentMessage {
    ResSendPeristentMessage(uint32_t track_, ChatResultCode result_, uint32_t messageId_)
        : track{track_}
        , result{result_}
        , messageId{messageId_} {}

    const ChatResponseType type = ChatResponseType::SENDPERSISTENTMESSAGE;
    uint32_t track;
    ChatResultCode result;
    uint32_t messageId;
};

template <typename StreamT>
void write(StreamT& ar, const ResSendPeristentMessage& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
    
    if (data.result == ChatResultCode::SUCCESS) {
        write(ar, data.messageId);
    }
}

/** Begin GETPERSISTENTHEADERS */

struct ResGetPersistentHeaders {
    ResGetPersistentHeaders(uint32_t track_, ChatResultCode result_, std::vector<PersistentHeader> headers_)
        : track{track_}
        , result{result_}
        , headers{headers_} {}

    const ChatResponseType type = ChatResponseType::GETPERSISTENTHEADERS;
    uint32_t track;
    ChatResultCode result;
    std::vector<PersistentHeader> headers;
};

template <typename StreamT>
void write(StreamT& ar, const ResGetPersistentHeaders& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
    write(ar, static_cast<uint32_t>(data.headers.size()));

    for (auto& header : data.headers) {
        write(ar, header);
    }
}

/** Begin GETPERSISTENTMESSAGE */

struct ResGetPersistentMessage {
    ResGetPersistentMessage(uint32_t track_, ChatResultCode result_, boost::optional<PersistentMessage> message_)
        : track{track_}
        , result{result_}
        , message{message_} {}

    const ChatResponseType type = ChatResponseType::GETPERSISTENTMESSAGE;
    uint32_t track;
    ChatResultCode result;
    boost::optional<PersistentMessage> message;
};

template <typename StreamT>
void write(StreamT& ar, const ResGetPersistentMessage& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);

    if (data.result == ChatResultCode::SUCCESS) {
        write(ar, *data.message);
    }
}

/** Begin UPDATEPERSISTENTMESSAGE */

struct ResUpdatePersistentMessage {
    ResUpdatePersistentMessage(uint32_t track_, ChatResultCode result_)
        : track{track_}
        , result{result_} {}

    const ChatResponseType type = ChatResponseType::UPDATEPERSISTENTMESSAGE;
    uint32_t track;
    ChatResultCode result;
};

template <typename StreamT>
void write(StreamT& ar, const ResUpdatePersistentMessage& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
}

/** Begin IGNORESTATUS */

struct ResIgnoreStatus {
    ResIgnoreStatus(uint32_t track_, ChatResultCode result_, const std::vector<IgnoreContact>& ignore_)
        : track{track_}
        , result{result_}
        , ignore{ignore_} {}

    const ChatResponseType type = ChatResponseType::IGNORESTATUS;
    uint32_t track;
    ChatResultCode result;
    const std::vector<IgnoreContact>& ignore;
};

template <typename StreamT>
void write(StreamT& ar, const ResIgnoreStatus& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
    
    write(ar, static_cast<uint32_t>(data.ignore.size()));
    for (auto& ignoreContact : data.ignore) {
        write(ar, ignoreContact);
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

/** Begin SETAVATARATTRIBUTES */

struct ResSetAvatarAttributes {
    ResSetAvatarAttributes(uint32_t track_, ChatResultCode result_, const ChatAvatar* avatar_)
        : track{track_}
        , result{result_}
        , avatar{avatar_} {}

    const ChatResponseType type = ChatResponseType::SETAVATARATTRIBUTES;
    uint32_t track;
    ChatResultCode result;
    const ChatAvatar* avatar;
};

template <typename StreamT>
void write(StreamT& ar, const ResSetAvatarAttributes& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);

    if (data.result == ChatResultCode::SUCCESS) {
        write(ar, data.avatar);
    }
}

/** Begin GETANYAVATAR */

struct ResGetAnyAvatar {
    ResGetAnyAvatar(uint32_t track_, ChatResultCode result_, bool isOnline_,
                    const ChatAvatar* avatar_)
        : track{track_}
        , result{result_}
        , isOnline{isOnline_}
        , avatar{avatar_} {}

    const ChatResponseType type = ChatResponseType::GETANYAVATAR;
    uint32_t track;
    ChatResultCode result;
    bool isOnline;
    const ChatAvatar* avatar;
};

template <typename StreamT>
void write(StreamT& ar, const ResGetAnyAvatar& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.result);
    write(ar, data.isOnline);

    if (data.result == ChatResultCode::SUCCESS) {
        write(ar, data.avatar);
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
