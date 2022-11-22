#include "Prefabs.hpp"
#include "Collider.hpp"
#include "Player/PlayerController.hpp"
#include "Player/PlayerSkin.hpp"
#include "Bullet/Bullet.hpp"
#include "MapScript/DefaultEnemies/BoubouleEnemy.hpp"
#include "MapScript/DefaultEnemies/TentaclesBossEnemy.hpp"
#include "GameMenuManager.hpp"
#include "LobbyMenuManager.hpp"

using namespace RType;

void Prefabs::registerPlayerPrefab(KapEngine::KEngine &engine) {
    engine.getPrefabManager()->createPrefab("Player", [](KapEngine::SceneManagement::Scene &scene, const std::string &name) {
        auto player = KapEngine::UI::UiFactory::createCanvas(scene, "Player");
        player->setTag("Collider");

        auto networkIdentityComponent = std::make_shared<KapMirror::NetworkIdentity>(player);
        player->addComponent(networkIdentityComponent);

        auto networkTransformComponent = std::make_shared<KapMirror::NetworkTransform>(player);
        networkTransformComponent->setClientAuthority(false);
        networkTransformComponent->setSendRate(30);
        player->addComponent(networkTransformComponent);

        auto controllerComponent = std::make_shared<PlayerController>(player);
        player->addComponent(controllerComponent);
        controllerComponent->setLocalAuthority(false);

        auto skinComponent = std::make_shared<PlayerSkin>(player);
        player->addComponent(skinComponent);

        auto collider = std::make_shared<KapEngine::Collider>(player, true);
        player->addComponent(collider);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(player);
        imageComp->setRectangle({0, 0, 263, 116});
        imageComp->setPathSprite("Assets/Textures/Ship/ship_1.png"); // Default skin
        player->addComponent(imageComp);

        auto &canvas = player->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::ResizyngType::RESIZE_WITH_SCREEN);

        auto &transform = player->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({79, 35, 0});

        auto shipIdle = std::make_shared<SpriteAnimation>(player);
        player->addComponent(shipIdle);

        KapEngine::Time::ETime duration;
        duration.setSeconds(.1f);
        shipIdle->setTiming(duration);
        shipIdle->setRect({263 * 2, 0, 263, 116});
        shipIdle->setNbAnimations(1);

        auto shipUp = std::make_shared<SpriteAnimation>(player);
        player->addComponent(shipUp);

        shipUp->setTiming(duration);
        shipUp->setRect({263 * 4, 0, 263, 116});
        shipUp->setNbAnimations(1);

        auto shipDown = std::make_shared<SpriteAnimation>(player);
        player->addComponent(shipDown);

        shipDown->setTiming(duration);
        shipDown->setRect({263 * 0, 0, 263, 116});
        shipDown->setNbAnimations(1);

        auto animator = std::make_shared<KapEngine::Animator>(player);
        player->addComponent(animator);

        animator->addAnim(shipIdle, "Idle");
        animator->addAnim(shipUp, "Up");
        animator->addAnim(shipDown, "Down");

        animator->addLink("Idle", "Idle", "IdleToIdle");

        animator->addLink("Idle", "Up", "IdleToUp");
        animator->addLink("Up", "Idle", "UpToIdle");

        animator->addLink("Idle", "Down", "IdleToDown");
        animator->addLink("Down", "Idle", "DownToIdle");

        return player;
    });
}

#pragma region Bullets

