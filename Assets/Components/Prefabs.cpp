#include "Prefabs.hpp"
#include "Player/Player.hpp"
#include "Bullet/Bullet.hpp"

using namespace RType;

void Prefabs::registerPlayerPrefab(KapEngine::KEngine& engine) {
    engine.getPrefabManager()->createPrefab("Player", [](KapEngine::SceneManagement::Scene& scene) {
        auto player = scene.createGameObject("Player");
        auto playerCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "PlayerCanvas");

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(player);
        player->addComponent(networkIdentityComp);

        auto networkTransformComp = std::make_shared<KapMirror::NetworkTransform>(player);
        networkTransformComp->setClientAuthority(false);
        networkTransformComp->setSendRate(5);
        player->addComponent(networkTransformComp);

        auto playerComp = std::make_shared<Player>(player);
        player->addComponent(playerComp);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(player);
        imageComp->setRectangle({0, 0, 263, 116});
        imageComp->setPathSprite("Assets/Textures/Ship/ship_1.png");
        player->addComponent(imageComp);

        auto& transform = player->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({48.9, 34.8, 0});
        transform.setParent(playerCanvas->getId());

        return player;
    });
}

void Prefabs::registerBulletPrefab(KapEngine::KEngine& engine) {
    engine.getPrefabManager()->createPrefab("Bullet", [](KapEngine::SceneManagement::Scene& scene) {
        auto bullet = scene.createGameObject("Bullet");
        auto bulletCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "BulletCanvas");

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(bullet);
        bullet->addComponent(networkIdentityComp);

        auto bulletComp = std::make_shared<Bullet>(bullet);
        bullet->addComponent(bulletComp);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(bullet);
        imageComp->setRectangle({0, 0, 26, 21});
        imageComp->setPathSprite("Assets/Textures/Bullet/bullet_1.png");
        bullet->addComponent(imageComp);

        auto& transform = bullet->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({(26 * 2), (21 * 2)});
        transform.setParent(bulletCanvas->getId());

        return bullet;
    });
}
