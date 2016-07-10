include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/externals/easyloggingpp
    ${Boost_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIR})

if(HAVE_UDPLIBRARY)
    include_directories(${PROJECT_SOURCE_DIR}/externals/udplibrary)
endif()

set(SOURCES
    protocol/AddBan.hpp
    protocol/AddFriend.hpp
    protocol/AddIgnore.hpp
    protocol/AddInvite.hpp
    protocol/AddModerator.hpp
    protocol/CreateRoom.hpp
    protocol/DestroyAvatar.hpp
    protocol/DestroyRoom.hpp
    protocol/EnterRoom.hpp
    protocol/FailoverReLoginAvatar.hpp
    protocol/FriendStatus.hpp
    protocol/GetAnyAvatar.hpp
    protocol/GetPersistentHeaders.hpp
    protocol/GetPersistentMessage.hpp
    protocol/GetRoom.hpp
    protocol/GetRoomSummaries.hpp
    protocol/IgnoreStatus.hpp
    protocol/KickAvatar.hpp
    protocol/LeaveRoom.hpp
    protocol/LoginAvatar.hpp
    protocol/LogoutAvatar.hpp
    protocol/Protocol.cpp
    protocol/RegistrarGetChatServer.hpp
    protocol/RemoveBan.hpp
    protocol/RemoveFriend.hpp
    protocol/RemoveIgnore.hpp
    protocol/RemoveInvite.hpp
    protocol/RemoveModerator.hpp
    protocol/SendInstantMessage.hpp
    protocol/SendPersistentMessage.hpp
    protocol/SendRoomMessage.hpp
    protocol/SetApiVersion.hpp
    protocol/SetAvatarAttributes.hpp
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
