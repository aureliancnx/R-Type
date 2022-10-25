/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GameMenuManager
*/

#include "GameMenuManager.hpp"

#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"

using namespace KapEngine;

RType::GameMenuManager::GameMenuManager(std::shared_ptr<GameObject> go) : Component(go, "GameMenuManager") {
    addRequireComponent("Canvas");

    auto screenSize = getGameObject().getEngine().getScreenSize();

    getTransform().setScale({screenSize.getX(), 113, 0});
    getTransform().setPosition({0, screenSize.getY() - 113, 0});
}

RType::GameMenuManager::~GameMenuManager() {}

void RType::GameMenuManager::onAwake() {
    if (!getGameObject().hasComponent<UI::Canvas>()) {
        auto canvas = std::make_shared<UI::Canvas>(getGameObject().getScene().getGameObject(getGameObject().getId()));
        getGameObject().addComponent(canvas);
        canvas->setResizeType(UI::Canvas::ResizyngType::RESIZE_WITH_SCREEN);
    }
    initMainMenu();
    initBonusMenu();
    initPauseMenu();
}

void RType::GameMenuManager::displayMainMenu() {
    if (mainMenu.use_count() != 0) {
        mainMenu->setActive(true);
    } else {
        initMainMenu();
    }

    if (pauseMenu.use_count() != 0) {
        pauseMenu->setActive(false);
    }
    if (bonusMenu.use_count() != 0) {
        bonusMenu->setActive(false);
    }
}

void RType::GameMenuManager::displayBonusMenu() {
    if (bonusMenu.use_count() != 0) {
        bonusMenu->setActive(true);
    } else {
        initBonusMenu();
        bonusMenu->setActive(true);
    }

    if (pauseMenu.use_count() != 0) {
        pauseMenu->setActive(false);
    }
    if (mainMenu.use_count() != 0) {
        mainMenu->setActive(false);
    }
}

void RType::GameMenuManager::displayPauseMenu() {
    if (pauseMenu.use_count() != 0) {
        pauseMenu->setActive(true);
    } else {
        initPauseMenu();
        pauseMenu->setActive(true);
    }

    if (mainMenu.use_count() != 0) {
        mainMenu->setActive(false);
    }
    if (bonusMenu.use_count() != 0) {
        bonusMenu->setActive(false);
    }
}

void RType::GameMenuManager::initMainMenu() {
    //menu set
    mainMenu = getGameObject().getScene().createGameObject("MainMenu");
    mainMenu->getComponent<Transform>().setParent(getGameObject().getId());

    initBackground(mainMenu);
}

void RType::GameMenuManager::initPauseMenu() {
    //menu set
    pauseMenu = getGameObject().getScene().createGameObject("PauseMenu");
    pauseMenu->getComponent<Transform>().setParent(getGameObject().getId());
    pauseMenu->setActive(false);

    initBackground(pauseMenu);
}

void RType::GameMenuManager::initBonusMenu() {
    //menu set
    bonusMenu = getGameObject().getScene().createGameObject("BonusMenu");
    bonusMenu->getComponent<Transform>().setParent(getGameObject().getId());
    bonusMenu->setActive(false);

    initBackground(bonusMenu);
}

void RType::GameMenuManager::initBackground(std::shared_ptr<GameObject> parent) {
    auto background = parent->getScene().createGameObject("Background");
    background->getComponent<Transform>().setParent(parent->getId());
    background->getComponent<Transform>().setPosition({0, 0, 0});

    auto backgroundImage = std::make_shared<UI::Image>(background);
    backgroundImage->setColor(Tools::Color::grey());
    background->addComponent(backgroundImage);
}

std::shared_ptr<GameObject> RType::GameMenuManager::initButton(std::shared_ptr<GameObject> parent, std::string name, std::string text, std::function<void()> callback, Tools::Color color, Tools::Color textColor) {
    auto button = parent->getScene().createGameObject(name);
    button->getComponent<Transform>().setParent(parent->getId());
    button->getComponent<Transform>().setPosition({0, 0, 0});

    auto buttonImage = std::make_shared<UI::Button>(button);
    buttonImage->setText(text);
    buttonImage->getOnClick().registerAction(callback);
    // buttonImage->setColor(color);
    buttonImage->setTextColor(textColor);
    button->addComponent(buttonImage);
    return button;
}

std::shared_ptr<GameObject> RType::GameMenuManager::initButton(std::shared_ptr<GameObject> parent, std::string name, std::string text, std::function<void()> callback, std::string pathSprite, Tools::Rectangle rect, Tools::Color color, Tools::Color textColor) {
    auto button = parent->getScene().createGameObject(name);
    button->getComponent<Transform>().setParent(parent->getId());
    button->getComponent<Transform>().setPosition({0, 0, 0});

    auto buttonImage = std::make_shared<UI::Button>(button);
    buttonImage->setText(text);
    buttonImage->getOnClick().registerAction(callback);
    // buttonImage->setColor(color);
    buttonImage->setTextColor(textColor);
    buttonImage->setBackground(pathSprite, rect);
    button->addComponent(buttonImage);
    return button;
}
