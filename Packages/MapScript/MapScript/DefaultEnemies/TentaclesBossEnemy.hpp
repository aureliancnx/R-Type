#pragma once

#include "KapEngine.hpp"
#include "MapScript/EnemyController.hpp"

namespace RType {
    class TentaclesBossEnemy : public EnemyController {
      private:
        long long lastShootTime = 0;
        bool invert = false;

      public:
        explicit TentaclesBossEnemy(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~TentaclesBossEnemy() = default;

        void onFixedUpdate() override;

      private:
        void shoot();
    };
} // namespace RType
