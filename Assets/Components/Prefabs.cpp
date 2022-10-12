#include "Prefabs.hpp"
#include "Player/PlayerController.hpp"
#include "Bullet/Bullet.hpp"

using namespace RType;

void Prefabs::registerPlayerPrefab(KapEngine::KEngine& engine) {
    engine.getPrefabManager()->createPrefab("Player", [](KapEngine::SceneManagement::Scene& scene) {
        auto player = KapEngine::UI::UiFactory::createCanvas(scene, "Player");

        auto networkIdentityComponent = std::make_shared<KapMirror::NetworkIdentity>(player);
        player->addComponent(networkIdentityComponent);

        auto networkTransformComponent = std::make_shared<KapMirror::NetworkTransform>(player);
        networkTransformComponent->setClientAuthority(false);
        networkTransformComponent->setSendRate(10);
        player->addComponent(networkTransformComponent);

        auto controllerComponent = std::make_shared<PlayerController>(player);
        player->addComponent(controllerComponent);
        controllerComponent->setLocalAuthoriy(false);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(player);
        imageComp->setRectangle({0, 0, 263, 116});
        imageComp->setPathSprite("Assets/Textures/Ship/ship_1.png");
        player->addComponent(imageComp);

        auto& transform = player->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({79, 35, 0});

        return player;
    });
}

void Prefabs::registerBulletPrefab(KapEngine::KEngine& engine) {
    engine.getPrefabManager()->createPrefab("Bullet", [](KapEngine::SceneManagement::Scene& scene) {
        auto bullet = KapEngine::UI::UiFactory::createCanvas(scene, "BulletCanvas");

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(bullet);
        bullet->addComponent(networkIdentityComp);

        auto bulletComp = std::make_shared<Bullet>(bullet);
        bullet->addComponent(bulletComp);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(bullet);
        imageComp->setRectangle({0, 0, 19, 6});
        imageComp->setPathSprite("Assets/Textures/Bullet/bullet_1.png");
        bullet->addComponent(imageComp);

        auto& transform = bullet->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({19, 6});

        return bullet;
    });
}
