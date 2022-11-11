/*
** EPITECH PROJECT, 2022
** RType
** File description:
** CampaignManager
*/

#include "CampaignManager.hpp"
#include "KapEngineDebug.hpp"

using namespace KapEngine;

RType::CampaignManager::CampaignManager(std::shared_ptr<GameObject> go) : Component(go, "CampaignManager"), _scene(go->getScene()) {}

RType::CampaignManager::~CampaignManager() {}

void RType::CampaignManager::onAwake() {
    std::string path = "";
    if (PlayerPrefs::hasKey("CampaignPath")) {
        path = PlayerPrefs::getString("CampaignPath");
    }
    if (path == "") {
        DEBUG_ERROR("No campaign path found");
        getGameObject().getEngine().getSceneManager()->loadScene(1);
        return;
    }
    _mapScript = std::make_shared<MapScript>(&getGameObject().getEngine());
    _mapScript->loadScript(path);
    _enemies = _mapScript->getSpawnedEnemies();
    _clock.restart();
    _lastElapsed.setSeconds(0);
}

void RType::CampaignManager::onFixedUpdate() {
    // if (_enemies.empty()) {
    //     KAP_DEBUG_LOG("No more enemies");
    //     getGameObject().getEngine().getSceneManager()->loadScene(1);
    //     return;
    // }
    auto time = _clock.getElapseTime();

    for (std::size_t i = 0; i < _enemies.size(); i++) {
        SpawnEnemy enemy = _enemies[i];
        if (time.asSecond() <= enemy.spawnTime) {
            DEBUG_LOG("Enemy: " + enemy.name + " time spawn:" + std::to_string(enemy.spawnTime) + " curr time: " + std::to_string(time.asSecond()));
            _mapScript->spawnEnemy(_scene, enemy.name, enemy.startPositionY, enemy.startPositionX, enemy.enemyHp);
            _enemies.erase(_enemies.begin() + i);
            i--;
        }
    }

    _lastElapsed = time;
}

void RType::CampaignManager::onSceneChanged() {
    if (_mapScript.use_count() == 0) {
        KAP_DEBUG_ERROR("MapScript is null when scene changed");
        return;
    }
    _mapScript->closeScript();
}
