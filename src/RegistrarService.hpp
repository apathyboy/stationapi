
#pragma once

#include "UdpHandler.hpp"

#include <memory>
#include <vector>

class RegistrarClient;

class RegistrarService : public UdpManagerHandler {
public:
    RegistrarService(const std::string& registrarAddress, uint16_t registrarPort);
    ~RegistrarService();

    void AddClient(std::unique_ptr<RegistrarClient> client);

    void Tick();

private:
    virtual void OnConnectRequest(UdpConnection* connection) override;
    std::vector<std::unique_ptr<RegistrarClient>> clients_;

    UdpManager* udpManager_;
};
