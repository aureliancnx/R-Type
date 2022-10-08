#include "GameManager.hpp"

#include "Menu/MainMenu.hpp"
#include "Menu/SoloMenu.hpp"
#include "Menu/MultiMenu.hpp"

#include "KapMirror/KapMirror.hpp"

using namespace RType;

GameManager::GameManager(KapEngine::KapEngine& _engine) : engine(_engine) {}

void GameManager::launchGame() {
    KapEngine::Debug::log("Launch game");

    registerMenus();
    registerPrefabsPlayer();
    initSinglePlayer();
    initMultiPlayer();
    registerAxises();
    //initSplashScreens();

    // Show main menu
    menuManager.showMenu("MainMenu");
}

void GameManager::registerMenus() {
    KapEngine::Debug::log("Register menus");

    auto& scene = engine.getSceneManager()->getScene(1);

    // Register menus
    auto mainMenu = std::make_shared<MainMenu>(scene);
    menuManager.registerMenu("MainMenu", mainMenu);

    auto soloMenu = std::make_shared<SoloMenu>(scene);
    menuManager.registerMenu("SoloMenu", soloMenu);

    auto multiMenu = std::make_shared<MultiMenu>(scene);
    menuManager.registerMenu("MultiMenu", multiMenu);
}

void GameManager::registerPrefabsPlayer() {
    KapEngine::Debug::log("Register player prefabs");

    engine.getPrefabManager()->createPrefab("Player", [](KapEngine::SceneManagement::Scene& scene) {
        auto player = scene.createGameObject("Player");
        auto playerCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "PlayerCanvas");

        auto networkIdentityComp = std::make_shared<KapMirror::Experimental::NetworkIdentity>(player);
        player->addComponent(networkIdentityComp);

        auto networkTransformComp = std::make_shared<KapMirror::Experimental::NetworkTransform>(player);
        networkTransformComp->setClientAuthority(false);
        networkTransformComp->setSendRate(5);
        player->addComponent(networkTransformComp);

        auto playerComp = std::make_shared<Player>(player);
        player->addComponent(playerComp);

        auto imageComp = std::make_shared<KapEngine::UI::Image>(player);
        imageComp->setRectangle({0, 0, 26, 21});
        imageComp->setPathSprite("Assets/Textures/Ship/space_ship.png");
        player->addComponent(imageComp);

        auto& transform = player->getComponent<KapEngine::Transform>();
        transform.setPosition({0, 0, 0});
        transform.setScale({(26 * 2), (21 * 2)});
        transform.setParent(playerCanvas->getId());

        return player;
    });
}

void GameManager::initSinglePlayer() {
    auto scene = engine.getSceneManager()->createScene("SinglePlayer");

    std::shared_ptr<KapEngine::GameObject> player;
    if (!engine.getPrefabManager()->instantiatePrefab("Player", *scene, player)) {
        KAP_DEBUG_ERROR("Failed to instantiate player prefab");
        return;
    }

    auto& transform = player->getComponent<KapEngine::Transform>();
    transform.setPosition({0, 0, 0});

    auto& playerComp = player->getComponent<Player>();
    playerComp.setLocalPlayer(true);

    // TODO: Fix animation

    // // Create animation manager
    // auto animator = std::make_shared<KapEngine::Animator>(player);
    // player->addComponent(animator);

    // // Create new animation -> stay animation (IDLE)
    // auto stayAnimation = std::make_shared<SpriteAnimation>(player);
    // player->addComponent(stayAnimation);

    // // Create timer to set the duration of animation
    // KapEngine::Time::ETime duration;
    // duration.setSeconds(.1f);
    // stayAnimation->setTiming(duration);
    // stayAnimation->loop(true); // Loop but isn't a loop, loop with break point
    // stayAnimation->setRect({0, 0, 26, 21});
    // stayAnimation->setNbAnimations(1);

    // auto upAnimation = std::make_shared<SpriteAnimation>(player);
    // player->addComponent(stayAnimation);
    // upAnimation->setTiming(duration);
    // upAnimation->loop(true); // Loop but isn't a loop, loop with break point
    // upAnimation->setRect({(26 * 2), 0, 26, 21});
    // upAnimation->setNbAnimations(1);

    // auto downAnimation = std::make_shared<SpriteAnimation>(player);
    // player->addComponent(stayAnimation);
    // downAnimation->setTiming(duration);
    // downAnimation->loop(true); // Loop but isn't a loop, loop with break point
    // downAnimation->setRect({(26 * 1), 0, 26, 21});
    // downAnimation->setNbAnimations(1);

    // // Add animation with the unique name to animation manager - the first addAnim is the first animation
    // // Put Stay/IDLE at he first position /!\ importante
    // animator->addAnim(stayAnimation, "Stay");
    // animator->addAnim(upAnimation, "Up");
    // animator->addAnim(downAnimation, "Down");

    // // Add link to change animation with trigger (some action)
    // animator->addLink("Up", "Stay");
    // animator->addLink("Down", "Stay");
    // animator->addLink("Stay", "Up", "UP");
    // animator->addLink("Stay", "Down", "DOWN");
    // animator->addLink("Down", "Stay", "Idle");
    // animator->addLink("Up", "Stay", "Idle");
}

void GameManager::initMultiPlayer() {
    auto scene = engine.getSceneManager()->createScene("MultiPlayer");
}

void GameManager::registerAxises() {
    KapEngine::Events::Input::Axis _axisV("Vertical");
    KapEngine::Events::Input::Axis _axisH("Horizontal");
    KapEngine::Events::Input::Axis _axisM("Mouseinput");

    // init vertical axis
    _axisV.positiveButton = KapEngine::Events::Key::UP;
    _axisV.negativeButton = KapEngine::Events::Key::DOWN;
    _axisV.invert = true;

    // init horizontal axis
    _axisH.positiveButton = KapEngine::Events::Key::RIGHT;
    _axisH.negativeButton = KapEngine::Events::Key::LEFT;

    // init mouse axis
    _axisM.positiveButton = KapEngine::Events::Key::MOUSE_LEFT;
    _axisM.negativeButton = KapEngine::Events::Key::MOUSE_RIGHT;

    // add axis
    engine.getEventManager().getInput().addAxis(_axisH);
    engine.getEventManager().getInput().addAxis(_axisV);
    engine.getEventManager().getInput().addAxis(_axisM);
}

void GameManager::initSplashScreens() {
    auto nsplash = std::make_shared<KapEngine::SceneManagement::SplashScreen::SplashScreenNode>("Assets/Textures/Background/bg-back.png", 4);

    nsplash->rect = {0.f, 0.f, 272.f, 160.f};
    nsplash->size = KapEngine::Tools::Vector2({650.f, 382.35f});
    nsplash->pos = KapEngine::Tools::Vector2({35.f, 48.825f});

    engine.getSplashScreen()->addSplashScreen(nsplash);
}
