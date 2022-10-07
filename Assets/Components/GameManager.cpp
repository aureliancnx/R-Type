#include "GameManager.hpp"

#include "Menu/MainMenu.hpp"

using namespace RType;

GameManager::GameManager(KapEngine::KapEngine& _engine) : engine(_engine) {}

void GameManager::launchGame() {
    KapEngine::Debug::log("Launch game");

    registerScenes();
    registerMenus();

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
    auto mainMenu = std::make_shared<MainMenu>(*this, scene);
    menuManager.registerMenu("MainMenu", mainMenu);
}

void GameManager::swichMenu(std::string const& currentMenu, std::string const& menuName) {
    menuManager.hideMenu(currentMenu);
    menuManager.showMenu(currentMenu);
}
