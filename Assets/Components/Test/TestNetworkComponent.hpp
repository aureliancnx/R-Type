#pragma once

#include "KapMirror/KapMirror.hpp"

namespace RType {
namespace Component {
    class TestNetworkComponent : public KapMirror::Experimental::NetworkComponent {
        public:
            TestNetworkComponent(std::shared_ptr<KapEngine::GameObject> go);
            ~TestNetworkComponent() = default;

            void onStartServer() override;
    };
}
}
