#include "RtypeNetworkManager.hpp"
#include "Player/PlayerController.hpp"

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
    getClient()->registerHandler<PlayerAuthorityMessage>([this](std::shared_ptr<KapMirror::NetworkConnectionToServer> connection, PlayerAuthorityMessage& message) {
        onPlayerAuthorityMessage(connection, message);
    });
}

void RtypeNetworkManager::onPlayerAuthorityMessage(std::shared_ptr<KapMirror::NetworkConnectionToServer> connection, PlayerAuthorityMessage& message) {
    std::shared_ptr<KapEngine::GameObject> player;
    if (getClient()->getNetworkObject(message.networkId, player)) {
        auto& playerController = player->getComponent<PlayerController>();
        playerController.setLocalAuthoriy(true);
    }
}

#pragma endregion

#pragma region Server

void RtypeNetworkManager::registerServerHandlers() {
    getServer()->registerHandler<PlayerInputMessage>([this](std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerInputMessage& message) {
        onPlayerInputMessage(connection, message);
    });
    getServer()->registerHandler<PlayerShootMessage>([this](std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerShootMessage& message) {
        onPlayerShootMessage(connection, message);
    });
}

void RtypeNetworkManager::onServerClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KAP_DEBUG_LOG("Player[" + std::to_string(connection->getNetworkId()) + "] -> connected");

    std::shared_ptr<KapEngine::GameObject> player;
    getServer()->spawnObject("Player", {0, 0, 0}, player);

    players[connection->getNetworkId()] = player;

    // Send player authority
    PlayerAuthorityMessage message;
    message.networkId = connection->getNetworkId();
    connection->send(message);
}

void RtypeNetworkManager::onServerClientDisconnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KAP_DEBUG_LOG("Player[" + std::to_string(connection->getNetworkId()) + "] -> disconnected");

    std::shared_ptr<KapEngine::GameObject> player;
    if (players.tryGetValue(connection->getNetworkId(), player)) {
        getServer()->destroyObject(player);
    }
}

void RtypeNetworkManager::onPlayerInputMessage(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerInputMessage& message) {
    std::shared_ptr<KapEngine::GameObject> player;
    if (players.tryGetValue(connection->getNetworkId(), player)) {
        auto& controllerComponent = player->getComponent<RType::PlayerController>();
        controllerComponent.movePlayer(KapEngine::Tools::Vector2(message.x, message.y));
    }
}

void RtypeNetworkManager::onPlayerShootMessage(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerShootMessage& message) {
    std::shared_ptr<KapEngine::GameObject> player;
    if (players.tryGetValue(connection->getNetworkId(), player)) {
        auto& controllerComponent = player->getComponent<RType::PlayerController>();
        controllerComponent.shoot();
    }
}

#pragma endregion
