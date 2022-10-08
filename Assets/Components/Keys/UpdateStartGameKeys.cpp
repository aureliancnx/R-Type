/*
** EPITECH PROJECT, 2022
** RType
** File description:
** UpdateStartGameKeys
*/

#include "UpdateStartGameKeys.hpp"

RType::UpdateStartGameKeys::UpdateStartGameKeys(std::shared_ptr<GameObject> go) : Component(go, "UpdateStartGameKeys"),
    _baseAxisHor("basicHorizontal"), _baseAxisVert("basicVertical"), _baseAxisShoot("basicShoot") {

    _baseAxisHor.positiveButton = Events::Key::RIGHT;
    _baseAxisHor.negativeButton = Events::Key::LEFT;

    _baseAxisVert.positiveButton = Events::Key::DOWN;
    _baseAxisVert.negativeButton = Events::Key::UP;

    _baseAxisShoot.positiveButton = Events::Key::MOUSE_LEFT;
}

RType::UpdateStartGameKeys::~UpdateStartGameKeys() {}

void RType::UpdateStartGameKeys::checkInputs() {

    Events::Key up = _baseAxisVert.negativeButton;
    Events::Key down = _baseAxisVert.positiveButton;
    Events::Key left = _baseAxisHor.negativeButton;
    Events::Key right = _baseAxisHor.positiveButton;
    Events::Key shoot = _baseAxisShoot.positiveButton;

    setValueSaved("upInput", up);
    setValueSaved("downInput", down);
    setValueSaved("leftInput", left);
    setValueSaved("rightInput", right);
    setValueSaved("shootInput", shoot);

    try {
        auto &axis = getInput().getAxisSettings("Vertical");

        axis.positiveButton = down;
        axis.negativeButton = up;
    } catch(...) {
        KAP_DEBUG_ERROR("Failed to update Vertical axis");
    }

    try {
        auto &axis = getInput().getAxisSettings("Horizontal");

        axis.positiveButton = right;
        axis.negativeButton = left;
    } catch(...) {
        KAP_DEBUG_ERROR("Failed to update Horizontal axis");
    }

    try {
        auto &axis = getInput().getAxisSettings("Shoot");

        axis.positiveButton = shoot;
    } catch(...) {
        KAP_DEBUG_ERROR("Failed to update Shoot axis");
    }

}

bool setValueSaved(std::string const& name, Events::Key &key) {
    if (PlayerPrefs::getString(name) == "")
        return false;
    int val = PlayerPrefs::getInt(name);
    if (!Events::Key::intInEnum(val))
        return false;
    key = (Events::Key::EKey)val;
    return true;
}
