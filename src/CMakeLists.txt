include_directories(
    ${PROJECT_SOURCE_DIR}/udplibrary)

add_executable(swgchat
    main.cpp)

target_link_libraries(swgchat
    udplibrary)
