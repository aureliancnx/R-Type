#pragma once

#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"
#include "Dictionary.hpp"
#include "Messages.hpp"

namespace RType {
    class RtypeNetworkManager : public KapMirror::NetworkManager {
        private:
        bool isServer = false;

        KapEngine::Dictionary<unsigned int, std::shared_ptr<KapEngine::GameObject>> players;

        public:
        RtypeNetworkManager(std::shared_ptr<KapEngine::GameObject> go, bool _isServer = false);
        ~RtypeNetworkManager() = default;

        void onStart() override;

        void onServerClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) override;

        void onServerClientDisconnected(std::shared_ptr<KapMirror::NetworkConnection> connection) override;

        private:
        void registerClientHandlers();

        void onPlayerAuthorityMessage(std::shared_ptr<KapMirror::NetworkConnectionToServer> connection, PlayerAuthorityMessage& message);

        void registerServerHandlers();

        void onPlayerInputMessage(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerInputMessage& message);

        void onPlayerShootMessage(std::shared_ptr<KapMirror::NetworkConnectionToClient> connection, PlayerShootMessage& message);
    };
}
