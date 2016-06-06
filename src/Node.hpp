
#pragma once

#include "ServiceContainer.hpp"
#include "UdpLibrary.hpp"

#include <algorithm>
#include <memory>
#include <vector>
#include <cstdint>

template <typename NodeT, typename ClientT>
class Node : public UdpManagerHandler {
public:
    explicit Node(ServiceContainer* services, const std::string& listenAddress, uint16_t listenPort)
        : services_{services} {

        UdpManager::Params params;
        params.handler = this;
        params.port = listenPort;

        udpManager_ = new UdpManager(&params);
    }

    virtual ~Node() { udpManager_->Release(); }

    void Tick() {
        udpManager_->GiveTime();

        auto remove_iter = std::remove_if(std::begin(clients_), std::end(clients_), [](auto& client) {
            return client->GetConnection()->GetStatus() == UdpConnection::cStatusDisconnected;
        });

        if (remove_iter != std::end(clients_))
            clients_.erase(remove_iter);

        OnTick();
    }

private:

    virtual void OnTick() = 0;

    void OnConnectRequest(UdpConnection* connection) override {
        AddClient(std::make_unique<ClientT>(connection, services_));
    }

    void AddClient(std::unique_ptr<ClientT> client) { clients_.push_back(std::move(client)); }

    std::vector<std::unique_ptr<ClientT>> clients_;
    ServiceContainer* services_;
    UdpManager* udpManager_;
};
