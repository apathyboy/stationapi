#include "RegistrarNode.hpp"

#include "RegistrarClient.hpp"
#include "ServiceContainer.hpp"
#include "UdpLibrary.hpp"

#include <algorithm>
#include <iostream>

RegistrarNode::RegistrarNode(ServiceContainer* services)
    : Node(services, services->GetConfig()->registrarAddress, services->GetConfig()->registrarPort)
    , services_{services} {}

RegistrarNode::~RegistrarNode() {}

void RegistrarNode::OnTick() {}

