#include "GameManager.hpp"

#include "Menu/MainMenu.hpp"
#include "Menu/SoloMenu.hpp"
#include "Menu/MultiMenu.hpp"
#include "Menu/KeyboardMenu.hpp"
#include "Menu/SettingsMenu.hpp"
#include "Menu/VolumeMenu.hpp"
#include "Menu/HowToPlayMenu.hpp"
#include "Menu/SettingPlayerMenu.hpp"
#include "Menu/EndMenu.hpp"
#include "CampaignGenerator/CampaignGenerator.hpp"
#include "Player/PlayerSkin.hpp"
#include "Campaign/CampaignManager.hpp"

#include "Sylph/SylphTransport.hpp"
#include "Prefabs.hpp"
#include "NetStatViewer.hpp"

RType::GameManager* RType::GameManager::instance = nullptr;

RType::GameManager::GameManager(KapEngine::KEngine* _engine, bool b) : engine(_engine), displaySplashScreens(b) { instance = this; }

void RType::GameManager::launchGame() {
    KapEngine::Debug::log("Launch game");

    registerPrefabs();
    initEndScene();
    registerMenus();
    initSinglePlayer();
    initMultiPlayer(false);
    initAxis();
    engine->getSplashScreen()->setDisplayKapEngineLogo(false);
    if (displaySplashScreens) {
        initSplashScreens();
    }

    // Show main menu
    menuManager.showMenu("MainMenu");
    menuManager.showMenu("EndMenu");

    engine->getGraphicalLibManager()->getCurrentLib()->playMusic("Assets/Sound/Music/space-asteroids.mp3");
    engine->getGraphicalLibManager()->getCurrentLib()->setMusicVolume((float(KapEngine::PlayerPrefs::getInt("volumeValue")) / 100.f));
    engine->getGraphicalLibManager()->getCurrentLib()->setSoundVolume((float(KapEngine::PlayerPrefs::getInt("volumeValue")) / 100.f));
}

void RType::GameManager::launchServer() {
    KapEngine::Debug::log("Launch server");
    engine->getSplashScreen()->setDisplayKapEngineLogo(false);

    registerPrefabs();
    initMultiPlayer(true);

    engine->getSceneManager()->loadScene("MultiPlayer");
    networkManager->startServer();
}

void RType::GameManager::registerPrefabs() {
    // Player
    Prefabs::registerPlayerPrefab(*engine);

    Prefabs::registerBulletPrefab(*engine);
    Prefabs::registerMissilePrefab(*engine);

    Prefabs::registerBulletExplodePrefab(*engine);
    Prefabs::registerMissileExplodePrefab(*engine);

    Prefabs::registerInGameMenuPrefab(*engine);

    // Enemies
    Prefabs::registerShipEnemyPrefab(*engine);
    Prefabs::registerBoubouleEnemyPrefab(*engine);
    Prefabs::registerTentaclesBossEnemyPrefab(*engine);

    // Paralax
    Prefabs::registerGalaxyParalaxPrefab(*engine);
    Prefabs::registerStarsParalaxPrefab(*engine);
}

void RType::GameManager::registerMenus() {
    KapEngine::Debug::log("Register menus");

    auto& scene = engine->getSceneManager()->getScene(1);
    auto& endScene = engine->getSceneManager()->getScene("EndScene");

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
}

void RType::GameManager::initEndScene() { auto scene = engine->getSceneManager()->createScene("EndScene"); }

