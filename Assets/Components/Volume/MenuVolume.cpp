//
// Created by leq on 11/10/22.
//

#include "MenuVolume.hpp"

using namespace KapEngine;

RType::MenuVolume::MenuVolume(std::shared_ptr<GameObject> go) : Component(go, "MenuVolum") {}

RType::MenuVolume::~MenuVolume() {}

void RType::MenuVolume::onAwake() {
    _type.push_back("On");
    _type.push_back("Off");
    foundText();
}

void RType::MenuVolume::onUpdate() {
    if (_txt.use_count() == 0) {
        foundText();
        if (_txt.use_count() == 0) {
            DEBUG_ERROR("Fail something");
            return;
        }
    }

    int nId = 0;

    if (PlayerPrefs::getString("volumeID") == "")
        PlayerPrefs::setInt("volumeID", 0);
    else
        nId = PlayerPrefs::getInt("volumeID");
    if (nId >= _type.size())
        nId = 0;
    if (nId == lastId)
        return;

    lastId = nId;
    try {
        auto &txt = _txt->getComponent<UI::Text>();
        txt.setText(_type[nId]);
    } catch (...) {
        DEBUG_ERROR("Failed to load new text");
    }
}

void RType::MenuVolume::foundText() {
    auto objs = getGameObjectConst().getScene().getGameObjects("Type Text Change");
    std::shared_ptr<GameObject> _found;

    for (std::size_t i = 0; i < objs.size(); i++) {
        if (objs[i]->hasComponent("Text")) {
            _found = objs[i];
            break;
        }
    }

    if (_found.use_count() == 0) {
        DEBUG_ERROR("Failed to find volume text");
        return;
    }
    _txt = _found;
    try {
        auto &txt = _txt->getComponent<UI::Text>();
        txt.setText(_type[lastId]);
    } catch (...) {
        DEBUG_ERROR("Failed to load new text");
    }
}