#pragma once

#include "KapEngine.hpp"
#include "MapScript/EnemyController.hpp"

namespace RType {
    class BoubouleEnemy : public EnemyController {
      private:
        long long lastShootTime = 0;

      public:
        explicit BoubouleEnemy(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~BoubouleEnemy() = default;

        void onFixedUpdate() override;

      private:
        void shoot();
    };
} // namespace RType
