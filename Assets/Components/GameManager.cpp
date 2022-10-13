#include "GameManager.hpp"

#include "Menu/MainMenu.hpp"
#include "Menu/SoloMenu.hpp"
#include "Menu/MultiMenu.hpp"
#include "Menu/KeyboardMenu.hpp"
#include "Menu/SettingsMenu.hpp"
#include "Menu/VolumeMenu.hpp"
#include "Menu/HowToPlayMenu.hpp"
#include "Menu/SettingPlayerMenu.hpp"

#include "KapMirror/KapMirror.hpp"
#include "Prefabs.hpp"

using namespace RType;

GameManager::GameManager(KapEngine::KEngine* _engine) : engine(_engine) {}

void GameManager::launchGame() {
    KapEngine::Debug::log("Launch game");

    registerPrefabs();
    registerMenus();
    initSinglePlayer();
    initMultiPlayer(false);
    initAxis();
    //initSplashScreens();

    // Show main menu
    menuManager.showMenu("MainMenu");

    engine->getGraphicalLibManager()->getCurrentLib()->playMusic("Assets/Sound/Music/space-asteroids.mp3");
}

void GameManager::launchServer() {
    KapEngine::Debug::log("Launch server");

    registerPrefabs();
    initMultiPlayer(true);

    engine->getSceneManager()->loadScene("MultiPlayer");
    networkManager->startServer();
}

void GameManager::registerPrefabs() {
    Prefabs::registerPlayerPrefab(*engine);
    Prefabs::registerBulletPrefab(*engine);
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

    auto settingsMenu = std::make_shared<SettingsMenu>(scene);
    menuManager.registerMenu("SettingsMenu", settingsMenu);

    auto volumeMenu = std::make_shared<VolumeMenu>(scene);
    menuManager.registerMenu("VolumeMenu", volumeMenu);

    auto htpMenu = std::make_shared<HowToPlayMenu>(scene);
    menuManager.registerMenu("HowToPlayMenu", htpMenu);

    auto settingPlayerMenu = std::make_shared<SettingPlayerMenu>(scene);
    menuManager.registerMenu("SettingPlayerMenu", settingPlayerMenu);
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

    auto& playerController = player->getComponent<PlayerController>();
    playerController.setLocalAuthoriy(true);

    // TODO: Fix animation (move animation)
    // https://github.com/aureliancnx/R-Type/blob/ae652adfdf49c702bd8513c27b8bef6dcfeaebc2/Assets/Components/GameManager.cpp#L84
}

// TODO: Move this to a dedicated class
void GameManager::initMultiPlayer(bool isServer) {
    auto scene = engine->getSceneManager()->createScene("MultiPlayer");

    auto networkManagerObject = scene->createGameObject("NetworkManager");
    networkManager = std::make_shared<RtypeNetworkManager>(networkManagerObject, isServer);
    networkManagerObject->addComponent(networkManager);
}

// TODO: Move this to a dedicated class
void GameManager::startLocalMultiPlayer() {
    auto& scene = engine->getSceneManager()->getScene("MultiPlayer");

    networkManager->startClient();
}

void GameManager::initSplashScreens() {
    auto nsplash = std::make_shared<KapEngine::SceneManagement::SplashScreen::SplashScreenNode>("Assets/Textures/Background/bg-back.png", 4);

    nsplash->rect = {0.f, 0.f, 272.f, 160.f};
    nsplash->size = KapEngine::Tools::Vector2({650.f, 382.35f});
    nsplash->pos = KapEngine::Tools::Vector2({35.f, 48.825f});

    engine->getSplashScreen()->addSplashScreen(nsplash);
}

void GameManager::initAxis() {
    KapEngine::Events::Input::Axis horizontal("Horizontal");
    KapEngine::Events::Input::Axis vertical("Vertical");
    KapEngine::Events::Input::Axis shoot("shoot");

    horizontal.positiveButton = KapEngine::Events::Key::RIGHT;
    horizontal.negativeButton = KapEngine::Events::Key::LEFT;

    vertical.positiveButton = KapEngine::Events::Key::UP;
    vertical.negativeButton = KapEngine::Events::Key::DOWN;
    vertical.invert = true;

    shoot.positiveButton = KapEngine::Events::Key::SPACE;

    engine->getEventManager().getInput().addAxis(horizontal);
    engine->getEventManager().getInput().addAxis(vertical);
}