void Prefabs::registerBulletPrefab(KapEngine::KEngine &engine) {
    engine.getPrefabManager()->createPrefab("Bullet", [](KapEngine::SceneManagement::Scene &scene, const std::string &name) {
        auto bullet = KapEngine::UI::UiFactory::createCanvas(scene, "Bullet");

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(bullet);
        bullet->addComponent(networkIdentityComp);

        auto networkTransformComponent = std::make_shared<KapMirror::NetworkTransform>(bullet);
        networkTransformComponent->setClientAuthority(false);
        networkTransformComponent->setActiveUpdate(false);
        networkTransformComponent->setActiveLateUpdate(true);
        bullet->addComponent(networkTransformComponent);

        auto bulletComp = std::make_shared<Bullet>(bullet);
        bulletComp->setDirection(Bullet::Direction::LEFT);
        bullet->addComponent(bulletComp);

        auto collider = std::make_shared<KapEngine::Collider>(bullet, true);
        bullet->addComponent(collider);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(bullet);
        imageComp->setRectangle({0, 0, 19, 6});
        imageComp->setPathSprite("Assets/Textures/Bullet/bullet_1.png"); // Default skin
        bullet->addComponent(imageComp);

        auto &canvas = bullet->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::ResizyngType::RESIZE_WITH_SCREEN);

        auto &transform = bullet->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({19, 6});

        return bullet;
    });
}

void Prefabs::registerMissilePrefab(KapEngine::KEngine &engine) {
    engine.getPrefabManager()->createPrefab("Missile", [](KapEngine::SceneManagement::Scene &scene, const std::string &name) {
        auto missile = KapEngine::UI::UiFactory::createCanvas(scene, "Missile");

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(missile);
        missile->addComponent(networkIdentityComp);

        auto networkTransformComponent = std::make_shared<KapMirror::NetworkTransform>(missile);
        networkTransformComponent->setClientAuthority(false);
        networkTransformComponent->setActiveUpdate(false);
        networkTransformComponent->setActiveLateUpdate(true);
        missile->addComponent(networkTransformComponent);

        auto missileComp = std::make_shared<Bullet>(missile);
        missileComp->setDirection(Bullet::Direction::LEFT);
        missile->addComponent(missileComp);

        auto collider = std::make_shared<KapEngine::Collider>(missile, true);
        missile->addComponent(collider);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(missile);
        imageComp->setRectangle({0, 31 * 7, 31, 31});
        imageComp->setPathSprite("Assets/Textures/Weapons/LoadingMissile.png"); // Default skin
        missile->addComponent(imageComp);

        auto &canvas = missile->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::ResizyngType::RESIZE_WITH_SCREEN);

        auto &transform = missile->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({25, 25});
        transform.setRotation({90, 0, 0});

        return missile;
    });
}

void Prefabs::registerMissileExplodePrefab(KapEngine::KEngine &engine) {
    engine.getPrefabManager()->createPrefab("MissileExplode", [](KapEngine::SceneManagement::Scene &scene, const std::string &name) {
        auto menu = KapEngine::UI::UiFactory::createCanvas(scene, "MissileExplode");
        auto img = KapEngine::UI::UiFactory::createImage(
            scene, "MissileExplodeImg",
            "Assets/Textures/Explosion/wills_pixel_explosions_sample/round_explosion/spritesheet/spritesheet.png", {0, 0, 100, 100});

        try {
            auto &tr = img->getComponent<KapEngine::Transform>();
            tr.setParent(menu->getId());
        } catch (...) {}

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(menu);
        menu->addComponent(networkIdentityComp);

        auto animator = std::make_shared<KapEngine::Animator>(menu);
        menu->addComponent(animator);

        {
            int nbAnimations = 16;
            float totalTimeAnim = 5.5f;
            KapEngine::Time::ETime timeAnim;
            timeAnim.setSeconds(totalTimeAnim / (float) nbAnimations);
            auto anim = std::make_shared<SpriteAnimation>(img);
            img->addComponent(anim);

            anim->setNbAnimations(71, 10, 8);
            anim->setRect({0, 0, 100, 100});
            anim->setTiming(timeAnim);
            animator->addAnim(anim, "Explosion");

            anim->getOnEnd().registerAction([menu]() { menu->destroy(); });
        }

        auto &tr = menu->getComponent<KapEngine::Transform>();
        tr.setScale({120.f, 120.f, 0.f});

        auto &canvas = menu->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::ResizyngType::RESIZE_WITH_SCREEN);

        return menu;
    });
}

