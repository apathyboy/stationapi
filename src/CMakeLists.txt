include_directories(
    ${PROJECT_SOURCE_DIR}/udplibrary
    ${Boost_INCLUDE_DIRS})

add_executable(swgchat
    BinaryStream.hpp
    main.cpp
    Node.hpp
    NodeClient.hpp
    RegistrarClient.cpp
    RegistrarClient.hpp
    RegistrarNode.cpp
    RegistrarNode.hpp
    Request.hpp
    Response.hpp
    Serialization.hpp
    ServiceContainer.hpp
    StreamUtils.cpp
    StreamUtils.hpp
    StringUtils.cpp
    StringUtils.hpp
    SwgChatApp.cpp
    SwgChatApp.hpp
    SwgChatConfig.hpp)

target_link_libraries(swgchat
    udplibrary)

if(WIN32)
    target_link_libraries(swgchat ws2_32)
endif()
