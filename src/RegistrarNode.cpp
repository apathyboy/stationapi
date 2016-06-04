#include "RegistrarNode.hpp"

#include "RegistrarClient.hpp"
#include "ServiceContainer.hpp"
#include "UdpLibrary.hpp"

#include <algorithm>

RegistrarNode::RegistrarNode(ServiceContainer* services)
    : services_{services} {
    auto config = services_->GetConfig();

    UdpManager::Params params;
    params.handler = this;
    params.port = config->registrarPort;

    udpManager_ = new UdpManager(&params);
}

RegistrarNode::~RegistrarNode() { udpManager_->Release(); }

void RegistrarNode::AddClient(std::unique_ptr<RegistrarClient> client) {
    clients_.push_back(std::move(client));
}

void RegistrarNode::Tick() {
    udpManager_->GiveTime();

    clients_.erase(std::remove_if(std::begin(clients_), std::end(clients_), [](auto& client) {
        return client->GetConnection()->GetStatus() == UdpConnection::cStatusDisconnected;
    }));
}

void RegistrarNode::OnConnectRequest(UdpConnection* connection) {
    AddClient(std::make_unique<RegistrarClient>(connection, services_));
}
