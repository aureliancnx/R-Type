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
        auto& image = getGameObject().getComponent<KapEngine::UI::Image>();
        image.setPathSprite("Assets/Textures/Ship/ship_" + std::to_string(skinId) + ".png");
    } catch (...) {
        KAP_DEBUG_ERROR("PlayerSkin::setSkinId: Image component not found");
    }
}

void PlayerSkin::onStartClient() {
    KAP_DEBUG_LOG("Player set skin id " + std::to_string(skinId));
    setSkinId(skinId);
}

void PlayerSkin::customPayloadSerialize(KapMirror::NetworkWriter& writer) {
    writer.write(skinId);
}

void PlayerSkin::customPayloadDeserialize(KapMirror::NetworkReader& reader) {
    skinId = reader.read<int>();
}
