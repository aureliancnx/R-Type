#include "Prefabs.hpp"
#include "Collider.hpp"
#include "Player/PlayerController.hpp"
#include "Player/PlayerSkin.hpp"
#include "Bullet/Bullet.hpp"
#include "Enemies/BasicEnemy.hpp"

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
        controllerComponent->setLocalAuthority(false);

        auto skinComponent = std::make_shared<PlayerSkin>(player);
        player->addComponent(skinComponent);

        auto collider = std::make_shared<KapEngine::Collider>(player, true, false, true);
        player->addComponent(collider);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(player);
        imageComp->setRectangle({0, 0, 263, 116});
        imageComp->setPathSprite("Assets/Textures/Ship/ship_1.png"); // Default skin
        player->addComponent(imageComp);

        auto& canvas = player->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::resizyngType::RESIZE_WITH_SCREEN);

        auto& transform = player->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({79, 35, 0});

        return player;
    });
}

void Prefabs::registerBulletPrefab(KapEngine::KEngine& engine) {
    engine.getPrefabManager()->createPrefab("Bullet", [](KapEngine::SceneManagement::Scene& scene) {
        auto bullet = KapEngine::UI::UiFactory::createCanvas(scene, "Bullet");

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(bullet);
        bullet->addComponent(networkIdentityComp);

        auto bulletComp = std::make_shared<Bullet>(bullet);
        bullet->addComponent(bulletComp);

        auto collider = std::make_shared<KapEngine::Collider>(bullet);
        bullet->addComponent(collider);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(bullet);
        imageComp->setRectangle({0, 0, 19, 6});
        imageComp->setPathSprite("Assets/Textures/Bullet/bullet_1.png"); // Default skin
        bullet->addComponent(imageComp);

        auto& canvas = bullet->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::resizyngType::RESIZE_WITH_SCREEN);

        auto& transform = bullet->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({19, 6});

        return bullet;
    });
}

void Prefabs::registerBasicEnemyPrefab(KapEngine::KEngine& engine) {
    engine.getPrefabManager()->createPrefab("BasicEnemy", [](KapEngine::SceneManagement::Scene& scene) {
        auto enemy = KapEngine::UI::UiFactory::createCanvas(scene, "BasicEnemy");

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(enemy);
        enemy->addComponent(networkIdentityComp);

        auto enemyComp = std::make_shared<BasicEnemy>(enemy);
        enemy->addComponent(enemyComp);

        auto collider = std::make_shared<KapEngine::Collider>(enemy, true, false, true);
        enemy->addComponent(collider);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(enemy);
        imageComp->setRectangle({0, 0, 263, 116});
        imageComp->setPathSprite("Assets/Textures/Ship/ship_1.png"); // Default skin
        enemy->addComponent(imageComp);

        auto& canvas = enemy->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::resizyngType::RESIZE_WITH_SCREEN);

        auto& transform = enemy->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({79, 35, 0});

        return enemy;
    });
}
