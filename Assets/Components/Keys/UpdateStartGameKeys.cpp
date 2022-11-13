#include "UpdateStartGameKeys.hpp"

using namespace RType;

UpdateStartGameKeys::UpdateStartGameKeys(std::shared_ptr<KapEngine::GameObject> go)
    : Component(go, "UpdateStartGameKeys"), _baseAxisHor("basicHorizontal"), _baseAxisVert("basicVertical"), _baseAxisShoot("basicShoot"),
      _baseAxisDebug("basicDebug") {

    _baseAxisHor.positiveButton = KapEngine::Events::Key::RIGHT;
    _baseAxisHor.negativeButton = KapEngine::Events::Key::LEFT;

    _baseAxisVert.positiveButton = KapEngine::Events::Key::DOWN;
    _baseAxisVert.negativeButton = KapEngine::Events::Key::UP;

    _baseAxisShoot.positiveButton = KapEngine::Events::Key::MOUSE_LEFT;

    _baseAxisDebug.positiveButton = KapEngine::Events::Key::F3;
}

UpdateStartGameKeys::~UpdateStartGameKeys() {}

void UpdateStartGameKeys::checkInputs() {
    KapEngine::Events::Key up = _baseAxisVert.negativeButton;
    KapEngine::Events::Key down = _baseAxisVert.positiveButton;
    KapEngine::Events::Key left = _baseAxisHor.negativeButton;
    KapEngine::Events::Key right = _baseAxisHor.positiveButton;
    KapEngine::Events::Key shoot = _baseAxisShoot.positiveButton;
    KapEngine::Events::Key debug = _baseAxisDebug.positiveButton;

    setValueSaved("upInput", up);
    setValueSaved("downInput", down);
    setValueSaved("leftInput", left);
    setValueSaved("rightInput", right);
    setValueSaved("shootInput", shoot);
    setValueSaved("debugInput", debug);

    try {
        auto &axis = getInput().getAxisSettings("Vertical");
        axis.positiveButton = down;
        axis.negativeButton = up;
    } catch (...) { KAP_DEBUG_ERROR("Failed to update Vertical axis"); }

    try {
        auto &axis = getInput().getAxisSettings("Horizontal");
        axis.positiveButton = right;
        axis.negativeButton = left;
    } catch (...) { KAP_DEBUG_ERROR("Failed to update Horizontal axis"); }

    try {
        auto &axis = getInput().getAxisSettings("Shoot");
        axis.positiveButton = shoot;
    } catch (...) { KAP_DEBUG_ERROR("Failed to update Shoot axis"); }

    try {
        auto &axis = getInput().getAxisSettings("Debug");
        axis.positiveButton = debug;
    } catch (...) { KAP_DEBUG_ERROR("Failed to update Debug axis"); }
}

bool UpdateStartGameKeys::setValueSaved(std::string const &name, KapEngine::Events::Key &key) {
    if (KapEngine::PlayerPrefs::getString(name) == "")
        return false;
    int val = KapEngine::PlayerPrefs::getInt(name);
    if (!KapEngine::Events::Key::intInEnum(val))
        return false;
    key = (KapEngine::Events::Key::EKey) val;
    return true;
}
