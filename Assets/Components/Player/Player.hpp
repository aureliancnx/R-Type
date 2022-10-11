#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
    class Player : public KapMirror::NetworkComponent {
        private:
        bool isLocalPlayer = false;
        KapEngine::Tools::Vector3 lastPos;

        public:
        Player(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~Player() = default;

        void setLocalPlayer(bool _isLocalPlayer);

        void onUpdate() override;
    };
}
