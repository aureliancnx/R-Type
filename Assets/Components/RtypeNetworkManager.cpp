#include "RtypeNetworkManager.hpp"

using namespace RType;

RtypeNetworkManager::RtypeNetworkManager(std::shared_ptr<KapEngine::GameObject> go, bool _isServer) : KapMirror::NetworkManager(go), isServer(_isServer) {}

void RtypeNetworkManager::onStart() {
    // Clean up
    players.clear();
}

#pragma region Server

void RtypeNetworkManager::onServerClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KapEngine::Debug::log("Client connected");

    std::shared_ptr<KapEngine::GameObject> player;
    getServer()->spawnObject("Player", {10, 50, 0}, player);

    players[connection->getNetworkId()] = player;
}

void RtypeNetworkManager::onServerClientDisconnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KapEngine::Debug::log("Client disconnected");

    std::shared_ptr<KapEngine::GameObject> player;
    if (players.tryGetValue(connection->getNetworkId(), player)) {
        getServer()->destroyObject(player);
    }
}

#pragma endregion
