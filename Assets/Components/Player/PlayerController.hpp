#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
    class PlayerController : public KapMirror::NetworkComponent {
        private:
        bool isLocalAuthoriy = false;

        KapEngine::Tools::Vector3 lastPos;
        KapEngine::Tools::Vector3 posToMove;
        KapEngine::Tools::Vector2 inputToMove;
        bool isMoving = false;

        long long lastRefreshTime = 0;

        public:
        PlayerController(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~PlayerController() = default;

        void setLocalAuthoriy(bool _isLocalAuthoriy);

        void onUpdate() override;

        void onFixedUpdate() override;

        void movePlayer(KapEngine::Tools::Vector2 input);

        void shoot();

        private:
        void sendInput(KapEngine::Tools::Vector2 input);
    };
}