void Prefabs::registerBulletExplodePrefab(KapEngine::KEngine &engine) {
    engine.getPrefabManager()->createPrefab("BulletExplode", [](KapEngine::SceneManagement::Scene &scene, const std::string &name) {
        auto menu = KapEngine::UI::UiFactory::createCanvas(scene, "MissileExplode");
        auto img = KapEngine::UI::UiFactory::createImage(
            scene, "MissileExplodeImg",
            "Assets/Textures/Explosion/wills_pixel_explosions_sample/vertical_explosion/spritesheet/spritesheet.png", {0, 0, 100, 100});

        try {
            auto &tr = img->getComponent<KapEngine::Transform>();
            tr.setParent(menu->getId());
        } catch (...) {}

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(menu);
        menu->addComponent(networkIdentityComp);

        auto animator = std::make_shared<KapEngine::Animator>(menu);
        menu->addComponent(animator);

        {
            int nbAnimations = 16;
            float totalTimeAnim = 6.5f;
            KapEngine::Time::ETime timeAnim;
            timeAnim.setSeconds(totalTimeAnim / (float) nbAnimations);
            auto anim = std::make_shared<SpriteAnimation>(img);
            img->addComponent(anim);

            anim->setNbAnimations(74, 10, 8);
            anim->setRect({0, 0, 100, 100});
            anim->setTiming(timeAnim);
            animator->addAnim(anim, "Explosion");

            anim->getOnEnd().registerAction([menu]() { menu->destroy(); });
        }

        auto &tr = menu->getComponent<KapEngine::Transform>();
        tr.setScale({70.f, 70.f, 0.f});

        auto &canvas = menu->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::ResizyngType::RESIZE_WITH_SCREEN);

        return menu;
    });
}

#pragma endregion

#pragma region IngameMenu

void Prefabs::registerInGameMenuPrefab(KapEngine::KEngine &engine) {
    engine.getPrefabManager()->createPrefab("InGameMenu", [](KapEngine::SceneManagement::Scene &scene, const std::string &name) {
        auto menu = KapEngine::UI::UiFactory::createCanvas(scene, "InGameMenu");

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(menu);
        menu->addComponent(networkIdentityComp);

        auto menuManager = std::make_shared<GameMenuManager>(menu);
        menu->addComponent(menuManager);

        auto lobbyManager = std::make_shared<LobbyMenuManager>(menu);
        menu->addComponent(lobbyManager);

        auto &canvas = menu->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::ResizyngType::RESIZE_WITH_SCREEN);

        return menu;
    });
}

#pragma endregion

#pragma region Enemies

void Prefabs::registerBoubouleEnemyPrefab(KapEngine::KEngine &engine) {
    engine.getPrefabManager()->createPrefab("Enemy:Bouboule", [](KapEngine::SceneManagement::Scene &scene, const std::string &name) {
        auto enemy = KapEngine::UI::UiFactory::createCanvas(scene, "BoubouleEnemy");
        enemy->setTag("Collider");

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(enemy);
        enemy->addComponent(networkIdentityComp);

        auto networkTransformComponent = std::make_shared<KapMirror::NetworkTransform>(enemy);
        networkTransformComponent->setClientAuthority(false);
        networkTransformComponent->setActiveUpdate(false);
        networkTransformComponent->setActiveLateUpdate(true);
        enemy->addComponent(networkTransformComponent);

        auto enemyComp = std::make_shared<BoubouleEnemy>(enemy);
        enemy->addComponent(enemyComp);

        auto collider = std::make_shared<KapEngine::Collider>(enemy, true);
        enemy->addComponent(collider);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(enemy);
        imageComp->setRectangle({0, 0, 17, 18});
        imageComp->setPathSprite("Assets/Textures/Enemy/enemy_1.png");
        enemy->addComponent(imageComp);

        auto &canvas = enemy->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::ResizyngType::RESIZE_WITH_SCREEN);

        auto &transform = enemy->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({17 * 3, 18 * 3, 0});

        auto bulletIdle = std::make_shared<SpriteAnimation>(enemy);
        enemy->addComponent(bulletIdle);

        KapEngine::Time::ETime duration;
        duration.setSeconds(0.5f);
        bulletIdle->setTiming(duration);
        bulletIdle->loop(true);
        bulletIdle->setRect({0, 0, 17, 18});
        bulletIdle->setNbAnimations(12);

        auto animator = std::make_shared<KapEngine::Animator>(enemy);
        enemy->addComponent(animator);
        animator->addAnim(bulletIdle, "Idle");
        animator->addLink("Idle", "Idle");
        return enemy;
    });
}

