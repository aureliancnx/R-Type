#include "RtypeNetworkManager.hpp"
#include "Player/PlayerController.hpp"
#include "Player/PlayerSkin.hpp"
#include "NetStatViewer.hpp"
#include "Campaign/MapManager.hpp"
#include <fstream>

using namespace RType;

RtypeNetworkManager::RtypeNetworkManager(std::shared_ptr<KapEngine::GameObject> go, bool _isServer)
    : KapMirror::NetworkManager(go), isServer(_isServer) {}

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
    getClient()->registerHandler<PlayerAuthorityMessage>(
        [this](const std::shared_ptr<KapMirror::NetworkConnectionToServer>& connection, PlayerAuthorityMessage& message) {
            onPlayerAuthorityMessage(connection, message);
        });
    getClient()->registerHandler<ErrorOnStartGameMessage>(
        [this](const std::shared_ptr<KapMirror::NetworkConnectionToServer>& connection, ErrorOnStartGameMessage& message) {
            onErrorOnStartGameMessage(connection, message);
        });
    getClient()->registerHandler<StartGameMessage>([this](const std::shared_ptr<KapMirror::NetworkConnectionToServer>& connection,
                                                          StartGameMessage& message) { onPlayerStartGameMessage(connection, message); });
    getClient()->registerHandler<PlayerPingRequest>([this](const std::shared_ptr<KapMirror::NetworkConnectionToServer>& connection,
                                                           PlayerPingRequest& message) { onClientPlayerPingRequest(connection, message); });
    getClient()->registerHandler<PlayerPingResult>([this](const std::shared_ptr<KapMirror::NetworkConnectionToServer>& connection,
                                                          PlayerPingResult& message) { onPlayerPingResult(connection, message); });
}

void RtypeNetworkManager::onClientConnected(const std::shared_ptr<KapMirror::NetworkConnection>& connection) {
    KapEngine::Debug::log("RtypeNetworkManager: Client connected");

    // TODO: Remove this (is for Test)
    StartGameMessage message;
    message.mapScriptPath = "Maps/TestMapServer.lua";
    connection->send(message);
}

void RtypeNetworkManager::onClientDisconnected(const std::shared_ptr<KapMirror::NetworkConnection>& connection) {
    KapEngine::Debug::log("RtypeNetworkManager: Disconnected from server");
}

void RtypeNetworkManager::onPlayerAuthorityMessage(const std::shared_ptr<KapMirror::NetworkConnectionToServer>& connection,
                                                   PlayerAuthorityMessage& message) {
    std::shared_ptr<KapEngine::GameObject> player;
    if (getClient()->getExistingObject(message.networkId, player)) {
        auto& playerController = player->getComponent<PlayerController>();
        playerController.setLocalAuthority(true);
    }
}

void RtypeNetworkManager::onErrorOnStartGameMessage(const std::shared_ptr<KapMirror::NetworkConnectionToServer>& connection,
                                                    ErrorOnStartGameMessage& message) {
    KAP_DEBUG_ERROR("onErrorOnStartGameMessage: Error on start game: " + message.errorMessage);
    // TODO: Handle error
}

void RtypeNetworkManager::onPlayerStartGameMessage(const std::shared_ptr<KapMirror::NetworkConnectionToServer>& connection,
                                                   StartGameMessage& message) {
    KAP_DEBUG_LOG("onPlayerStartGameMessage: Start game");
}

void RtypeNetworkManager::onClientPlayerPingRequest(const std::shared_ptr<KapMirror::NetworkConnectionToServer>& connection,
                                                    PlayerPingRequest& message) {
    // Ping-pong :)
    PlayerPingRequest reqCallback;

    reqCallback.id = message.id;
    connection->send(reqCallback);
}

