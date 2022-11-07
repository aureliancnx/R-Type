#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
    class BoubouleEnemy : public KapMirror::NetworkComponent {
      private:
        int life = 20;

        long long lastShootTime = 0;

        std::vector<std::shared_ptr<KapEngine::GameObject>> collidedObjects;

      public:
        explicit BoubouleEnemy(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~BoubouleEnemy() = default;

        void setLife(int _life);

        void onSceneUpdated() override;

        void onFixedUpdate() override;

        void onTriggerEnter(std::shared_ptr<KapEngine::GameObject> other) override;

        void serialize(KapMirror::NetworkWriter& writer) override;

        void deserialize(KapMirror::NetworkReader& reader) override;

      private:
        void shoot();
    };
} // namespace RType
