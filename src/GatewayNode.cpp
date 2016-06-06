
#include "GatewayNode.hpp"

#include "ChatAvatarService.hpp"
#include "SwgChatConfig.hpp"

#include <sqlite3.h>

GatewayNode::GatewayNode(SwgChatConfig& config)
    : Node(this, config.gatewayAddress, config.gatewayPort)
    , config_{config} {
    if (sqlite3_open(config.chatDatabasePath.c_str(), &db_) != SQLITE_OK) {
        throw std::runtime_error("Can't open database: " + std::string{sqlite3_errmsg(db_)});
    }

    avatarService_ = std::make_unique<ChatAvatarService>(db_);
}

GatewayNode::~GatewayNode() {
    sqlite3_close(db_);
}

ChatAvatarService* GatewayNode::GetAvatarService() {
    return avatarService_.get();
}

SwgChatConfig& GatewayNode::GetConfig() {
    return config_;
}

void GatewayNode::OnTick() {}
