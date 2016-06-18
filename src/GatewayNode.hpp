
#pragma once

#include "Node.hpp"
#include "GatewayClient.hpp"

#include <memory>

class ChatAvatarService;
class ChatRoomService;
class PersistentMessageService;
class ContactService;
struct SwgChatConfig;
struct sqlite3;

class GatewayNode : public Node<GatewayNode, GatewayClient> {
public:
    explicit GatewayNode(SwgChatConfig& config);
    ~GatewayNode();

    ChatAvatarService* GetAvatarService();
    ChatRoomService* GetRoomService();
    PersistentMessageService* GetMessageService();
    ContactService* GetContactService();
    SwgChatConfig& GetConfig();

private:
    void OnTick() override;

    std::unique_ptr<ChatAvatarService> avatarService_;
    std::unique_ptr<ChatRoomService> roomService_;
    std::unique_ptr<PersistentMessageService> messageService_;
    std::unique_ptr<ContactService> contactService_;
    SwgChatConfig& config_;
    sqlite3* db_;
};
