
#pragma once

#include "ServiceContainer.hpp"

class SwgChatApp {
public:
    SwgChatApp();

    bool IsRunning() const { return isRunning_; }

    void Tick();

private:
    bool isRunning_ = true;
    ServiceContainer services_;
};
