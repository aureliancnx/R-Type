//
// Created by leq on 12/11/22.
//

#include "ConvertEnum.hpp"
#include "Keys/UpdateStartGameKeys.hpp"
#include "KapUI/KapUI.hpp"

using namespace RType;

ConvertEnum::ConvertEnum(std::shared_ptr<GameObject> go, std::string prefsKey, std::string prefix, KapEngine::Events::Key::EKey basicKey)
    : Component(go, "Convert Enum to String"), _prefix(prefix), _basicKey(basicKey), _prefKey(prefsKey) {}

ConvertEnum::~ConvertEnum() {}

void ConvertEnum::onAwake() {}

void ConvertEnum::onUpdate() { setTextKey(); }

void ConvertEnum::setTextKey() {

    auto &btn = getGameObject().getComponent<KapEngine::UI::Button>();

    if (KapEngine::PlayerPrefs::hasKey(_prefKey)) {
        auto key = KapEngine::PlayerPrefs::getInt(_prefKey);
        btn.setText(_prefix + KeyToString(key));
    } else {
        KapEngine::Events::Key key;
        key = _basicKey;
        btn.setText(_prefix + key.toString());
    }
}

std::string ConvertEnum::KeyToString(int e) {
    if (KapEngine::Events::Key::intInEnum(e)) {
        KapEngine::Events::Key key;
        key = (KapEngine::Events::Key::EKey) e;
        return key.toString();
    } else {
        return "Unknown";
    }
}
