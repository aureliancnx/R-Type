#include "GameManager.hpp"

#include "Menu/MainMenu.hpp"
#include "Menu/SoloMenu.hpp"
#include "Menu/MultiMenu.hpp"
#include "Menu/KeyboardMenu.hpp"
#include "Menu/SettingsMenu.hpp"
#include "Menu/VolumeMenu.hpp"
#include "Menu/HowToPlayMenu.hpp"
#include "Menu/SettingPlayerMenu.hpp"
#include "Menu/ConnectionLostMenu.hpp"
#include "Menu/EndMenu.hpp"
#include "CampaignGenerator/CampaignGenerator.hpp"
#include "Player/PlayerSkin.hpp"
#include "Campaign/MapManager.hpp"
#include "KapMirror/Experimental/Compressions/GZip/GZipCompression.hpp"

#include "Sylph/SylphTransport.hpp"
#include "Prefabs.hpp"
#include "Network/NetStatViewer.hpp"

using namespace RType;

GameManager *GameManager::instance = nullptr;

GameManager::GameManager(KapEngine::KEngine *_engine, bool b) : engine(_engine), displaySplashScreens(b) { instance = this; }

void GameManager::launchGame() {
    KapEngine::Debug::log("Launch game");

    registerPrefabs();
    initEndScene();
    registerMenus();
    initSinglePlayer();
    initMultiPlayer(false);
    initAxis();
    if (displaySplashScreens) {
        initSplashScreens();
    }

    // Show main menu
    menuManager.showMenu("MainMenu");
    engine->getGraphicalLibManager()->getCurrentLib()->playMusic("Assets/Sound/Music/space-asteroids.mp3");
    engine->getGraphicalLibManager()->getCurrentLib()->setMusicVolume((float(KapEngine::PlayerPrefs::getInt("volumeValue")) / 100.f));
    engine->getGraphicalLibManager()->getCurrentLib()->setSoundVolume((float(KapEngine::PlayerPrefs::getInt("volumeValue")) / 100.f));
}

void GameManager::launchServer() {
    KapEngine::Debug::log("Launch server");

    registerPrefabs();
    initMultiPlayer(true);

    engine->getSceneManager()->loadScene("MultiPlayer");
    networkManager->startServer();
}

void GameManager::registerPrefabs() {
    // Player
    Prefabs::registerPlayerPrefab(*engine);

    Prefabs::registerBulletPrefab(*engine);
    Prefabs::registerMissilePrefab(*engine);

    Prefabs::registerBulletExplodePrefab(*engine);
    Prefabs::registerMissileExplodePrefab(*engine);

    Prefabs::registerInGameMenuPrefab(*engine);

    // Default Enemies
    Prefabs::registerBoubouleEnemyPrefab(*engine);
    Prefabs::registerTentaclesBossEnemyPrefab(*engine);

    // Paralax
    Prefabs::registerGalaxyParalaxPrefab(*engine);
    Prefabs::registerStarsParalaxPrefab(*engine);
}

void GameManager::registerMenus() {
    KapEngine::Debug::log("Register menus");

    auto &scene = engine->getSceneManager()->getScene(1);
    auto &endScene = engine->getSceneManager()->getScene("EndScene");
    auto lostConnectionScene = engine->getSceneManager()->createScene("MPConnectionLost");

    // Register menus
    auto mainMenu = std::make_shared<MainMenu>(scene);
    menuManager.registerMenu("MainMenu", mainMenu);

    auto soloMenu = std::make_shared<SoloMenu>(scene, *this);
    menuManager.registerMenu("SoloMenu", soloMenu);

    auto multiMenu = std::make_shared<MultiMenu>(scene, *this);
    menuManager.registerMenu("MultiMenu", multiMenu);

    auto keyMenu = std::make_shared<KeyboardMenu>(scene);
    menuManager.registerMenu("KeysMenu", keyMenu);

    auto settingsMenu = std::make_shared<SettingsMenu>(scene);
    menuManager.registerMenu("SettingsMenu", settingsMenu);

    auto volumeMenu = std::make_shared<VolumeMenu>(scene);
    menuManager.registerMenu("VolumeMenu", volumeMenu);

    auto htpMenu = std::make_shared<HowToPlayMenu>(scene);
    menuManager.registerMenu("HowToPlayMenu", htpMenu);

    auto settingPlayerMenu = std::make_shared<SettingPlayerMenu>(scene);
    menuManager.registerMenu("SettingPlayerMenu", settingPlayerMenu);

    auto endMenu = std::make_shared<EndMenu>(endScene, *this);
    menuManager.registerMenu("EndMenu", endMenu);

    auto connectionLostMenu = std::make_shared<ConnectionLostMenu>(*lostConnectionScene, *this);
    menuManager.registerMenu("MPConnectionLost", connectionLostMenu);
}

