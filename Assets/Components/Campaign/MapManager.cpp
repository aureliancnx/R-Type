#include "MapManager.hpp"
#include "KapEngineDebug.hpp"
#include "KapMirror/KapMirror.hpp"

using namespace RType;

MapManager::MapManager(std::shared_ptr<KapEngine::GameObject> go) : Component(go, "MapManager") {}

MapManager::~MapManager() {
    if (mapScript != nullptr) {
        mapScript->closeScript();
    }
}

void RType::MapManager::onAwake() {
    if (!KapEngine::PlayerPrefs::hasKey("CampaignPath")) {
        KapEngine::Debug::error("No MapScript path found");
        return;
    }

    std::string path = KapEngine::PlayerPrefs::getString("CampaignPath");

    mapScript = std::make_shared<MapScript>(&getEngine());
    mapScript->loadScript(path);
    enemies = mapScript->getSpawnedEnemies();

    lastUpdate = KapMirror::NetworkTime::localTime();
}

void RType::MapManager::onFixedUpdate() {
    long long time = KapMirror::NetworkTime::localTime();

    if (enemies.empty()) {
        return;
    }

    std::vector<int> toRemove;
    for (int i = 0; i < enemies.size(); i++) {
        const SpawnEnemy& enemy = enemies[i];
        long long seconds = (time - lastUpdate) / 1000;
        if (seconds >= enemy.spawnTime) {
            mapScript->spawnEnemy(getScene(), enemy.name, enemy.startPositionY, enemy.startPositionX, enemy.enemyHp);
            toRemove.push_back(i);
        }
    }

    for (int i = (int) toRemove.size() - 1; i >= 0; i--) {
        enemies.erase(enemies.begin() + toRemove[i]);
    }
}

void RType::MapManager::onSceneChanged() {}
