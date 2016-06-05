
#pragma once

#include "Node.hpp"
#include "GatewayClient.hpp"

class ServiceContainer;

class GatewayNode : public Node<GatewayNode, GatewayClient> {
public:
    GatewayNode(ServiceContainer* services);
    ~GatewayNode();

private:
    void OnTick() override;

    ServiceContainer* services_;
};
