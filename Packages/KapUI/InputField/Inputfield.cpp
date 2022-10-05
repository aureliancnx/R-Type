/*
** EPITECH PROJECT, 2022
** RType2
** File description:
** Inputfield
*/

#include "Inputfield.hpp"
#include "MouseDetector.hpp"
#include "Transform.hpp"

#include "UiImage.hpp"
#include "UiText.hpp"
#include "UiFactory.hpp"

#include "Debug.hpp"

KapEngine::UI::Inputfield::Inputfield(std::shared_ptr<GameObject> go) : Component(go, "InputField") {
    __init(go);
    setPlaceholderText("Enter text here...");
}

KapEngine::UI::Inputfield::~Inputfield() {}

void KapEngine::UI::Inputfield::onFixedUpdate() {
    if (getInput().getKeyDown(Events::Key::MOUSE_LEFT)) {
        if (_hovered) {
            _clicked = true;
        } else {
            _clicked = false;
        }
    }
    if (!_clicked)
        return;
    //check remove content
    if (getInput().getKeyDown(Events::Key::BACK) || getInput().getKeyDown(Events::Key::BACKSPACE)) {
        _content.resize(_content.size() - 1);
        Debug::log("new inputfield contrent: " + _content);
    } else {
        std::string val = __getInput();
        if (val != "\n") {
            if (getInput().getKey(Events::Key::LEFT_SHIFT) || getInput().getKey(Events::Key::RIGHT_SHIFT)) {
                for (std::size_t i = 0; i < val.size(); i++) {
                    val[i] = std::toupper(val[i]);
                }
            } else {
                for (std::size_t i = 0; i < val.size(); i++) {
                    val[i] = std::tolower(val[i]);
                }
            }
        } else {
            val = "";
            _hovered = false;
        }
        if (val != "" && _type == InputType::NUMBER) {
            if (!__stringIsNumber(val)) {
                val = "";
            }
        } else if (val != "" && _type == InputType::IPV4) {
            if (__stringIsNumber(val)) {
                if (_content.size() == 2 || _content.size() == 6 || _content.size() == 10) {
                    val += ".";
                } else if (_content.size() >= 15) {
                    val = "";
                }
            } else {
                val = "";
            }
        }

        if (val != "") {
            _content += val;
        }
    }
    __updateTexts();
}

void KapEngine::UI::Inputfield::onMouseEnter() {
    _hovered = true;
}

void KapEngine::UI::Inputfield::onMouseStay() {}

void KapEngine::UI::Inputfield::onMouseExit() {
    _hovered = false;
}

std::string KapEngine::UI::Inputfield::__getInput() {
    for (std::size_t i = 0; i < Events::Key::maxValue(); i++) {
        Events::Key _key;
        _key = (Events::Key::EKey)i;
        if (getInput().getKeyDown(_key)) {
            return _key.getTextValue();
        }
    }

    return "";
}

void KapEngine::UI::Inputfield::__updateTexts() {
    std::vector<std::shared_ptr<GameObject>> children;

    try {
        children = ((Transform &)getGameObject().getTransform()).getChildren();
    } catch(...) {
        Debug::error("[INPUT FIELD] Failed to get children of inputfield " + getGameObject().getName());
        return;
    }

    for (std::size_t i = 0; i < children.size(); i++) {
        if (_content.size() == 0) {
            if (children[i]->getName() == "Text") {
                children[i]->setActive(false);
            } else if (children[i]->getName() == "Placeholder") {
                children[i]->setActive(true);
            }
        } else {
            if (children[i]->getName() == "Text") {
                children[i]->setActive(true);
                try {
                    auto &txt = (UI::Text &)children[i]->getComponent("Text");
                    txt.setText(__getFormatedText());
                } catch(...) {
                    Debug::error("[INPUT FIELD] Failed to set content of text inputfield " + getGameObject().getName());
                }
            } else if (children[i]->getName() == "Placeholder") {
                children[i]->setActive(false);
            }
        }
    }
}

std::string KapEngine::UI::Inputfield::__getFormatedText() const {
    std::string result = _content;

    if (_type == InputType::PASSWORD) {
        result.clear();
        for (std::size_t i = 0; i < _content.size(); i++)
            result.push_back('*');
    }

    return result;
}

void KapEngine::UI::Inputfield::__init(std::shared_ptr<GameObject> go) {
    if (!go->hasComponent("Image")) {
        auto img = std::make_shared<Image>(go);
        go->addComponent(img);
    }
    if (!go->hasComponent("Mouse Detector")) {
        auto md = std::make_shared<MouseDetector>(go);
        go->addComponent(md);
    }

    auto text = UiFactory::createText(go->getScene(), "Text");
    auto placeholder = UiFactory::createText(go->getScene(), "Placeholder");

    try {
        auto &trTxt = (Transform &)text->getTransform();
        auto &trPhd = (Transform &)placeholder->getTransform();

        trTxt.setParent(go);
        trPhd.setParent(go);

        auto &txtTxt = (Text &)text->getComponent("Text");
        auto &txtPhd = (Text &)placeholder->getComponent("Text");

        txtPhd.setTextColor(Tools::Color::grey());
        txtTxt.setTextColor(Tools::Color::black());
    } catch(...) {
        Debug::error("Failed to get transform of text and placeholder in inputfield creation");
    }
}

void KapEngine::UI::Inputfield::setPlaceholderText(std::string const& text) {
    try {
        auto &tr = (Transform &)getGameObject().getTransform();
        std::vector<std::shared_ptr<GameObject>> children = tr.getChildren();

        for (std::size_t i = 0; i < children.size(); i++) {
            if (children[i]->getName() == "Placeholder") {
                auto &txt = (Text &)children[i]->getComponent("Text");
                txt.setText(text);
                break;
            }
        }
    } catch(...) {
        Debug::error("Failed to set text placeholder of " + getGameObject().getName());
    }
}
