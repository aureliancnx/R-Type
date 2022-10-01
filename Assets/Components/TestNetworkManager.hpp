#pragma once

#include "KapMirror/NetworkManager.hpp"

namespace RType {
namespace Component {
    class TestNetworkManager : public KapMirror::NetworkManager {
        bool isServer;

        public:
            TestNetworkManager(std::shared_ptr<KapEngine::GameObject> &go, std::shared_ptr<KapMirror::Compression> &compression, bool _isServer = false);
            ~TestNetworkManager() = default;

            void onStart() override;
    };
}
}
