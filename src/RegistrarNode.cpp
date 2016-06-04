#include "RegistrarNode.hpp"

#include "RegistrarClient.hpp"
#include "ServiceContainer.hpp"
#include "UdpLibrary.hpp"

#include <algorithm>
#include <iostream>

RegistrarNode::RegistrarNode(ServiceContainer* services)
    : services_{services} {
    auto config = services_->GetConfig();

    UdpManager::Params params;
    params.handler = this;
    params.port = config->registrarPort;

    std::cout << "Listening on port " << config->registrarPort << "\n";

    udpManager_ = new UdpManager(&params);
}

RegistrarNode::~RegistrarNode() { udpManager_->Release(); }

void RegistrarNode::AddClient(std::unique_ptr<RegistrarClient> client) {
    clients_.push_back(std::move(client));
}

void RegistrarNode::Tick() {
    udpManager_->GiveTime();

    auto& remove_iter = std::remove_if(std::begin(clients_), std::end(clients_), [](auto& client) {
        return client->GetConnection()->GetStatus() == UdpConnection::cStatusDisconnected;
    });

    if (remove_iter != std::end(clients_))
        clients_.erase(remove_iter);
}

void RegistrarNode::OnConnectRequest(UdpConnection* connection) {
    AddClient(std::make_unique<RegistrarClient>(connection, services_));
}