MenuManager &GameManager::getMenuManager() { return menuManager; }

void GameManager::initEndScene() { auto scene = engine->getSceneManager()->createScene("EndScene"); }

// TODO: Move this to a dedicated class
void GameManager::initSinglePlayer() {
    auto scene = engine->getSceneManager()->createScene("SinglePlayer");

    std::shared_ptr<KapEngine::GameObject> paralaxGalaxy;
    if (!engine->getPrefabManager()->instantiatePrefab("ParalaxGalaxy", *scene, paralaxGalaxy)) {
        KAP_DEBUG_ERROR("Failed to instantiate paralax prefab");
        return;
    }

    auto &transformPG = paralaxGalaxy->getComponent<KapEngine::Transform>();
    transformPG.setPosition({0, 0, 0});

    std::shared_ptr<KapEngine::GameObject> paralaxStars;
    if (!engine->getPrefabManager()->instantiatePrefab("ParalaxStars", *scene, paralaxStars)) {
        KAP_DEBUG_ERROR("Failed to instantiate paralax prefab");
        return;
    }

    auto &transformPS = paralaxStars->getComponent<KapEngine::Transform>();
    transformPS.setPosition({0, 0, 0});

    std::shared_ptr<KapEngine::GameObject> player;
    if (!engine->getPrefabManager()->instantiatePrefab("Player", *scene, player)) {
        KAP_DEBUG_ERROR("Failed to instantiate player prefab");
        return;
    }

    auto &transform = player->getComponent<KapEngine::Transform>();
    transform.setPosition({0, 0, 0});

    auto &playerIdentity = player->getComponent<KapMirror::NetworkIdentity>();
    playerIdentity.setAuthority(true);

    auto &playerController = player->getComponent<PlayerController>();
    playerController.setLocalAuthority(true);

    std::shared_ptr<GameObject> gameMenu;
    if (!engine->getPrefabManager()->instantiatePrefab("InGameMenu", *scene, gameMenu)) {
        KAP_DEBUG_ERROR("Failed to instantiate in game menu prefab");
        return;
    }

    auto mapManagerObject = scene->createGameObject("MapManager");
    auto mapManager = std::make_shared<MapManager>(mapManagerObject);
    mapManagerObject->addComponent(mapManager);
}

// TODO: Move this to a dedicated class
void GameManager::initMultiPlayer(bool isServer) {
    auto scene = engine->getSceneManager()->createScene("MultiPlayer");

    std::shared_ptr<KapEngine::GameObject> paralaxGalaxy;
    if (!engine->getPrefabManager()->instantiatePrefab("ParalaxGalaxy", *scene, paralaxGalaxy)) {
        KAP_DEBUG_ERROR("Failed to instantiate paralax prefab");
        return;
    }

    auto &transformPG = paralaxGalaxy->getComponent<KapEngine::Transform>();
    transformPG.setPosition({0, 0, 0});

    std::shared_ptr<KapEngine::GameObject> paralaxStars;
    if (!engine->getPrefabManager()->instantiatePrefab("ParalaxStars", *scene, paralaxStars)) {
        KAP_DEBUG_ERROR("Failed to instantiate paralax prefab");
        return;
    }

    auto &transformPS = paralaxStars->getComponent<KapEngine::Transform>();
    transformPS.setPosition({0, 0, 0});

    auto networkManagerObject = scene->createGameObject("NetworkManager");
    networkManager = std::make_shared<RtypeNetworkManager>(networkManagerObject, isServer);
    networkManager->setTransport(std::make_shared<KapMirror::SylphTransport>());
    networkManager->setCompression(std::make_shared<KapMirror::Experimental::GZipCompression>());
    networkManagerObject->addComponent(networkManager);

    auto mapManagerObject = scene->createGameObject("MapManager");
    auto mapManager = std::make_shared<MapManager>(mapManagerObject);
    mapManagerObject->addComponent(mapManager);

    if (!isServer) {
        std::shared_ptr<GameObject> gameMenu;
        if (!engine->getPrefabManager()->instantiatePrefab("InGameMenu", *scene, gameMenu)) {
            KAP_DEBUG_ERROR("Failed to instantiate in game menu prefab");
            return;
        }

        auto netstatObject = scene->createGameObject("NetStatViewer");

        auto networkStatistics = std::make_shared<KapMirror::Experimental::NetworkStatistics>(networkManagerObject);
        netstatObject->addComponent(networkStatistics);

        auto netstat = std::make_shared<NetStatViewer>(netstatObject);
        netstatObject->addComponent(netstat);
    }
}

