/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Button
*/

#include "Button.hpp"
#include "Debug.hpp"
#include "MouseDetector.hpp"
#include "UiImage.hpp"
#include "Transform.hpp"

KapEngine::KapUI::Button::Button(std::shared_ptr<GameObject> go) : Component(go, "KapButton") {
    addRequireComponent("Mouse Detector");
    addRequireComponent("Image");
    auto mouseDetector = std::make_shared<MouseDetector>(go);
    auto img = std::make_shared<UI::Image>(go);

    mouseDetector->setCheckZone(Tools::Rectangle(0, 0, 100, 100));

    try {
        Transform &tr = (Transform &)go->getTransform();
        tr.setPosition(Tools::Vector3::zero());
        tr.setScale(Tools::Vector3(100, 100, 0));
    } catch(...) {}

    go->addComponent(mouseDetector);
    go->addComponent(img);
}

void KapEngine::KapUI::Button::onAwake() {
}

void KapEngine::KapUI::Button::onMouseEnter() {
    Debug::log("Mouse enter");
}

void KapEngine::KapUI::Button::onMouseStay() {
    if (_in)
        return;
    _in = true;
    Debug::log("Mouse Stay");
}

void KapEngine::KapUI::Button::onMouseExit() {
    _in = false;
    Debug::log("Mouse leave");
}

