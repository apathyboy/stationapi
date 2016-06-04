
#pragma once

#include "UdpLibrary.hpp"

class RegistrarClient : public UdpConnectionHandler {
public:
    explicit RegistrarClient(UdpConnection* connection);

    UdpConnection* GetConnection() { return connection_; }

private:
    void OnRoutePacket(UdpConnection* connection, const uchar* data, int length) override;

    UdpConnection* connection_;
};