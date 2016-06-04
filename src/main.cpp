
#include "SwgChatApp.hpp"

#include <chrono>
#include <thread>

int main() {
    SwgChatApp app;

    while (app.IsRunning()) {
        app.Tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}
