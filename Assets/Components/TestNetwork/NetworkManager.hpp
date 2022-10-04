#pragma once

#include "KapEngine.hpp"
#include "Factory.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
namespace Component {
    class TestNetworkManager : public KapMirror::NetworkManager {
        bool isServer;

        std::shared_ptr<KapEngine::GameObject> ball;

        public:
            TestNetworkManager(std::shared_ptr<KapEngine::GameObject> go, bool _isServer = false);
            ~TestNetworkManager() = default;

            void onStart() override;
            void onUpdate() override;

            void onServerClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) override;
    };
}
}
