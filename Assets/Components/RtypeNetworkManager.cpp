#include "RtypeNetworkManager.hpp"

using namespace RType;

RtypeNetworkManager::RtypeNetworkManager(std::shared_ptr<KapEngine::GameObject> go) : KapMirror::NetworkManager(go) {
}

void RtypeNetworkManager::onStart() {
}

void RtypeNetworkManager::onUpdate() {
    KapMirror::NetworkManager::onUpdate();
}

void RtypeNetworkManager::onServerClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KapEngine::Debug::log("Client connected");

    std::shared_ptr<KapEngine::GameObject> player;
    getServer()->spawnObject("Player", {0, 0, 0}, player);
}
