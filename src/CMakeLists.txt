include_directories(
    ${PROJECT_SOURCE_DIR}/udplibrary)

add_executable(swgchat
    main.cpp
    RegistrarClient.cpp
    RegistrarClient.hpp
    RegistrarService.cpp
    RegistrarService.hpp
    Request.hpp
    Response.hpp
    SwgChatApp.cpp
    SwgChatApp.hpp)

target_link_libraries(swgchat
    udplibrary)

if(WIN32)
    target_link_libraries(swgchat ws2_32)
endif()