void RtypeNetworkManager::onPlayerPingResult(const std::shared_ptr<KapMirror::NetworkConnectionToServer>& connection,
                                             PlayerPingResult& message) {
    std::shared_ptr<KapEngine::GameObject> player;

    try {
        auto obj = getScene().findFirstGameObject("NetStatViewer");
        auto& viewer = obj->getComponent<NetStatViewer>();

        viewer.setPing(message.ping);
    } catch (KapEngine::Errors::SceneError&) {}
}

#pragma endregion

#pragma region Server

void RtypeNetworkManager::registerServerHandlers() {
    getServer()->registerHandler<PlayerInputMessage>([this](const std::shared_ptr<KapMirror::NetworkConnectionToClient>& connection,
                                                            PlayerInputMessage& message) { onPlayerInputMessage(connection, message); });
    getServer()->registerHandler<PlayerPrepareShootMessage>(
        [this](const std::shared_ptr<KapMirror::NetworkConnectionToClient>& connection, PlayerPrepareShootMessage& message) {
            onPlayerPrepareShootMessage(connection, message);
        });
    getServer()->registerHandler<PlayerShootMessage>([this](const std::shared_ptr<KapMirror::NetworkConnectionToClient>& connection,
                                                            PlayerShootMessage& message) { onPlayerShootMessage(connection, message); });
    getServer()->registerHandler<StartGameMessage>([this](const std::shared_ptr<KapMirror::NetworkConnectionToClient>& connection,
                                                          StartGameMessage& message) { onStartGameMessage(connection, message); });
    getServer()->registerHandler<PlayerPingRequest>([this](const std::shared_ptr<KapMirror::NetworkConnectionToClient>& connection,
                                                           PlayerPingRequest& message) { onServerPlayerPingRequest(connection, message); });
}

void RtypeNetworkManager::onServerClientConnected(const std::shared_ptr<KapMirror::NetworkConnection>& connection) {
    KapEngine::Debug::log("Player[" + std::to_string(connection->getConnectionId()) + "] -> connected");

    std::shared_ptr<KapEngine::GameObject> player;
    getServer()->spawnObject(
        "Player", {0, 0, 0},
        [](const std::shared_ptr<KapEngine::GameObject>& go) {
            auto& networkIdentity = go->getComponent<KapMirror::NetworkIdentity>();
            auto& playerSkin = go->getComponent<PlayerSkin>();

            // Set Default Skin (Send later the player skin)
            playerSkin.setSkinId(2);
        },
        player);

    player->getComponent<PlayerController>().setConnectionId(connection->getConnectionId());
    players[connection->getConnectionId()] = player;

    auto& networkIdentity = player->getComponent<KapMirror::NetworkIdentity>();

    // Send player authority
    PlayerAuthorityMessage message;
    message.networkId = networkIdentity.getNetworkId();
    connection->send(message);
}

void RtypeNetworkManager::onServerClientDisconnected(const std::shared_ptr<KapMirror::NetworkConnection>& connection) {
    KAP_DEBUG_LOG("Player[" + std::to_string(connection->getConnectionId()) + "] -> disconnected");

    std::shared_ptr<KapEngine::GameObject> player;
    if (players.tryGetValue(connection->getConnectionId(), player)) {
        getServer()->destroyObject(player);
    }
    // Clear ping requests
    pingRequests.remove(connection->getConnectionId());
}

void RtypeNetworkManager::onPlayerInputMessage(const std::shared_ptr<KapMirror::NetworkConnectionToClient>& connection,
                                               PlayerInputMessage& message) {
    std::shared_ptr<KapEngine::GameObject> player;
    if (players.tryGetValue(connection->getConnectionId(), player)) {
        auto& controllerComponent = player->getComponent<RType::PlayerController>();
        controllerComponent.movePlayer(KapEngine::Tools::Vector2(message.x, message.y));
    }
}

