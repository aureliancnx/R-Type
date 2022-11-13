#include "PlayerSkin.hpp"

using namespace RType;

PlayerSkin::PlayerSkin(std::shared_ptr<KapEngine::GameObject> _gameObject) : KapMirror::NetworkComponent(_gameObject, "PlayerSkin") {
    addRequireComponent("Image");
}

void PlayerSkin::setSkinId(int _skinId) {
    if (_skinId < 1 || _skinId > 5) {
        KapEngine::Debug::error("Invalid player skin id");
        return;
    }

    skinId = _skinId;

    try {
        auto &image = getGameObject().getComponent<KapEngine::UI::Image>();
        image.setPathSprite("Assets/Textures/Ship/ship_" + std::to_string(skinId) + ".png");
    } catch (...) { KAP_DEBUG_ERROR("PlayerSkin::setSkinId: Image component not found"); }
}

int PlayerSkin::getSkinId() const { return skinId; }

void PlayerSkin::onStart() {
    if (isLocal() && KapEngine::PlayerPrefs::hasKey("shipID")) {
        setSkinId(KapEngine::PlayerPrefs::getInt("shipID"));
    }
}

void PlayerSkin::serialize(KapMirror::NetworkWriter &writer) { writer.write(skinId); }

void PlayerSkin::deserialize(KapMirror::NetworkReader &reader) { skinId = reader.read<int>(); }

void PlayerSkin::onObjectUpdate() {
    if (isClient()) {
        setSkinId(skinId);
    }
}
