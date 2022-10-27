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

    float sizeY = 90;
    getTransform().setScale({screenSize.getX(), sizeY, 0});
    getTransform().setPosition({0, screenSize.getY() - sizeY, 0});
    if (!getGameObject().hasComponent<UI::Canvas>()) {
        auto canvas = std::make_shared<UI::Canvas>(getGameObject().getScene().getGameObject(getGameObject().getId()));
        getGameObject().addComponent(canvas);
        canvas->setResizeType(UI::Canvas::ResizyngType::RESIZE_WITH_SCREEN);
    }
}

RType::GameMenuManager::~GameMenuManager() {}

void RType::GameMenuManager::onAwake() {
    initMainMenu();
}

void RType::GameMenuManager::displayMainMenu() {
    if (mainMenu.use_count() != 0) {
        mainMenu->setActive(true);
    } else {
        initMainMenu();
    }
}

void RType::GameMenuManager::initMainMenu() {
    //menu set
    mainMenu = getGameObject().getScene().createGameObject("MainMenu");
    mainMenu->getComponent<Transform>().setParent(getGameObject().getId());

    Tools::Vector3 btnSize = {80.f / getGameObject().getEngine().getScreenSize().getX(), 80.f / 90.f, 0};
    Tools::Vector3 btnBasePos;

    KAP_DEBUG_LOG("Button size: " + btnSize.to_string());

    initBackground(mainMenu);

    //create quit button
    {
        auto btn = initButton(mainMenu, "QuitBtn", "", [this](){
            getGameObject().getEngine().getSceneManager()->loadScene(1);
        }, "Assets/Textures/Icons/logout.png", {0, 0, 512, 512});
        auto &tr = btn->getComponent<Transform>();

        tr.setScale(btnSize);
        tr.setPosition(btnBasePos + Tools::Vector3(160, 0, 0));
    }
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
    std::shared_ptr<GameObject> button = parent->getScene().createGameObject(name);

    if (IS_MAX_KAPUI_VERSION(0, 101)) {
        auto btnComp = KapEngine::UI::KapUiFactory::createButton(button, text);
        btnComp->setTextColor(textColor);
        btnComp->setNormalColor(color);
        btnComp->getOnClick().registerAction(callback);
    } else {
        KapEngine::UI::KapUiFactory::createButton(button, text, callback, textColor, color);
    }

    try {
        button->getComponent<Transform>().setParent(parent->getId());
    } catch (...) {
        KAP_DEBUG_ERROR("Failled to set button " + name + " parent");
    }
    return button;
}

std::shared_ptr<GameObject> RType::GameMenuManager::initButton(std::shared_ptr<GameObject> parent, std::string name, std::string text, std::function<void()> callback, std::string pathSprite, Tools::Rectangle rect, Tools::Color color, Tools::Color textColor) {
    std::shared_ptr<GameObject> button = parent->getScene().createGameObject(name);

    if (IS_MAX_KAPUI_VERSION(0, 101)) {
        auto btnComp = KapEngine::UI::KapUiFactory::createButton(button, text);
        btnComp->setTextColor(textColor);
        btnComp->setNormalColor(color);
        btnComp->getOnClick().registerAction(callback);
        btnComp->setBackground(pathSprite, rect);
    } else {
        auto btnComp = KapEngine::UI::KapUiFactory::createButton(button, text, callback, textColor, color);
        btnComp->setBackground(pathSprite, rect);
    }

    try {
        button->getComponent<Transform>().setParent(parent->getId());
    } catch (...) {
        KAP_DEBUG_ERROR("Failled to set button " + name + " parent");
    }
    return button;
}
