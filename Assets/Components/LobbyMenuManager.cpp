/*
** EPITECH PROJECT, 2022
** RType
** File description:
** LobbyMenuManager.cpp
*/

#include "LobbyMenuManager.hpp"

#include "Messages.hpp"

using namespace KapEngine;

RType::LobbyMenuManager::LobbyMenuManager(std::shared_ptr<KapEngine::GameObject> go) : KapMirror::NetworkComponent(go, "LobbyManger") {
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

void RType::LobbyMenuManager::onStart() {}

void RType::LobbyMenuManager::onStartClient() { initLobbyMenu(false); }

void RType::LobbyMenuManager::initBackground(std::shared_ptr<KapEngine::GameObject> parent) {
    auto background = parent->getScene().createGameObject("Background");
    background->getComponent<Transform>().setParent(parent->getId());
    background->getComponent<Transform>().setPosition({0, 0, 0});

    auto backgroundImage = std::make_shared<UI::Image>(background);
    Tools::Color color = Tools::Color::grey();
    color.setA(255);
    backgroundImage->setColor(color);
    background->addComponent(backgroundImage);
}

void RType::LobbyMenuManager::initLobbyMenu(bool local) {

    lobbyMenu = getGameObject().getScene().createGameObject("LobbyMenu");
    lobbyMenu->getComponent<Transform>().setParent(getGameObject().getId());

    Tools::Vector3 btnSize = {80.f / getGameObject().getEngine().getScreenSize().getX(), 80.f / 90.f, 0};
    Tools::Vector3 btnBasePos = {10, 5, 0};

    KAP_DEBUG_LOG("Button size: " + btnSize.to_string());

    initBackground(lobbyMenu);

    auto &scene = getGameObject().getScene();

    // Ready / Play button
    {
        std::shared_ptr<GameObject> btn;
        if (isClient()) {
            btn = initButton(lobbyMenu, "Ready", "Ready", [this]() { startGame(); }, "Assets/Textures/button.png", {5, 9, 655, 213});
        }
        auto &tr = btn->getComponent<Transform>();

        tr.setScale(btnSize);
        tr.setPosition({150, 5, 0});
    }

    // Text for input map
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Choose Map Text");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Path map : ");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        Tools::Vector3 calculatedPos;
        calculatedPos.setX(getEngine().getScreenSize().getX() - 80.0f - 250);
        calculatedPos.setY(40);

        txt->addComponent(compText);
        transform.setScale({150, 35, 0});
        transform.setPosition(calculatedPos);
        transform.setParent(lobbyMenu->getId());
    }

    // Input map
    {
        auto inpt = scene.createGameObject("InputFieldMap");

        mapField = std::make_shared<KapEngine::UI::Inputfield>(inpt);
        inpt->addComponent(mapField);
        mapField->setPlaceholderText("Maps/TestMapServer.lua");

        Tools::Vector3 calculatedPos;
        calculatedPos.setX(getEngine().getScreenSize().getX() - 80.0f - 100);
        calculatedPos.setY(5);

        auto &transform = inpt->getComponent<KapEngine::Transform>();
        transform.setScale({150, 15, 0});
        transform.setPosition(calculatedPos);
        transform.setParent(lobbyMenu->getId());
    }
}

std::shared_ptr<KapEngine::GameObject> RType::LobbyMenuManager::initButton(std::shared_ptr<KapEngine::GameObject> parent, std::string name,
                                                                           std::string text, std::function<void()> callback,
                                                                           KapEngine::Tools::Color color,
                                                                           KapEngine::Tools::Color textColor) {
    std::shared_ptr<GameObject> button = parent->getScene().createGameObject(name);

#if IS_MAX_KAPUI_VERSION(0, 101)
    auto btnComp = KapEngine::UI::KapUiFactory::createButton(button, text);
    btnComp->setTextColor(textColor);
    btnComp->setNormalColor(color);
    btnComp->getOnClick().registerAction(callback);
#else
    KapEngine::UI::KapUiFactory::createButton(button, text, callback, color, textColor);
#endif

    try {
        button->getComponent<Transform>().setParent(parent->getId());
    } catch (...) { KAP_DEBUG_ERROR("Failled to set button " + name + " parent"); }
    return button;
}
std::shared_ptr<KapEngine::GameObject> RType::LobbyMenuManager::initButton(std::shared_ptr<KapEngine::GameObject> parent, std::string name,
                                                                           std::string text, std::function<void()> callback,
                                                                           std::string pathSprite, KapEngine::Tools::Rectangle rect,
                                                                           KapEngine::Tools::Color color,
                                                                           KapEngine::Tools::Color textColor) {
    std::shared_ptr<GameObject> button = parent->getScene().createGameObject(name);

#if IS_MAX_KAPUI_VERSION(0, 101)
    auto btnComp = KapEngine::UI::KapUiFactory::createButton(button, text);
    btnComp->setTextColor(textColor);
    btnComp->setNormalColor(color);
    btnComp->getOnClick().registerAction(callback);
    btnComp->setBackground(pathSprite, rect);
#else
    auto btnComp = KapEngine::UI::KapUiFactory::createButton(button, text, callback, color, textColor);
    btnComp->setBackground(pathSprite, rect);
    btnComp->setTextPosition({25, 12});
#endif

    try {
        button->getComponent<Transform>().setParent(parent->getId());
        button->getComponent<Transform>().setScale({100, 230, 0});
    } catch (...) { KAP_DEBUG_ERROR("Failled to set button " + name + " parent"); }
    return button;
}

void RType::LobbyMenuManager::quit() {
    lobbyMenu->setActive(false);
    //    try {
    //        auto go = getGameObject().getScene().findFirstGameObject("MenuManager");
    //        if (go) {
    //            go->getComponent<GameMenuManager>().setActive(true);
    //        }
    //    } catch (...) { KAP_DEBUG_ERROR("Failed to find MenuManager"); }
}

void RType::LobbyMenuManager::startGame() {
    StartGameMessage message;
    KAP_DEBUG_WARNING("Map: " + mapField->getText());
    if (mapField->getText().empty())
        message.mapScriptPath = "Maps/TestMapServer.lua";
    else
        message.mapScriptPath = mapField->getText();
    getClient()->send(message);
}
