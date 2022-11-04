#include "RtypeNetworkManager.hpp"
#include "Player/PlayerController.hpp"
#include "Player/PlayerSkin.hpp"
#include "Enemies/ShipEnemy.hpp"

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

void RtypeNetworkManager::sendKeepAlive(KapMirror::NetworkIdentity *identity) {
    PlayerKeepAliveMessage keepAlive;
    keepAlive.timestamp = KapMirror::NetworkTime::localTime();

    std::vector<long long> playerKeepAlives;

    keepAlives.tryGetValue(identity->getNetworkId(), playerKeepAlives);
    playerKeepAlives.push_back(keepAlive.timestamp);
    keepAlives[identity->getNetworkId()] = playerKeepAlives;
    getServer()->sendToClient(keepAlive, identity->getNetworkId());
}

void RtypeNetworkManager::registerClientHandlers() {
    getClient()->registerHandler<PlayerAuthorityMessage>([this](std::shared_ptr<KapMirror::NetworkConnectionToServer> connection, PlayerAuthorityMessage& message) {
        onPlayerAuthorityMessage(connection, message);
    });
    getClient()->registerHandler<PlayerKeepAliveMessage>([this](std::shared_ptr<KapMirror::NetworkConnectionToServer> connection, PlayerKeepAliveMessage& message) {
        onServerSendKeepAlive(connection, message);
    });
    getClient()->registerHandler<ErrorOnStartGameMessage>([this](std::shared_ptr<KapMirror::NetworkConnectionToServer> connection, ErrorOnStartGameMessage& message) {
        onErrorOnStartGameMessage(connection, message);
    });
}

void RtypeNetworkManager::onPlayerAuthorityMessage(std::shared_ptr<KapMirror::NetworkConnectionToServer> connection, PlayerAuthorityMessage& message) {
    std::shared_ptr<KapEngine::GameObject> player;
    if (getClient()->getExistingObject(message.networkId, player)) {
        auto& playerController = player->getComponent<PlayerController>();
        playerController.setLocalAuthority(true);
    }
}

void RtypeNetworkManager::onServerSendKeepAlive(std::shared_ptr<KapMirror::NetworkConnectionToServer> connection, PlayerKeepAliveMessage& message) {
    PlayerKeepAliveMessage reply;
    reply.timestamp = message.timestamp;
    getClient()->send(message);
}

void RtypeNetworkManager::onErrorOnStartGameMessage(std::shared_ptr<KapMirror::NetworkConnectionToServer> connection, ErrorOnStartGameMessage& message) {
    KAP_DEBUG_ERROR("Error on start game: " + message.errorMessage);
    //TODO: Handle error
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
    getServer()->registerHandler<PlayerKeepAliveMessage>([this](std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerKeepAliveMessage& message) {
        onClientSendKeepAlive(connection, message);
    });
    getServer()->registerHandler<StartGameMessage>([this](std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, StartGameMessage& message) {
        onStartGameMessage(connection, message);
    });
}

void RtypeNetworkManager::onServerClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KapEngine::Debug::log("Player[" + std::to_string(connection->getConnectionId()) + "] -> connected");

    std::shared_ptr<KapEngine::GameObject> player;
    getServer()->spawnObject("Player", {0, 0, 0}, [this](std::shared_ptr<KapEngine::GameObject> go) {
        auto& networkIdentity = go->getComponent<KapMirror::NetworkIdentity>();
        auto& playerSkin = go->getComponent<PlayerSkin>();

        // Set Default Skin (Send later the player skin)
        playerSkin.setSkinId(1);
    }, player);

    players[connection->getConnectionId()] = player;

    auto& networkIdentity = player->getComponent<KapMirror::NetworkIdentity>();

    // Send player authority
    PlayerAuthorityMessage message;
    message.networkId = networkIdentity.getNetworkId();
    connection->send(message);
}

void RtypeNetworkManager::onServerClientDisconnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KAP_DEBUG_LOG("Player[" + std::to_string(connection->getConnectionId()) + "] -> disconnected");

    std::shared_ptr<KapEngine::GameObject> player;
    if (players.tryGetValue(connection->getConnectionId(), player)) {
        getServer()->destroyObject(player);
    }
}

void RtypeNetworkManager::onClientSendKeepAlive(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerKeepAliveMessage& message) {
    std::vector<long long> playerKeepAlives;
    if (keepAlives.tryGetValue(connection->getConnectionId(), playerKeepAlives)) {
        if (std::find(playerKeepAlives.begin(), playerKeepAlives.end(), message.timestamp) != playerKeepAlives.end()) {
            long long ping = KapMirror::NetworkTime::localTime() - message.timestamp;

            KAP_DEBUG_LOG("Player[" + std::to_string(connection->getConnectionId()) + "] -> ping: " + std::to_string(ping));
            playerKeepAlives.erase(std::remove(playerKeepAlives.begin(), playerKeepAlives.end(), message.timestamp), playerKeepAlives.end());
        } else{
            KAP_DEBUG_LOG("Player[" + std::to_string(connection->getConnectionId()) + "] -> bad keepAlive packet: unknown timestamp '" + std::to_string(message.timestamp) + "'");
        }
    } else{
        KAP_DEBUG_LOG("Player[" + std::to_string(connection->getConnectionId()) + "] -> received keepAlive timestamp " + std::to_string(message.timestamp) + " without a list");
    }
}

void RtypeNetworkManager::onPlayerInputMessage(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerInputMessage& message) {
    std::shared_ptr<KapEngine::GameObject> player;
    if (players.tryGetValue(connection->getConnectionId(), player)) {
        auto& controllerComponent = player->getComponent<RType::PlayerController>();
        controllerComponent.movePlayer(KapEngine::Tools::Vector2(message.x, message.y));
    }
}

void RtypeNetworkManager::onPlayerShootMessage(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerShootMessage& message) {
    std::shared_ptr<KapEngine::GameObject> player;
    if (players.tryGetValue(connection->getConnectionId(), player)) {
        auto& controllerComponent = player->getComponent<RType::PlayerController>();
        controllerComponent.shoot();
    }
}

void RtypeNetworkManager::onStartGameMessage(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, StartGameMessage& message) {
    if (isGameStarted) {
        KAP_DEBUG_LOG("Game already started");
        sendErrorOnStartGame(connection, "Game already started");
        return;
    }
    if (players.size() < 2) {
        KAP_DEBUG_LOG("Not enough players to start the game");
        sendErrorOnStartGame(connection, "Not enough players to start the game");
        return;
    }

    isGameStarted = true;
    startGame();
}

void RtypeNetworkManager::sendErrorOnStartGame(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, const std::string &errorMessage) {
    ErrorOnStartGameMessage message;
    message.errorMessage = errorMessage;

    connection->send(message);
}

void RtypeNetworkManager::startGame() {
    KapEngine::Debug::log("Start game");

    // TODO: Implement Map Manager
    std::shared_ptr<KapEngine::GameObject> enemy;
    for (int i = 1; i <= 10; i++) {
        getServer()->spawnObject("Enemy:BoubouleEnemy", {1280 + 100 + ((float)i * 100), 100 + ((float)i * 50), 0}, enemy);
    }
    getServer()->spawnObject("Enemy:TentaclesBossEnemy", {1280 - 200, 100, 0}, enemy);
}

#pragma endregion
