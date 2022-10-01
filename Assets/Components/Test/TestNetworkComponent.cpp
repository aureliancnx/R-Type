#include "Test/TestNetworkComponent.hpp"
#include "Debug.hpp"

using namespace RType::Component;

TestNetworkComponent::TestNetworkComponent(std::shared_ptr<KapEngine::GameObject> go) : KapMirror::Experimental::NetworkComponent(go, "TestNetworkComponent") {
}

void TestNetworkComponent::onStartServer() {
    KapEngine::Debug::log("TestNetworkComponent::onStartServer");
}
