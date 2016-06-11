
#include "ChatRoom.hpp"
#include "ChatAvatar.hpp"

#include <algorithm>

ChatResultCode ChatRoom::EnterRoom(ChatAvatar* avatar, const std::wstring& password) {
    ChatResultCode result = ChatResultCode::SUCCESS;

    if (password.compare(roomPassword_) != 0) {
        result = ChatResultCode::ROOM_PRIVATEROOM;
    } else {
        if (IsInRoom(avatar)) {
            result = ChatResultCode::ROOM_ALREADYINROOM;
        } else {
            avatars_.push_back(avatar);
        }
    }

    return result;
}

bool ChatRoom::IsInRoom(ChatAvatar* avatar) const {
    return std::find_if(std::begin(avatars_), std::end(avatars_), [avatar](ChatAvatar* roomAvatar) {
        return avatar->avatarId == roomAvatar->avatarId;
    }) != std::end(avatars_);
}
