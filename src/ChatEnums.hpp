
#pragma once

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