void RtypeNetworkManager::onPlayerPrepareShootMessage(const std::shared_ptr<KapMirror::NetworkConnectionToClient>& connection,
                                                      PlayerPrepareShootMessage& message) {
    std::shared_ptr<KapEngine::GameObject> player;
    if (players.tryGetValue(connection->getConnectionId(), player)) {
        auto& controllerComponent = player->getComponent<RType::PlayerController>();
        controllerComponent.prepareShoot();
    }
}

void RtypeNetworkManager::onPlayerShootMessage(const std::shared_ptr<KapMirror::NetworkConnectionToClient>& connection,
                                               PlayerShootMessage& message) {
    std::shared_ptr<KapEngine::GameObject> player;
    if (players.tryGetValue(connection->getConnectionId(), player)) {
        auto& controllerComponent = player->getComponent<RType::PlayerController>();
        controllerComponent.shoot();
    }
}

void RtypeNetworkManager::onStartGameMessage(const std::shared_ptr<KapMirror::NetworkConnectionToClient>& connection,
                                             StartGameMessage& message) {
    if (isGameStarted) {
        KapEngine::Debug::error("Game already started");
        sendErrorOnStartGame(connection, "Game already started");
        return;
    }
    if (players.size() < 1) { // TODO: Change to 2
        KapEngine::Debug::error("Not enough players to start the game");
        sendErrorOnStartGame(connection, "Not enough players to start the game");
        return;
    }

    // Check if Map Script exists and is valid
    MapScript script(&getEngine(), true);
    try {
        script.loadScript(message.mapScriptPath);
    } catch (LuaException& e) {
        script.closeScript();
        KapEngine::Debug::error("Map script error: " + std::string(e.what()));
        sendErrorOnStartGame(connection, "Invalid Map Script");
        return;
    }

    if (script.isModded()) {
        script.closeScript();
        KapEngine::Debug::error("Map script is modded!");
        sendErrorOnStartGame(connection, "Server not supported modded Map Script");
        return;
    }

    script.closeScript();

    isGameStarted = true;

    StartGameMessage startGameMessage;
    startGameMessage.mapScriptPath = message.mapScriptPath;
    getServer()->sendToAll(startGameMessage);

    KapEngine::Debug::log("Start game with " + std::to_string(players.size()) + " players");
    startGame(message.mapScriptPath, true);
}

void RtypeNetworkManager::sendErrorOnStartGame(const std::shared_ptr<KapMirror::NetworkConnectionToClient>& connection,
                                               const std::string& errorMessage) {
    ErrorOnStartGameMessage message;
    message.errorMessage = errorMessage;

    connection->send(message);
}

void RtypeNetworkManager::onServerPlayerPingRequest(const std::shared_ptr<KapMirror::NetworkConnectionToClient>& connection,
                                                    PlayerPingRequest& message) {
    // Ping request dictionary doesn't contains connection id, so
    // we stop here.
    if (!pingRequests.containsKey(connection->getConnectionId())) {
        return;
    }
    auto& requests = pingRequests[connection->getConnectionId()];
    // Check if request ID is in request list
    if (!requests.containsKey(message.id)) {
        return;
    }

    long long time = requests[message.id];
    long long diff = std::chrono::high_resolution_clock::now().time_since_epoch().count() - time;
    // Delete request ID from the dictionary
    requests.remove(message.id);

    // Send result
    PlayerPingResult res;
    res.networkId = connection->getConnectionId();
    res.ping = diff / 1000000;
    connection->send(res);
}

void RtypeNetworkManager::startGame(const std::string& mapScriptPath, bool isSpawn) {
    KapEngine::Debug::log("Map script path: " + mapScriptPath);

    auto scene = getEngine().getSceneManager()->getCurrentScene();
    auto mapManager = scene.findFirstGameObject("MapManager");
    if (mapManager == nullptr) {
        KAP_DEBUG_ERROR("Failed to find MapManager");
        return;
    }

    auto& mapManagerComponent = mapManager->getComponent<MapManager>();
    mapManagerComponent.loadMapScript(mapScriptPath, true, isSpawn);
}

#pragma endregion
