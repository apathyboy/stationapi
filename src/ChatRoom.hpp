
#pragma once

#include <string>

class ChatRoom {
public:
    const std::wstring& GetRoomAddress() const { return roomAddress_; }
    const std::wstring& GetRoomTopic() const { return roomTopic_; }
    uint32_t GetRoomAttributes() const { return roomAttributes_; }
    uint32_t GetCurrentRoomSize() const { return 0; }
    uint32_t GetMaxRoomSize() const { return 0; }

private:
    std::wstring creatorName_;
    std::wstring creatorAddress_;
    std::wstring roomName_;
    std::wstring roomTopic_;
    std::wstring roomPassword_;
    std::wstring roomPrefix_;
    std::wstring roomAddress_;

    uint32_t creatorId_;
    uint32_t roomAttributes_;
    uint32_t maxRoomSize_;
    uint32_t roomId_;
    uint32_t createTime_;
    uint32_t nodeLevel_;
    uint32_t roomMessageId_;
};
