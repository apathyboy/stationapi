
#include "RegistrarNode.hpp"

#include "ServiceContainer.hpp"

RegistrarNode::RegistrarNode(ServiceContainer* services)
    : Node(services, services->GetConfig()->registrarAddress, services->GetConfig()->registrarPort)
    , services_{services} {}

RegistrarNode::~RegistrarNode() {}

void RegistrarNode::OnTick() {}

