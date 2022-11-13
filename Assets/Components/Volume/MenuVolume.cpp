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

    if (PlayerPrefs::getString("volumeValue").empty()) {
        PlayerPrefs::setInt("volumeValue", 50);
        nId = 50;
        getEngine().getGraphicalLibManager()->getCurrentLib()->setMusicVolume(
            (float(KapEngine::PlayerPrefs::getInt("volumeValue")) / 100.f));
        getEngine().getGraphicalLibManager()->getCurrentLib()->setSoundVolume(
            (float(KapEngine::PlayerPrefs::getInt("volumeValue")) / 100.f));
    } else {
        nId = PlayerPrefs::getInt("volumeValue");
    }

    if (nId == lastValue) {
        return;
    }

    lastValue = nId;
    try {
        auto &txt = _txt->getComponent<UI::Text>();
        txt.setText(std::to_string(nId));
    } catch (...) { DEBUG_ERROR("Failed to load new text"); }
}

void RType::MenuVolume::foundText() {
    auto objs = getScene().getGameObjects("Volume Value Text");

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
        txt.setText(std::to_string(PlayerPrefs::getInt("volumeValue")));
    } catch (...) { DEBUG_ERROR("Failed to load new text"); }
}