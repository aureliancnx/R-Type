#include "GameManager.hpp"

#include "Menu/MainMenu.hpp"
#include "Menu/SoloMenu.hpp"
#include "Menu/MultiMenu.hpp"

using namespace RType;

GameManager::GameManager(KapEngine::KapEngine& _engine) : engine(_engine) {}

void GameManager::launchGame() {
    KapEngine::Debug::log("Launch game");

    registerScenes();
    registerMenus();
    registerPrefabsPlayer();
    initSoloPlayer();

    // Show main menu
    menuManager.showMenu("MainMenu");
}

void GameManager::registerScenes() {
    KapEngine::Debug::log("Register scenes");

    engine.getSceneManager()->createScene("SoloGame");
    engine.getSceneManager()->createScene("MultiGame");
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
    KAP_DEBUG_LOG("Register player prefabs");

    engine.getPrefabManager()->createPrefab("PlayerNetwork", [](KapEngine::SceneManagement::Scene& scene){
        auto player = KapEngine::UI::UiFactory::createImage(scene, "Player");

        return player;
    });

    engine.getPrefabManager()->createPrefab("PlayerSolo", [](KapEngine::SceneManagement::Scene& scene){
        auto player = scene.createGameObject("Player");
        auto playerCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "Player Canvas");
        auto compPlayer = std::make_shared<KapEngine::RType::Player>(player, "Assets/Textures/Ship/space_ship.png");

        player->addComponent(compPlayer);

        try {
            auto &tr = (KapEngine::Transform &)player->getTransform();
            tr.setParent(playerCanvas->getId());
        } catch (...) {}
        return player;
    });
}

void GameManager::initSoloPlayer() {
    auto scene = engine.getSceneManager()->createScene("Solo Game");
    std::shared_ptr<KapEngine::GameObject> player;

    if (!engine.getPrefabManager()->instantiatePrefab("PlayerSolo", *scene, player)) {
        KAP_DEBUG_ERROR("Failed to instantiate player prefab");
        return;
    }
    auto &tr = (KapEngine::Transform &)player->getTransform();
    tr.setPosition({0, 0, 0});
}
