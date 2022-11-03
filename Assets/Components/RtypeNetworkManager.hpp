#pragma once

#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"
#include "Dictionary.hpp"
#include "Messages.hpp"

namespace RType
{
    class RtypeNetworkManager : public KapMirror::NetworkManager
    {
      private:
        bool isServer = false;

        bool isGameStarted = false;

        KapEngine::Dictionary<unsigned int, std::shared_ptr<KapEngine::GameObject>> players;
        KapEngine::Dictionary<unsigned int, std::vector<long long>> keepAlives;

      public:
        RtypeNetworkManager(std::shared_ptr<KapEngine::GameObject> go, bool _isServer = false);
        ~RtypeNetworkManager() = default;

        void onStart() override;

        void onServerClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) override;

        void onServerClientDisconnected(std::shared_ptr<KapMirror::NetworkConnection> connection) override;

        void sendKeepAlive(KapMirror::NetworkIdentity *identity);

      private:
        void registerClientHandlers();

        void onPlayerAuthorityMessage(std::shared_ptr<KapMirror::NetworkConnectionToServer> connection, PlayerAuthorityMessage &message);

        void onServerSendKeepAlive(std::shared_ptr<KapMirror::NetworkConnectionToServer> connection, PlayerKeepAliveMessage &message);

        void onErrorOnStartGameMessage(std::shared_ptr<KapMirror::NetworkConnectionToServer> connection, ErrorOnStartGameMessage &message);

        void registerServerHandlers();

        void onClientSendKeepAlive(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerKeepAliveMessage &message);

        void onPlayerInputMessage(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerInputMessage &message);

        void onPlayerShootMessage(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerShootMessage &message);

        void onStartGameMessage(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, StartGameMessage &message);

        void sendErrorOnStartGame(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, const std::string &errorMessage);

        void startGame();
    };
} // namespace RType
