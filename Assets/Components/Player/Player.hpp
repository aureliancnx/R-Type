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
        float speed;
        KapEngine::Tools::Vector3 posToMove;
        bool isMoving = false;

        public:
        Player(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~Player() = default;

        void setLocalPlayer(bool _isLocalPlayer);

        void onUpdate() override;
        void onFixedUpdate() override;

        void moveTo(KapEngine::Tools::Vector3 nPos, float speedByUnit = 1.0f);

        private:
        void shoot();
        float calculPosMoved(float unitToMove, float distanceToTravel);
    };
}
