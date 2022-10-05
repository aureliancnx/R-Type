/*
** EPITECH PROJECT, 2022
** RType2
** File description:
** Button
*/

#include "Button.hpp"
#include "UiImage.hpp"
#include "UiText.hpp"
#include "UiFactory.hpp"
#include "Debug.hpp"
#include "MouseDetector.hpp"
#include "Key.hpp"

KapEngine::UI::Button::Button(std::shared_ptr<GameObject> go, std::string const& textContent) : Component(go, "Button") {
    __init(go);
    setText(textContent);
    setTextColor(Tools::Color::black());
}

KapEngine::UI::Button::~Button() {}

void KapEngine::UI::Button::__init(std::shared_ptr<GameObject> go) {
    addRequireComponent("Image");
    addRequireComponent("Mouse Detector");
    _currentColor = _defaultColor;
    //create mouseDetector if gameObject does not contain
    if (!go->hasComponent("Mouse Detector")) {
        auto md = std::make_shared<MouseDetector>(go);
        go->addComponent(md);
    }
    //create image component if gameObject does not contain
    if (!go->hasComponent("Image")) {
        auto img = std::make_shared<Image>(go);
        go->addComponent(img);
        img->setColor(_defaultColor);
    }
    //create text GameObject
    auto txtObj = UiFactory::createText(go->getScene());
    try {
        auto &tr = (Transform &)txtObj->getTransform();
        tr.setParent(go);
    } catch(...) {
        Debug::error("[BUTTON] cannot get text component of text object from parent " + go->getName());
    }
    __updateImageColor();
}

void KapEngine::UI::Button::__updateImageColor() {
    try {

        auto &img = (Image &)getGameObject().getComponent("Image");
        img.setColor(_currentColor);

    } catch(...) {
        Debug::error("failed to change color button");
    }
}

void KapEngine::UI::Button::setText(std::string const& text) {
    try {
        auto &tr = (Transform &)getGameObject().getTransform();
        std::vector<std::shared_ptr<GameObject>> children = tr.getChildren();
        if (children.size() == 0) {
            Debug::error("Cannot set text of button " + getGameObject().getName());
            return;
        }
        for (std::size_t i = 0; i < children.size(); i++) {
            if (children[i]->hasComponent("Text")) {
                auto &txt = (Text &)children[i]->getComponent("Text");
                txt.setText(text);
            }
        }
    } catch(...) {
        Debug::error("Cannot set text of button " + getGameObject().getName());
    }
}

void KapEngine::UI::Button::setTextColor(Tools::Color const& color) {
    try {
        auto &tr = (Transform &)getGameObject().getTransform();
        std::vector<std::shared_ptr<GameObject>> children = tr.getChildren();
        if (children.size() == 0) {
            Debug::error("Cannot set text of button " + getGameObject().getName());
            return;
        }
        for (std::size_t i = 0; i < children.size(); i++) {
            if (children[i]->hasComponent("Text")) {
                auto &txt = (Text &)children[i]->getComponent("Text");
                txt.setTextColor(color);
            }
        }
    } catch(...) {
        Debug::error("Cannot set text of button " + getGameObject().getName());
    }
}

void KapEngine::UI::Button::setBackground(std::string const& path, Tools::Rectangle const& rect) {
    try {
        auto &img = (Image &)getGameObject().getComponent("Image");
        img.setPathSprite(path);
        img.setRectangle(rect);
    } catch(...) {
        Debug::error("[BUTTON] failed to get image component");
    }
}

void KapEngine::UI::Button::onMouseEnter() {
    if (_currentColor != _hoverColor) {
        _currentColor = _hoverColor;
        __updateImageColor();
    }
    _onHover.invoke();
}

void KapEngine::UI::Button::onMouseStay() {
    if (getInput().getKeyDown(Events::Key::MOUSE_LEFT)) {
        _onClick.invoke();
    }
    if (getInput().getKey(Events::Key::MOUSE_LEFT)) {
        if (_currentColor != _clickedColor) {
            _currentColor = _clickedColor;
            __updateImageColor();
        }
    } else {
        if (_currentColor != _hoverColor) {
            _currentColor = _hoverColor;
            __updateImageColor();
        }
    }
}

void KapEngine::UI::Button::onMouseExit() {
    if (_currentColor != _defaultColor) {
        _currentColor = _defaultColor;
        __updateImageColor();
    }
    _onUnhover.invoke();
}
