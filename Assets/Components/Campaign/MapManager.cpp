#include "MapManager.hpp"
#include "KapEngineDebug.hpp"
#include "KapMirror/KapMirror.hpp"

using namespace RType;

MapManager::MapManager(std::shared_ptr<KapEngine::GameObject> go) : Component(go, "MapManager") {}

MapManager::~MapManager() {
    if (mapScript != nullptr) {
        mapScript->closeScript();
    }
    isLoaded = false;
}

void MapManager::loadMapScript(const std::string &path, bool isServer, bool _isSpawn) {
    isSpawn = _isSpawn;

    mapScript = std::make_shared<MapScript>(&getEngine(), isServer);
    mapScript->loadScript(path);

    isLoaded = true;

    KapEngine::Debug::log("MapScript loaded");
    KapEngine::Debug::log("Map Name: " + mapScript->getName());

    enemies = mapScript->getSpawnedEnemies();
    lastUpdate = KapMirror::NetworkTime::localTime();
}

void MapManager::onFixedUpdate() {
    if (!isSpawn || !isLoaded || enemies.empty()) {
        return;
    }

    long long time = KapMirror::NetworkTime::localTime();
    std::vector<int> toRemove;
    for (int i = 0; i < enemies.size(); i++) {
        const SpawnEnemy &enemy = enemies[i];
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
