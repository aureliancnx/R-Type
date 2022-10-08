/*
** EPITECH PROJECT, 2022
** RType
** File description:
** KeySelector
*/

#include "KeySelector.hpp"

RType::KeySelector::KeySelector(std::shared_ptr<GameObject> go) : Component(go, "KeySelector") {}

RType::KeySelector::~KeySelector() {}

void RType::KeySelector::onUpdate() {
    if (_check == false)
        return;
    for (std::size_t i = Events::Key::minValue(); i < Events::Key::maxValue(); i++) {
        if (Events::Key::intInEnum(i)) {
            Events::Key toCheck;
            toCheck = (Events::Key::EKey)i;
            if (getInput().getKey(toCheck)) {
                _selected = toCheck;
                _check = false;
                return;
            }
        }
    }
}

bool RType::KeySelector::keySelected(Events::Key &key) {
    if (_selected == Events::Key::UNKNOWN)
        return false;
    _check = false;
    key = _selected;
    return true;
}

void RType::KeySelector::selectKey() {
    _selected = Events::Key::UNKNOWN;
    _check = true;
}
