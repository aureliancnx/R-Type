#include "ChangeKey.hpp"
#include "KeySelector.hpp"

RType::ChangeKey::ChangeKey(std::shared_ptr<GameObject> go) : Component(go, "ChangeKey") {
    addRequireComponent("KeySelector");

    if (!getGameObject().hasComponent("KeySelector")) {
        auto keySelector = std::make_shared<KeySelector>(go);
        go->addComponent(keySelector);
    }
}

RType::ChangeKey::~ChangeKey() {}

void RType::ChangeKey::onAwake() {
    if (_idSettings == 0 || _idInput == 0) {
        DEBUG_ERROR("Setting GameObject and/or Input GameObject not set. Component disable.");
        setActive(false);
        return;
    }
}

void RType::ChangeKey::onUpdate() {
    if (!_startSelect)
        return;
    auto &keySel = getGameObject().getComponent<KeySelector>();
    Events::Key key;
    if (keySel.keySelected(key)) {
        _startSelect = false;
        PlayerPrefs::setInt(_prefName, key.get());
        _prefName = "";
        displaySettings();
    }
}

void RType::ChangeKey::startSelect(std::string const &prefName) {
    if (prefName == "") {
        DEBUG_ERROR("You can't select a key without set a name to PlayerPrefs");
        return;
    }
    _startSelect = true;
    _prefName = prefName;
    auto &keySel = getGameObject().getComponent<KeySelector>();
    keySel.selectKey();
    displayInputs();
}

void RType::ChangeKey::displayInputs() {
    std::shared_ptr<GameObject> go;
    std::shared_ptr<GameObject> goS;
    try {
        go = getScene().getGameObject(_idInput);
    } catch (...) {
        DEBUG_ERROR("Failed to get GameObject for selected inputs");
        return;
    }

    try {
        goS = getScene().getGameObject(_idSettings);
    } catch (...) {
        DEBUG_ERROR("Failed to get GameObject for selected settings");
        return;
    }
    go->setActive(true);
    goS->setActive(false);
}

void RType::ChangeKey::displaySettings() {
    KAP_DEBUG_LOG("DISPLAYING SETTINGS");
    std::shared_ptr<GameObject> go;
    std::shared_ptr<GameObject> goS;
    try {
        go = getScene().getGameObject(_idInput);
    } catch (...) {
        DEBUG_ERROR("Failed to get GameObject for selected inputs");
        return;
    }

    try {
        goS = getScene().getGameObject(_idSettings);
    } catch (...) {
        DEBUG_ERROR("Failed to get GameObject for selected settings");
        return;
    }
    go->setActive(false);
    goS->setActive(true);
}
