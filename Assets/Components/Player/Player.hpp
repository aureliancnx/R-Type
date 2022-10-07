#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
    class Player : public KapMirror::Experimental::NetworkComponent {
        public:
        Player(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~Player() = default;
    };
}
