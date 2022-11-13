#pragma once

#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"
#include "MapScript.hpp"

namespace RType {
    class EnemyController : public KapMirror::NetworkComponent {
      private:
        MapScript *mapScript = nullptr;

        std::vector<std::shared_ptr<KapEngine::GameObject>> collidedObjects;

        std::string enemyName;
        int hp = 20;

      public:
        explicit EnemyController(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~EnemyController() = default;

        void setMapScript(MapScript *_mapScript);

        void setEnemyName(const std::string &_enemyName);

        void setHp(int _hp);

        void onFixedUpdate() override;

        void onTriggerEnter(std::shared_ptr<KapEngine::GameObject> other) override;

        void onSceneUpdated() override;
    };
} // namespace RType
