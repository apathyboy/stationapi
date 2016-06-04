#include "RegistrarService.hpp"

#include "RegistrarClient.hpp"
#include "UdpLibrary.hpp"

#include <algorithm>

RegistrarService::RegistrarService(const std::string& registrarAddress, uint16_t registrarPort) {
    UdpManager::Params params;
    params.handler = this;
    params.port = registrarPort;

    udpManager_ = new UdpManager(&params);
}

RegistrarService::~RegistrarService() { udpManager_->Release(); }

void RegistrarService::AddClient(std::unique_ptr<RegistrarClient> client) {
    clients_.push_back(std::move(client));
}

void RegistrarService::Tick() {
    udpManager_->GiveTime();

    clients_.erase(std::remove_if(std::begin(clients_), std::end(clients_), [](auto& client) {
        return client->GetConnection()->GetStatus() == UdpConnection::cStatusDisconnected;
    }));
}

void RegistrarService::OnConnectRequest(UdpConnection* connection) {
    AddClient(std::make_unique<RegistrarClient>(connection));
}
