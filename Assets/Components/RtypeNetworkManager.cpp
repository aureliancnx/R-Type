#include "RtypeNetworkManager.hpp"

using namespace RType;

RtypeNetworkManager::RtypeNetworkManager(std::shared_ptr<KapEngine::GameObject> go, bool _isServer) : KapMirror::NetworkManager(go), isServer(_isServer) {}

void RtypeNetworkManager::onStart() {
    // Clean up
    players.clear();

    if (isServer) {
        registerServerHandlers();
    } else {
        registerClientHandlers();
    }
}

#pragma region Client

void RtypeNetworkManager::registerClientHandlers() {
}

#pragma endregion

#pragma region Server

void RtypeNetworkManager::registerServerHandlers() {
    getServer()->registerHandler<PlayerInputMessage>([this](std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerInputMessage& message) {
        onPlayerInputMessage(connection, message);
    });
}

void RtypeNetworkManager::onServerClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KAP_DEBUG_LOG("Player[" + std::to_string(connection->getNetworkId()) + "] -> connected");

    std::shared_ptr<KapEngine::GameObject> player;
    getServer()->spawnObject("Player", {10, 50, 0}, player);

    players[connection->getNetworkId()] = player;
}

void RtypeNetworkManager::onServerClientDisconnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KAP_DEBUG_LOG("Player[" + std::to_string(connection->getNetworkId()) + "] -> disconnected");

    std::shared_ptr<KapEngine::GameObject> player;
    if (players.tryGetValue(connection->getNetworkId(), player)) {
        getServer()->destroyObject(player);
    }
}

void RtypeNetworkManager::onPlayerInputMessage(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerInputMessage& message) {
    KAP_DEBUG_LOG("Player[" + std::to_string(connection->getNetworkId()) + "] -> input message received");

    std::shared_ptr<KapEngine::GameObject> player;
    if (players.tryGetValue(connection->getNetworkId(), player)) {
        auto &transform = player->getComponent<KapEngine::Transform>();

        transform.setPosition({transform.getLocalPosition().getX() + message.x, transform.getLocalPosition().getY() + message.y});
    }
}

#pragma endregion