// TODO: Move this to a dedicated class
void GameManager::startCampaign(const std::string &pathMap) {
    auto scene = engine->getSceneManager()->getScene("SinglePlayer");

    engine->getSceneManager()->loadScene("SinglePlayer");

    auto mapManager = scene.findFirstGameObject("MapManager");
    if (mapManager == nullptr) {
        KAP_DEBUG_ERROR("Failed to find MapManager");
        return;
    }

    auto &mapManagerComponent = mapManager->getComponent<MapManager>();
    mapManagerComponent.loadMapScript(pathMap, false);
}

// TODO: Move this to a dedicated class
void GameManager::startLocalMultiPlayer(const std::string &ip, const std::string &port) {
    engine->getSceneManager()->loadScene("MultiPlayer");

    std::string toConnectIp = ip;
    std::string toConnectPort = port;

    if (toConnectIp.empty()) {
        toConnectIp = "127.0.0.1";
    }

    if (toConnectPort.empty()) {
        toConnectPort = "7777";
    }

    KapEngine::Debug::log("Connecting to " + toConnectIp + ":" + toConnectPort);
    networkManager->networkAddress = toConnectIp;
    networkManager->networkPort = std::stoi(toConnectPort);
    networkManager->startClient();
}

void GameManager::initSplashScreens() {
    engine->getSplashScreen()->setDisplayKapEngineLogo(true);
    auto nsplash =
        std::make_shared<KapEngine::SceneManagement::SplashScreen::SplashScreenNode>("Assets/Textures/Background/bg-back.png", 4);

    nsplash->rect = {0.f, 0.f, 272.f, 160.f};
    nsplash->size = KapEngine::Tools::Vector2({650.f, 382.35f});
    nsplash->pos = KapEngine::Tools::Vector2({35.f, 48.825f});

    engine->getSplashScreen()->addSplashScreen(nsplash);
}

void GameManager::toggleDebugMode() {
    debugMode = !debugMode;

    if (debugMode) {
        KapEngine::Debug::log("Debug mode enabled.");
    } else {
        KapEngine::Debug::log("Debug mode disabled.");
    }
}

bool GameManager::hasDebugMode() const { return debugMode; }

void GameManager::initAxis() {
    KapEngine::Events::Input::Axis horizontal("Horizontal");
    KapEngine::Events::Input::Axis vertical("Vertical");
    KapEngine::Events::Input::Axis shoot("shoot");
    KapEngine::Events::Input::Axis debug("Debug");

    horizontal.positiveButton = KapEngine::Events::Key::RIGHT;
    horizontal.negativeButton = KapEngine::Events::Key::LEFT;

    vertical.positiveButton = KapEngine::Events::Key::UP;
    vertical.negativeButton = KapEngine::Events::Key::DOWN;
    vertical.invert = true;

    shoot.positiveButton = KapEngine::Events::Key::SPACE;
    debug.positiveButton = KapEngine::Events::Key::F3;

    engine->getEventManager().getInput().addAxis(horizontal);
    engine->getEventManager().getInput().addAxis(vertical);
}

std::shared_ptr<RtypeNetworkManager> &GameManager::getNetworkManager() { return networkManager; }
