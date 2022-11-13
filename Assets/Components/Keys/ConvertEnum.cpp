//
// Created by leq on 12/11/22.
//

#include "ConvertEnum.hpp"
#include "Keys/UpdateStartGameKeys.hpp"


using namespace RType;

ConvertEnum::ConvertEnum(std::shared_ptr<GameObject> go) : Component(go, "Convert Enum to String") { }

ConvertEnum::~ConvertEnum() {}

void ConvertEnum::onAwake() {

}

void ConvertEnum::onUpdate() {
    setTextKey();
}

void ConvertEnum::setTextKey() {
    try {
        auto children = _buttonKeyBoard->getComponent<KapEngine::Transform>().getChildren();

        for (auto &i : children) {
            if (i->hasComponent<KapEngine::UI::Button>() && i->getName() == "ButtonInput1") {
                auto &txt = i->getComponent<KapEngine::UI::Text>();
                txt.setText("Move Up : " + KeyToString(KapEngine::PlayerPrefs::getInt("upInput")));
            }
            if (i->hasComponent<KapEngine::UI::Button>() && i->getName() == "ButtonInput2") {
                auto &txt = i->getComponent<KapEngine::UI::Text>();
                txt.setText("Move Down : " + KeyToString(KapEngine::PlayerPrefs::getInt("downInput")));
            }
            if (i->hasComponent<KapEngine::UI::Button>() && i->getName() == "ButtonInput3") {
                auto &txt = i->getComponent<KapEngine::UI::Text>();
                txt.setText("Move Left : " + KeyToString(KapEngine::PlayerPrefs::getInt("leftInput")));
            }
            if (i->hasComponent<KapEngine::UI::Button>() && i->getName() == "ButtonInput4") {
                auto &txt = i->getComponent<KapEngine::UI::Text>();
                txt.setText("Move Right : " + KeyToString(KapEngine::PlayerPrefs::getInt("rightInput")));
            }
            if (i->hasComponent<KapEngine::UI::Button>() && i->getName() == "ButtonInput5") {
                auto &txt = i->getComponent<KapEngine::UI::Text>();
                txt.setText("Shoot : " + KeyToString(KapEngine::PlayerPrefs::getInt("shootInput")));
            }
            if (i->hasComponent<KapEngine::UI::Button>() && i->getName() == "ButtonInput6") {
                auto &txt = i->getComponent<KapEngine::UI::Text>();
                txt.setText("Debug :" + KeyToString(KapEngine::PlayerPrefs::getInt("debugInput")));
            }

        }
    } catch (const std::exception& e) { KAP_DEBUG_ERROR("Failed to update KeyBoard button " + std::string(e.what())); }
}