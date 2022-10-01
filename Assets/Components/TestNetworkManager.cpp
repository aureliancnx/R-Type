#include "TestNetworkManager.hpp"
#include "KapEngine.hpp"
#include "Debug.hpp"

using namespace RType::Component;

TestNetworkManager::TestNetworkManager(std::shared_ptr<KapEngine::GameObject> &go, std::shared_ptr<KapMirror::Compression> &compression, bool _isServer) : KapMirror::NetworkManager(go) {
    this->setCompression(compression);
    isServer = _isServer;
}

void TestNetworkManager::onStart() {
    KapEngine::Debug::log("TestNetworkManager::onStart");
    if (isServer) {
        KapEngine::Debug::log("TestNetworkManager::onStart: Starting server");
        startServer();
    } else {
        KapEngine::Debug::log("TestNetworkManager::onStart: Starting client");
        startClient();
    }
}
