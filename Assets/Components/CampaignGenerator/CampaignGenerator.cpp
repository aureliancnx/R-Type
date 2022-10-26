//
// Created by leq on 25/10/22.
//

#include "CampaignGenerator.hpp"


using namespace KapEngine;

RType::CampaignGenerator::CampaignGenerator(std::shared_ptr<GameObject> go) : Component(go, "Campaign Generator") {}

RType::CampaignGenerator::~CampaignGenerator() {}

void RType::CampaignGenerator::addEnemy(const RType::CampaignGenerator::Enemy &enemy) {
    _enemies.push_back(enemy);
}

void RType::CampaignGenerator::onAwake() {
    addEnemy(Enemy("Enemy:BoubouleEnemy"));
    addEnemy(Enemy("Enemy:BoubouleEnemy", 200, 20));
    addEnemy(Enemy("Enemy:BoubouleEnemy", 300, 30));
    addEnemy(Enemy("Enemy:BoubouleEnemy", 400, 40));
    _clock.restart();
    _time.setSeconds(0);
}

void RType::CampaignGenerator::onFixedUpdate() {
    auto &scene = getGameObjectConst().getScene();

    KapEngine::Time::ETime tmp = _clock.getElapseTime();

    for (std::size_t i = 0; i < _enemies.size(); i++) {
        if (_time.asSecond() < _enemies[i]._time && _enemies[i]._time <= tmp.asSecond()) {
            auto enemy = spawnMob(_enemies[i]._mobName, scene);
            auto &trEnemy = enemy->getComponent<KapEngine::Transform>();

            trEnemy.setPosition({1280, static_cast<float>(_enemies[i]._positionY), 0});
            _enemies.erase(_enemies.begin() + i);
            i--;
        }
    }
    _time = tmp;
}

std::shared_ptr<KapEngine::GameObject> RType::CampaignGenerator::spawnMob(const std::string &mobName, KapEngine::SceneManagement::Scene &scene) {
    std::shared_ptr<KapEngine::GameObject> mob;
    scene.getEngine().getPrefabManager()->instantiatePrefab(mobName, scene, mob);
    return mob;
}