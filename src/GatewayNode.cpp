
#include "GatewayNode.hpp"

#include "ServiceContainer.hpp"

GatewayNode::GatewayNode(ServiceContainer* services)
    : Node(services, services->GetConfig()->gatewayAddress, services->GetConfig()->gatewayPort)
    , services_{services} {}

GatewayNode::~GatewayNode() {}

void GatewayNode::OnTick() {}
