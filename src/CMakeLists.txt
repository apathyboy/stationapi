include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/externals/easyloggingpp
    ${Boost_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIR})

if(HAVE_UDPLIBRARY)
    include_directories(${PROJECT_SOURCE_DIR}/externals/udplibrary)
endif()

set(SOURCES
    protocol/AddBan.cpp
    protocol/AddBan.hpp
    protocol/AddFriend.cpp
    protocol/AddFriend.hpp
    protocol/AddIgnore.cpp
    protocol/AddIgnore.hpp
    protocol/AddInvite.cpp
    protocol/AddInvite.hpp
    protocol/AddModerator.cpp
    protocol/AddModerator.hpp
    protocol/CreateRoom.cpp
    protocol/CreateRoom.hpp
    protocol/DestroyAvatar.cpp
    protocol/DestroyAvatar.hpp
    protocol/DestroyRoom.cpp
    protocol/DestroyRoom.hpp
    protocol/EnterRoom.cpp
    protocol/EnterRoom.hpp
    protocol/FailoverReLoginAvatar.cpp
    protocol/FailoverReLoginAvatar.hpp
    protocol/FriendStatus.cpp
    protocol/FriendStatus.hpp
    protocol/GetAnyAvatar.cpp
    protocol/GetAnyAvatar.hpp
    protocol/GetPersistentHeaders.cpp
    protocol/GetPersistentHeaders.hpp
    protocol/GetPersistentMessage.cpp
    protocol/GetPersistentMessage.hpp
    protocol/GetRoom.cpp
    protocol/GetRoom.hpp
    protocol/GetRoomSummaries.cpp
    protocol/GetRoomSummaries.hpp
    protocol/IgnoreStatus.cpp
    protocol/IgnoreStatus.hpp
    protocol/KickAvatar.cpp
    protocol/KickAvatar.hpp
    protocol/LeaveRoom.cpp
    protocol/LeaveRoom.hpp
    protocol/LoginAvatar.cpp
    protocol/LoginAvatar.hpp
    protocol/LogoutAvatar.cpp
    protocol/LogoutAvatar.hpp
    protocol/RegistrarGetChatServer.cpp
    protocol/RegistrarGetChatServer.hpp
    protocol/RemoveBan.cpp
    protocol/RemoveBan.hpp
    protocol/RemoveFriend.cpp
    protocol/RemoveFriend.hpp
    protocol/RemoveIgnore.cpp
    protocol/RemoveIgnore.hpp
    protocol/RemoveInvite.cpp
    protocol/RemoveInvite.hpp
    protocol/RemoveModerator.cpp
    protocol/RemoveModerator.hpp
    protocol/SendInstantMessage.cpp
    protocol/SendInstantMessage.hpp
    protocol/SendPersistentMessage.cpp
    protocol/SendPersistentMessage.hpp
    protocol/SendRoomMessage.cpp
    protocol/SendRoomMessage.hpp
    protocol/SetApiVersion.cpp
    protocol/SetApiVersion.hpp
    protocol/SetAvatarAttributes.cpp
    protocol/SetAvatarAttributes.hpp
    protocol/UpdatePersistentMessage.cpp
    protocol/UpdatePersistentMessage.hpp

    ChatAvatar.cpp
    ChatAvatar.hpp
    ChatAvatarService.cpp
    ChatAvatarService.hpp
    ChatEnums.cpp
    ChatEnums.hpp
    ChatRoom.cpp
    ChatRoom.hpp
    ChatRoomService.cpp
    ChatRoomService.hpp
    GatewayClient.cpp
    GatewayClient.hpp
    GatewayNode.cpp
    GatewayNode.hpp
    Message.hpp
    Node.hpp
    NodeClient.cpp
    NodeClient.hpp
    PersistentMessage.hpp
    PersistentMessageService.cpp
    PersistentMessageService.hpp
    RegistrarClient.cpp
    RegistrarClient.hpp
    RegistrarNode.cpp
    RegistrarNode.hpp
    Serialization.hpp
    SQLite3.hpp
    StreamUtils.cpp
    StreamUtils.hpp
    StringUtils.cpp
    StringUtils.hpp)

add_library(stationapi ${SOURCES})

GroupSourceByFilesystem("${SOURCES}")

add_executable(stationchat
    main.cpp
    StationChatApp.cpp
    StationChatApp.hpp
    StationChatConfig.hpp)

target_link_libraries(stationchat
    stationapi
    ${Boost_LIBRARIES}
    ${SQLite3_LIBRARY})

if (HAVE_UDPLIBRARY)
    target_link_libraries(stationchat udplibrary)
endif()

if(WIN32)
    target_link_libraries(stationchat ws2_32)
endif()
