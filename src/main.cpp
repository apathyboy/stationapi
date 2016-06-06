
#include "SwgChatApp.hpp"

#include <chrono>
#include <thread>

int main() {
    SwgChatApp app{{"192.168.0.10", 5001, "192.168.0.10", 5000, "chat.db"}};

    while (app.IsRunning()) {
        app.Tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}
