#include "GameManager.hpp"

#include "Menu/MainMenu.hpp"
#include "Menu/SoloMenu.hpp"
#include "Menu/MultiMenu.hpp"
#include "Menu/KeyboardMenu.hpp"

#include "KapMirror/KapMirror.hpp"
#include "Prefabs.hpp"

using namespace RType;

GameManager::GameManager(KapEngine::KEngine* _engine) : engine(_engine) {}

void GameManager::launchGame() {
    KapEngine::Debug::log("Launch game");

    Prefabs::registerPlayerPrefab(*engine);

    registerMenus();
    initSinglePlayer();
    //initSplashScreens();

    // Show main menu
    menuManager.showMenu("MainMenu");
}

void GameManager::launchServer() {
    KapEngine::Debug::log("Launch server");

    serverManager = std::make_shared<ServerManager>(engine);

    Prefabs::registerPlayerPrefab(*engine);

    initMultiPlayer();
    registerAxises();

    serverManager->start();
}

void GameManager::registerMenus() {
    KapEngine::Debug::log("Register menus");

    auto& scene = engine->getSceneManager()->getScene(1);

    // Register menus
    auto mainMenu = std::make_shared<MainMenu>(scene);
    menuManager.registerMenu("MainMenu", mainMenu);

    auto soloMenu = std::make_shared<SoloMenu>(scene);
    menuManager.registerMenu("SoloMenu", soloMenu);

    auto multiMenu = std::make_shared<MultiMenu>(scene, *this);
    menuManager.registerMenu("MultiMenu", multiMenu);

    auto keymenu = std::make_shared<KeyboardMenu>(scene);
    menuManager.registerMenu("KeysMenu", keymenu);
}

// TODO: Move this to a dedicated class
void GameManager::initSinglePlayer() {
    auto scene = engine->getSceneManager()->createScene("SinglePlayer");

    std::shared_ptr<KapEngine::GameObject> player;
    if (!engine->getPrefabManager()->instantiatePrefab("Player", *scene, player)) {
        KAP_DEBUG_ERROR("Failed to instantiate player prefab");
        return;
    }

    auto& transform = player->getComponent<KapEngine::Transform>();
    transform.setPosition({0, 0, 0});

    auto& playerComp = player->getComponent<Player>();
    playerComp.setLocalPlayer(true);

    // TODO: Fix animation (move animation)
    // https://github.com/aureliancnx/R-Type/blob/ae652adfdf49c702bd8513c27b8bef6dcfeaebc2/Assets/Components/GameManager.cpp#L84
}

// TODO: Move this to a dedicated class
void GameManager::initMultiPlayer() {
    auto scene = engine->getSceneManager()->createScene("MultiPlayer");

    auto networkManagerObject = scene->createGameObject("NetworkManager");
    networkManager = std::make_shared<RtypeNetworkManager>(networkManagerObject);
    networkManagerObject->addComponent(networkManager);
}

// TODO: Move this to a dedicated class
void GameManager::startLocalMultiPlayer() {
    auto& scene = engine->getSceneManager()->getScene("MultiPlayer");

    networkManager->startClient();
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
    engine->getEventManager().getInput().addAxis(_axisH);
    engine->getEventManager().getInput().addAxis(_axisV);
    engine->getEventManager().getInput().addAxis(_axisM);
}

void GameManager::initSplashScreens() {
    auto nsplash = std::make_shared<KapEngine::SceneManagement::SplashScreen::SplashScreenNode>("Assets/Textures/Background/bg-back.png", 4);

    nsplash->rect = {0.f, 0.f, 272.f, 160.f};
    nsplash->size = KapEngine::Tools::Vector2({650.f, 382.35f});
    nsplash->pos = KapEngine::Tools::Vector2({35.f, 48.825f});

    engine->getSplashScreen()->addSplashScreen(nsplash);
}