void Prefabs::registerTentaclesBossEnemyPrefab(KapEngine::KEngine &engine) {
    engine.getPrefabManager()->createPrefab("Enemy:TentacleBoss", [](KapEngine::SceneManagement::Scene &scene, const std::string &name) {
        auto enemy = KapEngine::UI::UiFactory::createCanvas(scene, "TentacleBoss");
        enemy->setTag("Collider");

        auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(enemy);
        enemy->addComponent(networkIdentityComp);

        auto networkTransformComponent = std::make_shared<KapMirror::NetworkTransform>(enemy);
        networkTransformComponent->setClientAuthority(false);
        networkTransformComponent->setActiveUpdate(false);
        networkTransformComponent->setActiveLateUpdate(true);
        enemy->addComponent(networkTransformComponent);

        auto enemyComp = std::make_shared<TentaclesBossEnemy>(enemy);
        enemy->addComponent(enemyComp);

        auto collider = std::make_shared<KapEngine::Collider>(enemy, true);
        enemy->addComponent(collider);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(enemy);
        imageComp->setRectangle({0, 0, 64, 66});
        imageComp->setPathSprite("Assets/Textures/Enemy/enemy_3.png");
        enemy->addComponent(imageComp);

        auto &canvas = enemy->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::ResizyngType::RESIZE_WITH_SCREEN);

        auto &transform = enemy->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({64 * 2, 66 * 2, 0});

        auto bulletIdle = std::make_shared<SpriteAnimation>(enemy);
        enemy->addComponent(bulletIdle);

        KapEngine::Time::ETime duration;
        duration.setSeconds(0.4f);
        bulletIdle->setTiming(duration);
        bulletIdle->loop(true);
        bulletIdle->setRect({0, 0, 65.5, 66});
        bulletIdle->setNbAnimations(12);
        bulletIdle->bouncingVersion(false);

        auto animator = std::make_shared<KapEngine::Animator>(enemy);
        enemy->addComponent(animator);
        animator->addAnim(bulletIdle, "Idle");
        animator->addLink("Idle", "Idle");
        return enemy;
    });
}

#pragma endregion

#pragma region Paralax

void Prefabs::registerGalaxyParalaxPrefab(KapEngine::KEngine &engine) {
    engine.getPrefabManager()->createPrefab("ParalaxGalaxy", [](KapEngine::SceneManagement::Scene &scene, const std::string &name) {
        auto paralax = scene.createGameObject("Paralax");
        auto paralaxCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "ParalaxCanvas");

        try {
            auto &tr = paralax->getComponent<KapEngine::Transform>();
            tr.setParent(paralaxCanvas);
        } catch (...) { KAP_DEBUG_ERROR("Failed to get Transform of parent"); }

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
    engine.getPrefabManager()->createPrefab("ParalaxStars", [](KapEngine::SceneManagement::Scene &scene, const std::string &name) {
        auto paralax = scene.createGameObject("Paralax");
        auto paralaxCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "ParalaxCanvas");

        try {
            auto &tr = paralax->getComponent<KapEngine::Transform>();
            tr.setParent(paralaxCanvas);
        } catch (...) { KAP_DEBUG_ERROR("Failed to get Transform of parent"); }

        auto stars1 = KapEngine::UI::UiFactory::createImage(scene, "stars1");
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

#pragma endregion
