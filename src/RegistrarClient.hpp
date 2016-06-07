
#pragma once

#include "NodeClient.hpp"

class RegistrarNode;
class UdpConnection;

struct ReqRegistrarGetChatServer;

class RegistrarClient : public NodeClient<2048> {
public:
    RegistrarClient(UdpConnection* connection, RegistrarNode* node);
    virtual ~RegistrarClient();

private:
    void OnIncoming(BinarySourceStream& istream) override;

    void HandleGetChatServer(const ReqRegistrarGetChatServer& request);

    RegistrarNode* node_;
};
