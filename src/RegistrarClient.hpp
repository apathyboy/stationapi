
#pragma once

#include "NodeClient.hpp"

class RegistrarNode;
class UdpConnection;

class RegistrarClient : public NodeClient<2048> {
public:
    RegistrarClient(UdpConnection* connection, RegistrarNode* node);
    virtual ~RegistrarClient();

private:
    void OnIncoming(BinarySourceStream& istream) override;

    void HandleGetChatServer(BinarySourceStream& istream);

    RegistrarNode* node_;
};
