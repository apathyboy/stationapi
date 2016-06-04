
#pragma once

#include <array>

class UdpConnection;

template <int N>
struct NodeClient {
    template <typename T>
    void SendMessage(UdpConnection* connection, T& message) {
        BinarySinkStream ostream{buffer.data(), buffer.size()};

        write(ostream, message);

        connection->Send(cUdpChannelReliable1, buffer.data(),
            static_cast<int>(boost::iostreams::seek(ostream, 0, std::ios_base::cur)));
    }

    std::array<char, N> buffer;
};