// TODO: Move this to a dedicated class
void RType::GameManager::initSinglePlayer() {
    auto scene = engine->getSceneManager()->createScene("SinglePlayer");

    std::shared_ptr<KapEngine::GameObject> paralaxGalaxy;
    if (!engine->getPrefabManager()->instantiatePrefab("ParalaxGalaxy", *scene, paralaxGalaxy)) {
        KAP_DEBUG_ERROR("Failed to instantiate paralax prefab");
        return;
    }

    auto& transformPG = paralaxGalaxy->getComponent<KapEngine::Transform>();
    transformPG.setPosition({0, 0, 0});

    std::shared_ptr<KapEngine::GameObject> paralaxStars;
    if (!engine->getPrefabManager()->instantiatePrefab("ParalaxStars", *scene, paralaxStars)) {
        KAP_DEBUG_ERROR("Failed to instantiate paralax prefab");
        return;
    }

    auto& transformPS = paralaxStars->getComponent<KapEngine::Transform>();
    transformPS.setPosition({0, 0, 0});

    std::shared_ptr<KapEngine::GameObject> player;
    if (!engine->getPrefabManager()->instantiatePrefab("Player", *scene, player)) {
        KAP_DEBUG_ERROR("Failed to instantiate player prefab");
        return;
    }

    player->getComponent<PlayerSkin>().setSkinId(player->getComponent<PlayerSkin>().getSkinId());

    auto& transform = player->getComponent<KapEngine::Transform>();
    transform.setPosition({0, 0, 0});

    auto& playerController = player->getComponent<PlayerController>();
    playerController.setLocalAuthority(true);

    std::shared_ptr<GameObject> gameMenu;
    if (!engine->getPrefabManager()->instantiatePrefab("InGameMenu", *scene, gameMenu)) {
        KAP_DEBUG_ERROR("Failed to instantiate in game menu prefab");
        return;
    }

    auto campaignManager = std::make_shared<CampaignManager>(gameMenu);
    gameMenu->addComponent(campaignManager);
    // TODO: Fix animation (move animation)
    // https://github.com/aureliancnx/R-Type/blob/ae652adfdf49c702bd8513c27b8bef6dcfeaebc2/Assets/Components/GameManager.cpp#L84
}

// TODO: Move this to a dedicated class
void RType::GameManager::initMultiPlayer(bool isServer) {
    auto scene = engine->getSceneManager()->createScene("MultiPlayer");

    std::shared_ptr<KapEngine::GameObject> paralaxGalaxy;
    if (!engine->getPrefabManager()->instantiatePrefab("ParalaxGalaxy", *scene, paralaxGalaxy)) {
        KAP_DEBUG_ERROR("Failed to instantiate paralax prefab");
        return;
    }

    auto& transformPG = paralaxGalaxy->getComponent<KapEngine::Transform>();
    transformPG.setPosition({0, 0, 0});

    std::shared_ptr<KapEngine::GameObject> paralaxStars;
    if (!engine->getPrefabManager()->instantiatePrefab("ParalaxStars", *scene, paralaxStars)) {
        KAP_DEBUG_ERROR("Failed to instantiate paralax prefab");
        return;
    }

    auto& transformPS = paralaxStars->getComponent<KapEngine::Transform>();
    transformPS.setPosition({0, 0, 0});

    auto networkManagerObject = scene->createGameObject("NetworkManager");
    networkManager = std::make_shared<RtypeNetworkManager>(networkManagerObject, isServer);
    networkManager->setTransport(std::make_shared<KapMirror::SylphTransport>());
    networkManagerObject->addComponent(networkManager);

    if (!isServer) {
        std::shared_ptr<GameObject> gameMenu;
        if (!engine->getPrefabManager()->instantiatePrefab("InGameMenu", *scene, gameMenu)) {
            KAP_DEBUG_ERROR("Failed to instantiate in game menu prefab");
            return;
        }

        auto networkStatistics = std::make_shared<KapMirror::Experimental::NetworkStatistics>(networkManagerObject);

        auto netstatObject = scene->createGameObject("NetStatViewer");
        std::shared_ptr<NetStatViewer> netstat = std::make_shared<NetStatViewer>(netstatObject, networkStatistics);
        // netstatObject->addComponent(networkStatistics);
        netstatObject->addComponent(netstat);
    }
}

// TODO: Move this to a dedicated class
void RType::GameManager::startCampaign() {
    auto& scene = engine->getSceneManager()->getScene("SinglePlayer");

    auto enemies = scene.createGameObject("Enemies Generator");
    auto compEnemies = std::make_shared<CampaignGenerator>(enemies);
    enemies->addComponent(compEnemies);
}

// TODO: Move this to a dedicated class
void RType::GameManager::startLocalMultiPlayer() {
    auto& scene = engine->getSceneManager()->getScene("MultiPlayer");

    networkManager->startClient();
}

void RType::GameManager::initSplashScreens() {
    engine->getSplashScreen()->setDisplayKapEngineLogo(true);
    auto nsplash =
        std::make_shared<KapEngine::SceneManagement::SplashScreen::SplashScreenNode>("Assets/Textures/Background/bg-back.png", 4);

    nsplash->rect = {0.f, 0.f, 272.f, 160.f};
    nsplash->size = KapEngine::Tools::Vector2({650.f, 382.35f});
    nsplash->pos = KapEngine::Tools::Vector2({35.f, 48.825f});

    engine->getSplashScreen()->addSplashScreen(nsplash);
}

void RType::GameManager::initAxis() {
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

std::shared_ptr<RType::RtypeNetworkManager>& RType::GameManager::getNetworkManager() { return networkManager; }
