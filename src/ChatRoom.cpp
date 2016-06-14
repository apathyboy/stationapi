
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
    return IsInRoom(avatar->avatarId);
}

bool ChatRoom::IsInRoom(uint32_t avatarId) const {
    return std::find_if(std::begin(avatars_), std::end(avatars_), [avatarId](ChatAvatar* roomAvatar) {
        return roomAvatar->avatarId == avatarId;
    }) != std::end(avatars_);
}

void ChatRoom::ExitRoom(uint32_t avatarId) {
    auto avatarsIter = std::remove_if(std::begin(avatars_), std::end(avatars_), [avatarId](auto avatar) {
        return avatar->avatarId == avatarId;
    });

    if (avatarsIter != std::end(avatars_)) {
        avatars_.erase(avatarsIter);
    }

    auto administratorsIter = std::remove_if(std::begin(administrators_), std::end(administrators_), [avatarId](auto avatar) {
        return avatar->avatarId == avatarId;
    });

    if (administratorsIter != std::end(administrators_)) {
        administrators_.erase(administratorsIter);
    }

    auto moderatorsIter = std::remove_if(std::begin(moderators_), std::end(moderators_), [avatarId](auto avatar) {
        return avatar->avatarId == avatarId;
    });

    if (moderatorsIter != std::end(moderators_)) {
        moderators_.erase(moderatorsIter);
    }

    auto tempModeratorsIter = std::remove_if(std::begin(tempModerators_), std::end(tempModerators_), [avatarId](auto avatar) {
        return avatar->avatarId == avatarId;
    });

    if (tempModeratorsIter != std::end(tempModerators_)) {
        tempModerators_.erase(tempModeratorsIter);
    }
}
