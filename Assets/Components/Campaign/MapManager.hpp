#pragma once

#include "KapEngine.hpp"
#include "MapScript/MapScript.hpp"

namespace RType {
    class MapManager : public KapEngine::Component {
      private:
        bool isLoaded = false;
        bool isSpawn = false;

        std::shared_ptr<MapScript> mapScript = nullptr;
        std::vector<SpawnEnemy> enemies;
        long long lastUpdate = 0;

      public:
        explicit MapManager(std::shared_ptr<KapEngine::GameObject> go);
        ~MapManager();

        void loadMapScript(const std::string &path, bool isServer, bool _isSpawn = true);

        void onFixedUpdate() override;
    };
} // namespace RType
