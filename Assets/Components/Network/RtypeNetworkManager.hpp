#pragma once

#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"
#include "Dictionary.hpp"
#include "Messages.hpp"

namespace RType {
    class RtypeNetworkManager : public KapMirror::NetworkManager {
      private:
        bool isServer = false;

        bool isGameStarted = false;

        KapEngine::Dictionary<unsigned int, std::shared_ptr<KapEngine::GameObject>> players;

      public:
        KapEngine::Dictionary<unsigned int, KapEngine::Dictionary<unsigned int, long long>> pingRequests;

        explicit RtypeNetworkManager(std::shared_ptr<KapEngine::GameObject> go, bool _isServer = false);
        ~RtypeNetworkManager() = default;

        void onStart() override;

        void onClientConnected(const std::shared_ptr<KapMirror::NetworkConnection> &connection) override;

        void onClientDisconnected(const std::shared_ptr<KapMirror::NetworkConnection> &connection) override;

        void onServerClientConnected(const std::shared_ptr<KapMirror::NetworkConnection> &connection) override;

        void onServerClientDisconnected(const std::shared_ptr<KapMirror::NetworkConnection> &connection) override;

      private:
        void registerClientHandlers();

        void onPlayerAuthorityMessage(const std::shared_ptr<KapMirror::NetworkConnectionToServer> &connection,
                                      PlayerAuthorityMessage &message);

        void onErrorOnStartGameMessage(const std::shared_ptr<KapMirror::NetworkConnectionToServer> &connection,
                                       ErrorOnStartGameMessage &message);

        void onPlayerStartGameMessage(const std::shared_ptr<KapMirror::NetworkConnectionToServer> &connection, StartGameMessage &message);

        void onClientPlayerPingRequest(const std::shared_ptr<KapMirror::NetworkConnectionToServer> &connection, PlayerPingRequest &request);

        void onPlayerPingResult(const std::shared_ptr<KapMirror::NetworkConnectionToServer> &connection, PlayerPingResult &request);

        void registerServerHandlers();

        void onPlayerInputMessage(const std::shared_ptr<KapMirror::NetworkConnectionToClient> &connection, PlayerInputMessage &message);

        void onPlayerPrepareShootMessage(const std::shared_ptr<KapMirror::NetworkConnectionToClient> &connection,
                                         PlayerPrepareShootMessage &message);

        void onPlayerShootMessage(const std::shared_ptr<KapMirror::NetworkConnectionToClient> &connection, PlayerShootMessage &message);

        void onStartGameMessage(const std::shared_ptr<KapMirror::NetworkConnectionToClient> &connection, StartGameMessage &message);

        void sendErrorOnStartGame(const std::shared_ptr<KapMirror::NetworkConnectionToClient> &connection, const std::string &errorMessage);

        void onServerPlayerPingRequest(const std::shared_ptr<KapMirror::NetworkConnectionToClient> &connection, PlayerPingRequest &request);

        void startGame(const std::string &mapScriptPath, bool isSpawn);
    };
} // namespace RType
