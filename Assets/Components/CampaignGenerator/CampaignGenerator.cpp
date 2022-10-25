//
// Created by leq on 25/10/22.
//

#include "CampaignGenerator.hpp"


using namespace KapEngine;

RType::CampaignGenerator::CampaignGenerator(std::shared_ptr<GameObject> go) : Component(go, "Campaign Generator") {}

RType::CampaignGenerator::~CampaignGenerator() {}

void RType::CampaignGenerator::onAwake() {
    Id = 0;
    delay = 0;
    positionYEnemy.push_back(100);
    positionYEnemy.push_back(200);
    positionYEnemy.push_back(300);
    positionYEnemy.push_back(400);
    positionYEnemy.push_back(500);
    positionYEnemy.push_back(600);
}

void RType::CampaignGenerator::onFixedUpdate() {
    auto &scene = getGameObjectConst().getScene();


    if (delay == 100) {
        auto enemy = spawnMob("Enemy:BoubouleEnemy", scene);
        auto &trEnemy = enemy->getComponent<KapEngine::Transform>();

        trEnemy.setPosition({1280, static_cast<float>(positionYEnemy[Id]), 0});

        if (Id > 5)
            Id = 0;
        else
            Id++;
        delay = -1;
    }
    delay++;
}

std::shared_ptr<KapEngine::GameObject> RType::CampaignGenerator::spawnMob(const std::string &mobName, KapEngine::SceneManagement::Scene &scene) {
    std::shared_ptr<KapEngine::GameObject> mob;
    scene.getEngine().getPrefabManager()->instantiatePrefab(mobName, scene, mob);
    return mob;
}