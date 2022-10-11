#pragma once

#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"
#include "Dictionary.hpp"

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
    };
}
