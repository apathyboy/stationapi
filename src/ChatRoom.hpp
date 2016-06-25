
#pragma once

#include "ChatEnums.hpp"

#include <string>
#include <vector>

class ChatAvatar;

class ChatRoom {
public:
    ChatRoom() = default;
    ChatRoom(uint32_t creatorId,
             const std::wstring& creatorName, const std::wstring& creatorAddress,
             const std::wstring& roomName, const std::wstring& roomTopic, const std::wstring& roomPassword,
             uint32_t roomAttributes, uint32_t maxRoomSize, const std::wstring& roomAddress,
             const std::wstring& srcAddress)
        : creatorName_{creatorName}
        , creatorAddress_{creatorAddress}
        , roomName_{roomName}
        , roomTopic_{roomTopic}
        , roomPassword_{roomPassword}
        , roomAddress_{roomAddress+L"+"+roomName}
        , creatorId_{creatorId}
        , roomAttributes_{roomAttributes}
        , maxRoomSize_{maxRoomSize}
    {}
    
    ChatResultCode EnterRoom(ChatAvatar* avatar, const std::wstring& password);
    bool IsInRoom(ChatAvatar* avatar) const;
    bool IsInRoom(uint32_t avatarId) const;
    void ExitRoom(uint32_t avatarId);

    uint32_t GetCreatorId() const { return creatorId_; }
    const std::wstring& GetCreatorName() const { return creatorName_; }
    const std::wstring& GetCreatorAddress() const { return creatorAddress_; }
    const std::wstring& GetRoomName() const { return roomName_; }
    const std::wstring& GetRoomAddress() const { return roomAddress_; }
    const std::wstring& GetRoomTopic() const { return roomTopic_; }
    const std::wstring& GetRoomPassword() const { return roomPassword_; }
    const std::wstring& GetRoomPrefix() const { return roomPrefix_; }
    uint32_t GetRoomAttributes() const { return roomAttributes_; }
    uint32_t GetCurrentRoomSize() const { return avatars_.size(); }
    uint32_t GetMaxRoomSize() const { return maxRoomSize_; }
    uint32_t GetRoomId() const { return roomId_; }
    uint32_t GetCreateTime() const { return createTime_; }
    uint32_t GetNodeLevel() const { return nodeLevel_; }

    const std::vector<ChatAvatar*> GetAvatars() const { return avatars_; }
    const std::vector<ChatAvatar*> GetAdminstrators() const { return administrators_; }
    const std::vector<ChatAvatar*> GetModerators() const { return moderators_; }
    const std::vector<ChatAvatar*> GetTempModerators() const { return tempModerators_; }
    const std::vector<ChatAvatar*> GetBanned() const { return banned_; }
    const std::vector<ChatAvatar*> GetInvited() const { return invited_; }
    const std::vector<ChatAvatar*> GetVoice() const { return voice_; }

private:
    friend class ChatRoomService;
    std::wstring creatorName_;
    std::wstring creatorAddress_;
    std::wstring roomName_;
    std::wstring roomTopic_;
    std::wstring roomPassword_;
    std::wstring roomPrefix_ = L"";
    std::wstring roomAddress_;

    uint32_t creatorId_;
    uint32_t roomAttributes_;
    uint32_t maxRoomSize_;
    uint32_t roomId_ = 0;
    uint32_t createTime_ = 0;
    uint32_t nodeLevel_ = 0;
    uint32_t roomMessageId_ = 0;

    std::vector<ChatAvatar*> avatars_;
    std::vector<ChatAvatar*> administrators_;
    std::vector<ChatAvatar*> moderators_;
    std::vector<ChatAvatar*> tempModerators_;
    std::vector<ChatAvatar*> banned_;
    std::vector<ChatAvatar*> invited_;
    std::vector<ChatAvatar*> voice_;
};

template <typename StreamT>
void write(StreamT& ar, const ChatRoom& data) {
    write(ar, data.GetCreatorName());
    write(ar, data.GetCreatorAddress());
    write(ar, data.GetCreatorId());
    write(ar, data.GetRoomName());
    write(ar, data.GetRoomTopic());
    write(ar, data.GetRoomPrefix());
    write(ar, data.GetRoomAddress());
    write(ar, data.GetRoomPassword());
    write(ar, data.GetRoomAttributes());
    write(ar, data.GetMaxRoomSize());
    write(ar, data.GetRoomId());
    write(ar, data.GetCreateTime());
    write(ar, data.GetNodeLevel());

    auto& avatars = data.GetAvatars();
    write(ar, static_cast<uint32_t>(avatars.size()));
    for (auto& avatar : avatars)
        write(ar, avatar);

    auto& administrators = data.GetAdminstrators();
    write(ar, static_cast<uint32_t>(administrators.size()));
    for (auto& avatar : administrators)
        write(ar, avatar);

    auto& moderators = data.GetModerators();
    write(ar, static_cast<uint32_t>(moderators.size()));
    for (auto& avatar : moderators)
        write(ar, avatar);

    auto& tempModerators = data.GetTempModerators();
    write(ar, static_cast<uint32_t>(tempModerators.size()));
    for (auto& avatar : tempModerators)
        write(ar, avatar);

    auto& banned = data.GetBanned();
    write(ar, static_cast<uint32_t>(banned.size()));
    for (auto& avatar : banned)
        write(ar, avatar);

    auto& invited = data.GetInvited();
    write(ar, static_cast<uint32_t>(invited.size()));
    for (auto& avatar : invited)
        write(ar, avatar);

    auto& voice = data.GetVoice();
    write(ar, static_cast<uint32_t>(voice.size()));
    for (auto& avatar : voice)
        write(ar, avatar);
}
