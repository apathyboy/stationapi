include_directories(
    ${PROJECT_SOURCE_DIR}/udplibrary)

add_executable(swgchat
    main.cpp
    ServiceContainer.hpp
    SwgChatApp.cpp
    SwgChatApp.hpp)

target_link_libraries(swgchat
    udplibrary)
