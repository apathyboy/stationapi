
#pragma once

#include "UdpHandler.hpp"

#include <memory>
#include <vector>

class RegistrarClient;
class ServiceContainer;

class RegistrarNode : public UdpManagerHandler {
public:
    RegistrarNode(ServiceContainer* services);
    ~RegistrarNode();

    void AddClient(std::unique_ptr<RegistrarClient> client);

    void Tick();

private:
    void OnConnectRequest(UdpConnection* connection) override;
    std::vector<std::unique_ptr<RegistrarClient>> clients_;

    ServiceContainer* services_;
    UdpManager* udpManager_;
};
