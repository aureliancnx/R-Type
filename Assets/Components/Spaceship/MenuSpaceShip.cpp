/*
** EPITECH PROJECT, 2022
** RType
** File description:
** MenuSpaceShip
*/

#include "MenuSpaceShip.hpp"

using namespace KapEngine;

RType::MenuSpaceShip::MenuSpaceShip(std::shared_ptr<GameObject> go) : Component(go, "MenuSpasceShip") {}

RType::MenuSpaceShip::~MenuSpaceShip() {}

void RType::MenuSpaceShip::onAwake() {
    _pathes.push_back("Assets/Textures/ship1.png");
    _pathes.push_back("Assets/Textures/ship2.png");
    _pathes.push_back("Assets/Textures/ship3.png");
    _pathes.push_back("Assets/Textures/ship4.png");
    _pathes.push_back("Assets/Textures/ship5.png");
    foundImage();
}

void RType::MenuSpaceShip::onUpdate() {
    if (_img.use_count() == 0) {
        foundImage();
        if (_img.use_count() == 0)
            return;
    }

    //check id path
    int nId = 0;
    if (PlayerPrefs::getString("shipID") == "") {
        PlayerPrefs::setInt("shipID", 0);
    } else {
        nId = PlayerPrefs::getInt("shipID");
    }
    if (nId >= _pathes.size())
        nId = 0;
    if (nId == lastId)
        return;

    //change id path
    lastId = nId;
    try {        
        auto &img = _img->getComponent<UI::Image>();
        img.setPathSprite(_pathes[nId]);
    } catch(...) {
        DEBUG_ERROR("Failed to load new sprite");
    }
}

void RType::MenuSpaceShip::foundImage() {
    auto objs = getGameObjectConst().getScene().getGameObjects("Animation Ship");
    std::shared_ptr<GameObject> _found;

    for (std::size_t i = 0; i < objs.size(); i++) {
        if (objs[i]->hasComponent("Image")) {
            _found = objs[i];
            break;
        }
    }

    if (_found.use_count() == 0) {
        KAP_DEBUG_ERROR("Failed to find spaceship image");
        return;
    }
    _img = _found;
    try {        
        auto &img = _img->getComponent<UI::Image>();
        img.setPathSprite(_pathes[lastId]);
    } catch(...) {
        DEBUG_ERROR("Failed to load new sprite");
    }
}
