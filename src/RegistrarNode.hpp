
#pragma once

#include "Node.hpp"
#include "RegistrarClient.hpp"

#include <memory>
#include <vector>

class ServiceContainer;

class RegistrarNode : public Node<RegistrarNode, RegistrarClient> {
public:
    RegistrarNode(ServiceContainer* services);
    ~RegistrarNode();

private:
    void OnTick() override;

    ServiceContainer* services_;
};
