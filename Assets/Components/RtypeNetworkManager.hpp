#pragma once

#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
    class RtypeNetworkManager : public KapMirror::NetworkManager {
        bool isServer;

        public:
        RtypeNetworkManager(std::shared_ptr<KapEngine::GameObject> go, bool _isServer = false);
        ~RtypeNetworkManager() = default;

        void onServerClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) override;
    };
}
