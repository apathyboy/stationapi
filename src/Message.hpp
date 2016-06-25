
#pragma once

#include "ChatAvatar.hpp"
#include "PersistentMessage.hpp"

#include <cstdint>
#include <string>

enum class ChatMessageType : uint16_t {
    // ChatAvatar message types
    INSTANTMESSAGE = 0, // 0
    ROOMMESSAGE,
    BROADCASTMESSAGE,
    FRIENDLOGIN,
    FRIENDLOGOUT,
    KICKROOM, // 5

    // ChatRoom message types
    ADDMODERATORROOM,
    REMOVEMODERATORROOM,
    REMOVEMODERATORAVATAR,
    ADDBANROOM,
    REMOVEBANROOM, // 10
    REMOVEBANAVATAR,
    ADDINVITEROOM,
    ADDINVITEAVATAR,
    REMOVEINVITEROOM,
    REMOVEINVITEAVATAR, // 15
    ENTERROOM,
    LEAVEROOM,
    DESTROYROOM,
    SETROOMPARAMS,
    PERSISTENTMESSAGE, // 20
    FORCEDLOGOUT,
    UNREGISTERROOMREADY,
    KICKAVATAR,
    ADDMODERATORAVATAR,
    ADDBANAVATAR, // 25
    ADDADMIN,
    REMOVEADMIN,
    FRIENDCONFIRMREQUEST,
    FRIENDCONFIRMRESPONSE,
    CHANGEROOMOWNER, // 30
    FORCEROOMFAILOVER,
    ADDTEMPORARYMODERATORROOM,
    ADDTEMPORARYMODERATORAVATAR,
    REMOVETEMPORARYMODERATORROOM,
    REMOVETEMPORARYMODERATORAVATAR, // 35
    GRANTVOICEROOM,
    GRANTVOICEAVATAR,
    REVOKEVOICEROOM,
    REVOKEVOICEAVATAR,
    SNOOP, // 40
    UIDLIST,
    REQUESTROOMENTRY,
    DELAYEDROOMENTRY,
    DENIEDROOMENTRY,
    FRIENDSTATUS, // 45
    FRIENDCONFIRMRECIPROCATE_REQUEST,
    FRIENDCONFIRMRECIPROCATE_RESPONSE,
    FILTERMESSAGE,
    FAILOVER_AVATAR_LIST,
    NOTIFY_FRIENDS_LIST_CHANGE, // 50
    NOTIFY_FRIEND_IS_REMOVED
};

/** Begin FRIENDLOGIN */

struct MFriendLogin {
    MFriendLogin(const ChatAvatar* avatar_, const std::wstring& friendAddress_, uint32_t destAvatarId_, const std::wstring& friendStatus_)
        : avatar{avatar_}
        , friendAddress{friendAddress_}
        , destAvatarId{destAvatarId_}
        , friendStatus{friendStatus_} {}

    const ChatMessageType type = ChatMessageType::FRIENDLOGIN;
    const uint32_t track = 0;
    const ChatAvatar* avatar;
    std::wstring friendAddress;
    uint32_t destAvatarId;
    std::wstring friendStatus;
};

template <typename StreamT>
void write(StreamT& ar, const MFriendLogin& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.avatar);
    write(ar, data.friendAddress);
    write(ar, data.destAvatarId);
    write(ar, data.friendStatus);
}

/** Begin PERSISTENTMESSAGE */

struct MPersistentMessage {
    MPersistentMessage(uint32_t destAvatarId_, PersistentHeader header_)
        : destAvatarId{destAvatarId_}
        , header{header_} {}

    const ChatMessageType type = ChatMessageType::PERSISTENTMESSAGE;
    const uint32_t track = 0;
    uint32_t destAvatarId;
    PersistentHeader header;
};

template <typename StreamT>
void write(StreamT& ar, const MPersistentMessage& data) {
    write(ar, data.type);
    write(ar, data.track);
    write(ar, data.destAvatarId);
    write(ar, data.header);
}
