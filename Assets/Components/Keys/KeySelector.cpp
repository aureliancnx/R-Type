#include "KeySelector.hpp"

using namespace RType;

KeySelector::KeySelector(std::shared_ptr<KapEngine::GameObject> go) : Component(go, "KeySelector") {}

void KeySelector::onUpdate() {
    if (_check == false)
        return;
    for (int i = KapEngine::Events::Key::minValue(); i < KapEngine::Events::Key::maxValue(); i++) {
        if (KapEngine::Events::Key::intInEnum(i)) {
            KapEngine::Events::Key toCheck;
            toCheck = (KapEngine::Events::Key::EKey) i;
            if (getInput().getKeyDown(toCheck)) {
                _selected = toCheck;
                _check = false;
                return;
            }
        }
    }
}

bool KeySelector::keySelected(KapEngine::Events::Key &key) {
    if (_selected == KapEngine::Events::Key::UNKNOWN)
        return false;
    _check = false;
    key = _selected;
    return true;
}

void KeySelector::selectKey() {
    _selected = KapEngine::Events::Key::UNKNOWN;
    _check = true;
}
