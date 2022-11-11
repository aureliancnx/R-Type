/*
** EPITECH PROJECT, 2022
** RType
** File description:
** LobbyManager.cpp
*/

#include "LobbyManager.hpp"

namespace KapEngine {

    LobbyManager::LobbyManager(std::shared_ptr<KapEngine::GameObject> go) : KapMirror::NetworkComponent(go, "LobbyManager") {
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
        go->setName("MenuManager");
    }

    LobbyManager::~LobbyManager() = default;

    void LobbyManager::onStart() { initLobby(); }

    void LobbyManager::initBackground(std::shared_ptr<KapEngine::GameObject> parent) {
        auto background = parent->getScene().createGameObject("Background");
        background->getComponent<Transform>().setParent(parent->getId());
        background->getComponent<Transform>().setPosition({0, 0, 0});

        auto backgroundImage = std::make_shared<UI::Image>(background);
        Tools::Color color = Tools::Color::grey();
        color.setA(126);
        backgroundImage->setColor(color);
        background->addComponent(backgroundImage);
    }

} // namespace KapEngine