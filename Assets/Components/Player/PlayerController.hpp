#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapMirror/KapMirror.hpp"

#include "GameMenuManager.hpp"

namespace RType {
    class PlayerController : public KapMirror::NetworkComponent {
      private:
        bool isLocalAuthority = false;

        KapEngine::Tools::Vector3 lastPos;
        KapEngine::Tools::Vector3 posToMove;
        KapEngine::Tools::Vector2 inputToMove;
        bool isMoving = false;

        long long lastRefreshTime = 0;

        std::shared_ptr<GameMenuManager> menuManager;
        KapEngine::Time::EClock clockMissile;

        KapEngine::Events::Key::EKey upKey = KapEngine::Events::Key::UP;
        KapEngine::Events::Key::EKey downKey = KapEngine::Events::Key::DOWN;
        KapEngine::Events::Key::EKey leftKey = KapEngine::Events::Key::LEFT;
        KapEngine::Events::Key::EKey rightKey = KapEngine::Events::Key::RIGHT;
        KapEngine::Events::Key::EKey shootKey = KapEngine::Events::Key::SPACE;

        int life = 100;
        bool isDead = false;

      public:
        explicit PlayerController(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~PlayerController() = default;

        void setLocalAuthority(bool _isLocalAuthority);

        void onUpdate() override;

        void onStart() override;

        void onFixedUpdate() override;

        void onStartClient() override;

        void movePlayer(const KapEngine::Tools::Vector2& input);

        void shoot();

        void prepareShoot();

        void spawnBullet(const KapEngine::Tools::Vector3& pos);

        void spawnMissile(const KapEngine::Tools::Vector3& pos);

        int getLife() const;

        bool dead() const;

        void takeDamage(int damage);

        void serialize(KapMirror::NetworkWriter& writer) override;

        void deserialize(KapMirror::NetworkReader& reader) override;

      private:
        void sendInput(const KapEngine::Tools::Vector2& input);

        void sendKeepAlive();

        void playShootSound();

        void initSettings();
    };
} // namespace RType
