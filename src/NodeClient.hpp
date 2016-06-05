
#pragma once

#include "StreamUtils.hpp"
#include "UdpHandler.hpp"

#include <array>

class UdpConnection;

template <int N>
class NodeClient : public UdpConnectionHandler {
public:
    explicit NodeClient(UdpConnection* connection)
        : connection_{connection} {
        connection_->AddRef();
    }

    virtual ~NodeClient() {
        connection_->SetHandler(nullptr);
        connection_->Disconnect();
        connection_->Release();
    }

    template <typename T>
    void SendMessage(T& message) {
        BinarySinkStream ostream{buffer_.data(), buffer_.size()};
        write(ostream, message);

        auto length = static_cast<int>(boost::iostreams::seek(ostream, 0, std::ios_base::cur));
        logNetworkMessage(connection_, "Registrar Message To", reinterpret_cast<unsigned char*>(buffer_.data()), length);
        connection_->Send(cUdpChannelReliable1, buffer_.data(), length);
    }

    UdpConnection* GetConnection() { return connection_; }

    virtual void OnIncoming(BinarySourceStream& istream) = 0;

private:
    void OnRoutePacket(UdpConnection* connection, const uchar* data, int length) override {
        logNetworkMessage(connection, "Registrar Message From", data, length);

        BinarySourceStream istream{ reinterpret_cast<const char*>(data), length };        
        OnIncoming(istream);
    }

    std::array<char, N> buffer_;
    UdpConnection* connection_;
};
