#include "NetworkManager.hpp"
#include "KapEngine.hpp"
#include "Debug.hpp"

using namespace RType::Component;

TestNetworkManager::TestNetworkManager(std::shared_ptr<KapEngine::GameObject> go, bool _isServer) : KapMirror::NetworkManager(go) {
    isServer = _isServer;
}

void TestNetworkManager::onStart() {
    if (isServer) {
        startServer();
    } else {
        startClient();
    }
}

void TestNetworkManager::onUpdate() {
    NetworkManager::onUpdate();
}

void TestNetworkManager::onServerClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KapEngine::Debug::log("TestNetworkManager::onServerClientConnected");

    std::shared_ptr<KapEngine::GameObject> spaceShip;
    getServer()->spawnObject("SpaceShip", spaceShip);
}
