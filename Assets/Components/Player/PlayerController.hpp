#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapMirror/KapMirror.hpp"

#include "GameMenuManager.hpp"

namespace RType
{
    class PlayerController : public KapMirror::NetworkComponent
    {
      private:
        bool isLocalAuthority = false;

        KapEngine::Tools::Vector3 lastPos;
        KapEngine::Tools::Vector3 posToMove;
        KapEngine::Tools::Vector2 inputToMove;
        bool isMoving = false;

        long long lastRefreshTime = 0;
        long long lastKeepAliveTime = 0;

        std::shared_ptr<GameMenuManager> menuManager;
        KapEngine::Time::EClock clockMissile;
        bool shootMissile = false;

        KapEngine::Events::Key::EKey upKey = KapEngine::Events::Key::UP;
        KapEngine::Events::Key::EKey downKey = KapEngine::Events::Key::DOWN;
        KapEngine::Events::Key::EKey leftKey = KapEngine::Events::Key::LEFT;
        KapEngine::Events::Key::EKey rightKey = KapEngine::Events::Key::RIGHT;
        KapEngine::Events::Key::EKey shootKey = KapEngine::Events::Key::SPACE;

      public:
        PlayerController(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~PlayerController() = default;

        void setLocalAuthority(bool _isLocalAuthority);

        void onUpdate() override;

        void onStart() override;

        void onFixedUpdate() override;

        void onStartClient() override;

        void movePlayer(KapEngine::Tools::Vector2 input);

        void shoot();

      private:
        void sendInput(KapEngine::Tools::Vector2 input);

        void sendKeepAlive();

        void playShootSound();

        void initSettings();
    };
} // namespace RType
