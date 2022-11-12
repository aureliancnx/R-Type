#pragma once

#include "KapEngine.hpp"
#include "MapScript/MapScript.hpp"

namespace RType {
    class MapManager : public KapEngine::Component {
      private:
        std::shared_ptr<MapScript> mapScript = nullptr;
        std::vector<SpawnEnemy> enemies;
        long long lastUpdate = 0;

      public:
        explicit MapManager(std::shared_ptr<KapEngine::GameObject> go);
        ~MapManager();

        void loadMapScript(const std::string& path, bool isServer = false);

        void onFixedUpdate() override;
    };
} // namespace RType
