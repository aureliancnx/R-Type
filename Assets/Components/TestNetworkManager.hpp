#pragma once

#include "KapMirror/NetworkManager.hpp"

namespace RType {
namespace Component {
    class TestNetworkManager : public KapMirror::NetworkManager {
        bool isServer;

        public:
            TestNetworkManager(std::shared_ptr<KapEngine::GameObject> go, bool _isServer = false);
            ~TestNetworkManager() = default;

            void onStart() override;
            void onUpdate() override;

            // Events
            void onStartServer() override;
            void onStopServer() override;
            void onServerClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) override;
            void onServerClientDisconnected(std::shared_ptr<KapMirror::NetworkConnection> connection) override;

            void onStartClient() override;
            void onStopClient() override;
            void onClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) override;
            void onClientDisconnected(std::shared_ptr<KapMirror::NetworkConnection> connection) override;
    };
}
}
