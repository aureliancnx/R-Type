#include "NetworkManager.hpp"
#include "KapEngine.hpp"
#include "Debug.hpp"

using namespace RType::Component;

TestNetworkManager::TestNetworkManager(std::shared_ptr<KapEngine::GameObject> go, bool _isServer) : KapMirror::NetworkManager(go) {
    isServer = _isServer;
}

void TestNetworkManager::onStart() {
}

void TestNetworkManager::onUpdate() {
    NetworkManager::onUpdate();
}

