#include "Prefabs.hpp"
#include "Collider.hpp"
#include "Player/PlayerController.hpp"
#include "Player/PlayerSkin.hpp"
#include "Bullet/Bullet.hpp"
#include "Enemies/ShipEnemy.hpp"
#include "Enemies/BoubouleEnemy.hpp"

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

#pragma region Enemies

void Prefabs::registerShipEnemyPrefab(KapEngine::KEngine& engine) {
    engine.getPrefabManager()->createPrefab("Enemy:ShipEnemy", [](KapEngine::SceneManagement::Scene& scene) {
        auto enemy = KapEngine::UI::UiFactory::createCanvas(scene, "ShipEnemy");

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(enemy);
        enemy->addComponent(networkIdentityComp);

        auto enemyComp = std::make_shared<ShipEnemy>(enemy);
        enemy->addComponent(enemyComp);

        auto collider = std::make_shared<KapEngine::Collider>(enemy, true, false, true);
        enemy->addComponent(collider);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(enemy);
        imageComp->setRectangle({0, 0, 263, 116});
        imageComp->setPathSprite("Assets/Textures/Enemy/enemy_4.png");
        enemy->addComponent(imageComp);

        auto& canvas = enemy->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::resizyngType::RESIZE_WITH_SCREEN);

        auto& transform = enemy->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({79, 35, 0});

        return enemy;
    });
}

void Prefabs::registerGalaxyParalaxPrefab(KapEngine::KEngine& engine) {
    engine.getPrefabManager()->createPrefab("ParalaxGalaxy", [](KapEngine::SceneManagement::Scene& scene) {
        auto paralax = scene.createGameObject("Paralax");
        auto paralaxCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "ParalaxCanvas");

        try {
            auto &tr = paralax->getComponent<KapEngine::Transform>();
            tr.setParent(paralaxCanvas);
        } catch(...) {
            KAP_DEBUG_ERROR("Failed to get Transform of parent");
        }

        auto galaxy1 = KapEngine::UI::UiFactory::createImage(scene, "galaxy1");
        auto galaxy2 = KapEngine::UI::UiFactory::createImage(scene, "galaxy2");

        auto &canvas = paralaxCanvas->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
        canvas.setScreenCompare({272, 160});

        try {
            auto &img = galaxy1->getComponent<KapEngine::UI::Image>();
            img.setRectangle({0, 0, 272, 160});
            img.setPathSprite("Assets/Textures/Background/bg-back.png");

            auto &transform = galaxy1->getComponent<KapEngine::Transform>();
            transform.setParent(paralax);
            transform.setScale({271, 160, 0});
        } catch (...) {}

        try {
            auto &img = galaxy2->getComponent<KapEngine::UI::Image>();
            img.setRectangle({0, 0, 272, 160});
            img.setPathSprite("Assets/Textures/Background/bg-back.png");

            auto &transform = galaxy2->getComponent<KapEngine::Transform>();
            transform.setParent(paralax);
            transform.setScale({271, 160, 0});
            transform.setPosition({271 * 1, 0, 0});
        } catch (...) {}

        // Animation
        auto paralaxAnimation = std::make_shared<RType::ParalaxAnimation>(paralaxCanvas, .05, 272);
        paralax->addComponent(paralaxAnimation);

        auto animator = std::make_shared<KapEngine::Animator>(paralax);
        paralax->addComponent(animator);
        animator->addAnim(paralaxAnimation, "idle");
        animator->addLink("idle", "idle");

        return paralax;
    });
}

void Prefabs::registerStarsParalaxPrefab(KapEngine::KEngine &engine) {
    engine.getPrefabManager()->createPrefab("ParalaxStars", [](KapEngine::SceneManagement::Scene& scene) {
        auto paralax = scene.createGameObject("Paralax");
        auto paralaxCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "ParalaxCanvas");

        try {
            auto &tr = paralax->getComponent<KapEngine::Transform>();
            tr.setParent(paralaxCanvas);
        } catch(...) {
            KAP_DEBUG_ERROR("Failed to get Transform of parent");
        }

        auto  stars1 = KapEngine::UI::UiFactory::createImage(scene, "stars1");
        auto stars2 = KapEngine::UI::UiFactory::createImage(scene, "stars2");

        auto &canvas = paralaxCanvas->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
        canvas.setScreenCompare({272, 160});

        try {
            auto &img = stars1->getComponent<KapEngine::UI::Image>();
            img.setRectangle({0, 0, 272, 160});
            img.setPathSprite("Assets/Textures/Background/bg-stars.png");

            auto &transform = stars1->getComponent<KapEngine::Transform>();
            transform.setParent(paralax);
            transform.setScale({271, 160, 0});
        } catch (...) {}

        try {
            auto &img = stars2->getComponent<KapEngine::UI::Image>();
            img.setRectangle({0, 0, 272, 160});
            img.setPathSprite("Assets/Textures/Background/bg-stars.png");

            auto &transform = stars2->getComponent<KapEngine::Transform>();
            transform.setParent(paralax);
            transform.setScale({271, 160, 0});
            transform.setPosition({271 * 1, 0, 0});
        } catch (...) {}

        // Animation
        auto paralaxAnimation = std::make_shared<RType::ParalaxAnimation>(paralaxCanvas, .5, 272);
        paralax->addComponent(paralaxAnimation);

        auto animator = std::make_shared<KapEngine::Animator>(paralax);
        paralax->addComponent(animator);
        animator->addAnim(paralaxAnimation, "idle");
        animator->addLink("idle", "idle");

        return paralax;
    });
}

void Prefabs::registerBoubouleEnemyPrefab(KapEngine::KEngine& engine) {
    engine.getPrefabManager()->createPrefab("Enemy:BoubouleEnemy", [](KapEngine::SceneManagement::Scene& scene) {
        auto enemy = KapEngine::UI::UiFactory::createCanvas(scene, "BoubouleEnemy");

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(enemy);
        enemy->addComponent(networkIdentityComp);

        auto enemyComp = std::make_shared<BoubouleEnemy>(enemy);
        enemy->addComponent(enemyComp);

        auto collider = std::make_shared<KapEngine::Collider>(enemy, true, false, true);
        enemy->addComponent(collider);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(enemy);
        imageComp->setRectangle({0, 0, 17, 18});
        imageComp->setPathSprite("Assets/Textures/Enemy/enemy_1.png");
        enemy->addComponent(imageComp);

        auto& canvas = enemy->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::resizyngType::RESIZE_WITH_SCREEN);

        auto& transform = enemy->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({17 * 3, 18 * 3, 0});

        return enemy;
    });
}

#pragma endregion