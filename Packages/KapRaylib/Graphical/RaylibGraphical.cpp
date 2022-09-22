/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RaylibGraphical
*/

#include "RaylibGraphical.hpp"
#include "Vectors.hpp"
#include "Debug.hpp"
#include "Key.hpp"

KapEngine::Graphical::RaylibGraphical::RaylibGraphical(GraphicalLibManager &manager) : GraphicalLib("raylib", manager) {

    Tools::Vector2 size = manager.getEngine().getScreenSize();

    raylib = std::make_unique<RaylibEncapsulation>(
        size.getX(),
        size.getY(),
        manager.getEngine().getGameName(),
        manager.getEngine().getMaxFps()
    );

}

KapEngine::Graphical::RaylibGraphical::~RaylibGraphical() {
    raylib->closeWindow();
}

void KapEngine::Graphical::RaylibGraphical::clearCache() {

}

void KapEngine::Graphical::RaylibGraphical::stopDisplay() {
    raylib->closeWindow();
}

void KapEngine::Graphical::RaylibGraphical::startDisplay() {
    raylib->openWindow();
    Debug::log("Use " + getName());
}

void KapEngine::Graphical::RaylibGraphical::clear() {
    raylib->startDrawing();
}

void KapEngine::Graphical::RaylibGraphical::display() {
    raylib->stopDrawing();
}

void KapEngine::Graphical::RaylibGraphical::getEvents() {

    //check close window
    if (raylib->windownShouldClose()) {
        manager.getEngine().stop();
        return;
    }

    //check inputs
    Events::Key _tmpKey;
    _tmpKey = Events::Key::UNKNOWN;

    // give last new pressed input to pressed input
    for (std::size_t i = 0; i < _newPressedInputs.size(); i++) {
        _pressedInputs.push_back(_newPressedInputs[i]);
    }

    //clear useless input
    _newPressedInputs.clear();
    _releasedInputs.clear();

    _tmpKey = toKey((KeyboardKey)raylib->getKeyPressed());
    //check key got
    if (_tmpKey != Events::Key::UNKNOWN && !keyAlreadyInList(_tmpKey)) {
        _newPressedInputs.push_back(_tmpKey);
    }

    //check mouse inputs
    for (size_t i = 0; i < 7; i++) {
        _tmpKey = toKey((MouseButton) i);
        if (raylib->isMouseButtonPressed(i) && !keyAlreadyInList(_tmpKey)) {
            _newPressedInputs.push_back(_tmpKey);
        }
    }

    //check gamepad inputs
    for (std::size_t i = Events::Key::GAMEPAD_LEFT_FACE_UP; i <= (std::size_t)Events::Key::GAMEPAD1_RIGHT_THUMB; i++) {
        if (isGamepadButtonPressedEngine((Events::Key::EKey)i)) {
            Events::Key k;
            k = (Events::Key::EKey)i;
            _newPressedInputs.push_back(k);
        }
    }

    //clear inputs no more pressed
    for (std::size_t i = 0; i < _pressedInputs.size(); i++) {
        Events::Key _k = _pressedInputs[i];
        std::vector<Events::Key>::iterator it = _pressedInputs.begin();
        if (_k.isKeyboardKey() && raylib->isKeyReleased(toRaylibKey(_k))) {
            _releasedInputs.push_back(_k);
            _pressedInputs.erase(it + i);
            i--;
        } else if (_k.isMouseKey() && raylib->isMouseButtonReleased(toRaylibKey(_k))) {
            _releasedInputs.push_back(_k);
            _pressedInputs.erase(it + i);
            i--;
        } else if (_k.isGamepadKey()) {
            if (isGamepadButtonReleasedEngine(_k)) {
                _releasedInputs.push_back(_k);
                _pressedInputs.erase(it + i);
                i--;
            }
        }
    }
}

bool KapEngine::Graphical::RaylibGraphical::keyAlreadyInList(Events::Key key) {
    for (std::size_t i = 0; i < _pressedInputs.size(); i++) {
        if (_pressedInputs[i] == key)
            return true;
    }
    return false;
}

float KapEngine::Graphical::RaylibGraphical::getJoystikValue(int gamepadId, int joystickId) {
    return raylib->getGamepadJoystickValue(gamepadId, joystickId);
}

KapEngine::Events::Key::EKey KapEngine::Graphical::RaylibGraphical::toKey(KeyboardKey _key) {
    int val = (int) _key;

    if (_key == KEY_NULL)
        return Events::Key::UNKNOWN;
    if (!Events::Key::intInEnum(val))
        return Events::Key::UNKNOWN;
    return (Events::Key::EKey) val;
}

KapEngine::Events::Key::EKey KapEngine::Graphical::RaylibGraphical::toKey(MouseButton _key) {
    switch (_key) {
        case MOUSE_BUTTON_BACK:
            return Events::Key::MOUSE_BACK;
        case MOUSE_BUTTON_EXTRA:
            return Events::Key::MOUSE_EXTRA;
        case MOUSE_BUTTON_FORWARD:
            return Events::Key::MOUSE_FORWARD;
        case MOUSE_BUTTON_LEFT:
            return Events::Key::MOUSE_LEFT;
        case MOUSE_BUTTON_MIDDLE:
            return Events::Key::MOUSE_MIDDLE;
        case MOUSE_BUTTON_RIGHT:
            return Events::Key::MOUSE_RIGHT;
        case MOUSE_BUTTON_SIDE:
            return Events::Key::MOUSE_SIDE;
        default:
            return Events::Key::UNKNOWN;
    }
}

KapEngine::Events::Key::EKey KapEngine::Graphical::RaylibGraphical::toKey(GamepadButton _key, int id) {
    Events::Key::EKey res;
    switch (_key) {
        case GAMEPAD_BUTTON_LEFT_FACE_UP:
            res = Events::Key::GAMEPAD_LEFT_FACE_UP;
        case GAMEPAD_BUTTON_LEFT_FACE_DOWN:
            res = Events::Key::GAMEPAD_LEFT_FACE_DOWN;
        case GAMEPAD_BUTTON_LEFT_FACE_LEFT:
            res = Events::Key::GAMEPAD_LEFT_FACE_LEFT;
        case GAMEPAD_BUTTON_LEFT_FACE_RIGHT:
            res = Events::Key::GAMEPAD_LEFT_FACE_RIGHT;
        case GAMEPAD_BUTTON_LEFT_THUMB:
            res = Events::Key::GAMEPAD_LEFT_THUMB;
        case GAMEPAD_BUTTON_LEFT_TRIGGER_1:
            res = Events::Key::GAMEPAD_LEFT_TRIGGER_1;
        case GAMEPAD_BUTTON_LEFT_TRIGGER_2:
            res = Events::Key::GAMEPAD_LEFT_TRIGGER_2;
        case GAMEPAD_BUTTON_MIDDLE_LEFT:
            res = Events::Key::GAMEPAD_MIDDLE_LEFT;
        case GAMEPAD_BUTTON_MIDDLE:
            res = Events::Key::GAMEPAD_MIDDLE;
        case GAMEPAD_BUTTON_MIDDLE_RIGHT:
            res = Events::Key::GAMEPAD_MIDDLE_RIGHT;
        case GAMEPAD_BUTTON_RIGHT_FACE_UP:
            res = Events::Key::GAMEPAD_RIGHT_FACE_UP;
        case GAMEPAD_BUTTON_RIGHT_FACE_DOWN:
            res = Events::Key::GAMEPAD_RIGHT_FACE_DOWN;
        case GAMEPAD_BUTTON_RIGHT_FACE_LEFT:
            res = Events::Key::GAMEPAD_RIGHT_FACE_LEFT;
        case GAMEPAD_BUTTON_RIGHT_FACE_RIGHT:
            res = Events::Key::GAMEPAD_RIGHT_FACE_RIGHT;
        case GAMEPAD_BUTTON_RIGHT_THUMB:
            res = Events::Key::GAMEPAD_RIGHT_THUMB;
        case GAMEPAD_BUTTON_RIGHT_TRIGGER_1:
            res = Events::Key::GAMEPAD_RIGHT_TRIGGER_1;
        case GAMEPAD_BUTTON_RIGHT_TRIGGER_2:
            res = Events::Key::GAMEPAD_RIGHT_TRIGGER_2;
        default:
            res = Events::Key::UNKNOWN;
    }
    if (res == Events::Key::UNKNOWN)
        return res;
    if (id == 0)
        return (Events::Key::EKey)((int)res + (int)Events::Key::GAMEPAD0_LEFT_FACE_UP);
    if (id == 1)
        return (Events::Key::EKey)((int)res + (int)Events::Key::GAMEPAD1_LEFT_FACE_UP);
    return res;
}

int KapEngine::Graphical::RaylibGraphical::toRaylibKey(Events::Key key)
{
    if (key.isKeyboardKey())
        return key.get();
    if (key.isMouseKey()) {
        switch (key.get()) {
            case Events::Key::MOUSE_BACK:
                return  MOUSE_BUTTON_BACK;
            case Events::Key::MOUSE_EXTRA:
                return MOUSE_BUTTON_EXTRA;
            case Events::Key::MOUSE_FORWARD:
                return MOUSE_BUTTON_FORWARD;
            case Events::Key::MOUSE_LEFT:
                return MOUSE_BUTTON_LEFT;
            case Events::Key::MOUSE_MIDDLE:
                return MOUSE_BUTTON_MIDDLE;
            case Events::Key::MOUSE_RIGHT:
                return MOUSE_BUTTON_RIGHT;
            case Events::Key::MOUSE_SIDE:
                return MOUSE_BUTTON_SIDE;
            default:
                return 0;
        }
    }
    if (key.isGamepadKey()) {
        switch (key.get()) {
            case Events::Key::GAMEPAD_LEFT_FACE_UP:
                return GAMEPAD_BUTTON_LEFT_FACE_UP;
            case Events::Key::GAMEPAD_LEFT_FACE_DOWN:
                return GAMEPAD_BUTTON_LEFT_FACE_DOWN;
            case Events::Key::GAMEPAD_LEFT_FACE_LEFT:
                return GAMEPAD_BUTTON_LEFT_FACE_LEFT;
            case Events::Key::GAMEPAD_LEFT_FACE_RIGHT:
                return GAMEPAD_BUTTON_LEFT_FACE_RIGHT;
            case Events::Key::GAMEPAD_LEFT_THUMB:
                return GAMEPAD_BUTTON_LEFT_THUMB;
            case Events::Key::GAMEPAD_LEFT_TRIGGER_1:
                return GAMEPAD_BUTTON_LEFT_TRIGGER_1;
            case Events::Key::GAMEPAD_LEFT_TRIGGER_2:
                return GAMEPAD_BUTTON_LEFT_TRIGGER_2;
            case Events::Key::GAMEPAD_MIDDLE_LEFT:
                return GAMEPAD_BUTTON_MIDDLE_LEFT;
            case Events::Key::GAMEPAD_MIDDLE:
                return GAMEPAD_BUTTON_MIDDLE;
            case Events::Key::GAMEPAD_MIDDLE_RIGHT:
                return GAMEPAD_BUTTON_MIDDLE_RIGHT;
            case Events::Key::GAMEPAD_RIGHT_FACE_UP:
                return GAMEPAD_BUTTON_RIGHT_FACE_UP;
            case Events::Key::GAMEPAD_RIGHT_FACE_DOWN:
                return GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
            case Events::Key::GAMEPAD_RIGHT_FACE_LEFT:
                return GAMEPAD_BUTTON_RIGHT_FACE_LEFT;
            case Events::Key::GAMEPAD_RIGHT_FACE_RIGHT:
                return GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;
            case Events::Key::GAMEPAD_RIGHT_THUMB:
                return GAMEPAD_BUTTON_RIGHT_THUMB;
            case Events::Key::GAMEPAD_RIGHT_TRIGGER_1:
                return GAMEPAD_BUTTON_RIGHT_TRIGGER_1;
            case Events::Key::GAMEPAD_RIGHT_TRIGGER_2:
                return GAMEPAD_BUTTON_RIGHT_TRIGGER_2;
            case Events::Key::GAMEPAD1_LEFT_FACE_UP:
                return GAMEPAD_BUTTON_LEFT_FACE_UP;
            case Events::Key::GAMEPAD1_LEFT_FACE_DOWN:
                return GAMEPAD_BUTTON_LEFT_FACE_DOWN;
            case Events::Key::GAMEPAD1_LEFT_FACE_LEFT:
                return GAMEPAD_BUTTON_LEFT_FACE_LEFT;
            case Events::Key::GAMEPAD1_LEFT_FACE_RIGHT:
                return GAMEPAD_BUTTON_LEFT_FACE_RIGHT;
            case Events::Key::GAMEPAD1_LEFT_THUMB:
                return GAMEPAD_BUTTON_LEFT_THUMB;
            case Events::Key::GAMEPAD1_LEFT_TRIGGER_1:
                return GAMEPAD_BUTTON_LEFT_TRIGGER_1;
            case Events::Key::GAMEPAD1_LEFT_TRIGGER_2:
                return GAMEPAD_BUTTON_LEFT_TRIGGER_2;
            case Events::Key::GAMEPAD1_MIDDLE_LEFT:
                return GAMEPAD_BUTTON_MIDDLE_LEFT;
            case Events::Key::GAMEPAD1_MIDDLE:
                return GAMEPAD_BUTTON_MIDDLE;
            case Events::Key::GAMEPAD1_MIDDLE_RIGHT:
                return GAMEPAD_BUTTON_MIDDLE_RIGHT;
            case Events::Key::GAMEPAD1_RIGHT_FACE_UP:
                return GAMEPAD_BUTTON_RIGHT_FACE_UP;
            case Events::Key::GAMEPAD1_RIGHT_FACE_DOWN:
                return GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
            case Events::Key::GAMEPAD1_RIGHT_FACE_LEFT:
                return GAMEPAD_BUTTON_RIGHT_FACE_LEFT;
            case Events::Key::GAMEPAD1_RIGHT_FACE_RIGHT:
                return GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;
            case Events::Key::GAMEPAD1_RIGHT_THUMB:
                return GAMEPAD_BUTTON_RIGHT_THUMB;
            case Events::Key::GAMEPAD1_RIGHT_TRIGGER_1:
                return GAMEPAD_BUTTON_RIGHT_TRIGGER_1;
            case Events::Key::GAMEPAD1_RIGHT_TRIGGER_2:
                return GAMEPAD_BUTTON_RIGHT_TRIGGER_2;
            case Events::Key::GAMEPAD0_LEFT_FACE_UP:
                return GAMEPAD_BUTTON_LEFT_FACE_UP;
            case Events::Key::GAMEPAD0_LEFT_FACE_DOWN:
                return GAMEPAD_BUTTON_LEFT_FACE_DOWN;
            case Events::Key::GAMEPAD0_LEFT_FACE_LEFT:
                return GAMEPAD_BUTTON_LEFT_FACE_LEFT;
            case Events::Key::GAMEPAD0_LEFT_FACE_RIGHT:
                return GAMEPAD_BUTTON_LEFT_FACE_RIGHT;
            case Events::Key::GAMEPAD0_LEFT_THUMB:
                return GAMEPAD_BUTTON_LEFT_THUMB;
            case Events::Key::GAMEPAD0_LEFT_TRIGGER_1:
                return GAMEPAD_BUTTON_LEFT_TRIGGER_1;
            case Events::Key::GAMEPAD0_LEFT_TRIGGER_2:
                return GAMEPAD_BUTTON_LEFT_TRIGGER_2;
            case Events::Key::GAMEPAD0_MIDDLE_LEFT:
                return GAMEPAD_BUTTON_MIDDLE_LEFT;
            case Events::Key::GAMEPAD0_MIDDLE:
                return GAMEPAD_BUTTON_MIDDLE;
            case Events::Key::GAMEPAD0_MIDDLE_RIGHT:
                return GAMEPAD_BUTTON_MIDDLE_RIGHT;
            case Events::Key::GAMEPAD0_RIGHT_FACE_UP:
                return GAMEPAD_BUTTON_RIGHT_FACE_UP;
            case Events::Key::GAMEPAD0_RIGHT_FACE_DOWN:
                return GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
            case Events::Key::GAMEPAD0_RIGHT_FACE_LEFT:
                return GAMEPAD_BUTTON_RIGHT_FACE_LEFT;
            case Events::Key::GAMEPAD0_RIGHT_FACE_RIGHT:
                return GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;
            case Events::Key::GAMEPAD0_RIGHT_THUMB:
                return GAMEPAD_BUTTON_RIGHT_THUMB;
            case Events::Key::GAMEPAD0_RIGHT_TRIGGER_1:
                return GAMEPAD_BUTTON_RIGHT_TRIGGER_1;
            case Events::Key::GAMEPAD0_RIGHT_TRIGGER_2:
                return GAMEPAD_BUTTON_RIGHT_TRIGGER_2;
            default:
                return 0;
        }
    }
    return 0;
}

int KapEngine::Graphical::RaylibGraphical::toRaylibKey(Events::Key::EKey key)
{
    Events::Key k;
    k = key;
    return toRaylibKey(k);
}

bool KapEngine::Graphical::RaylibGraphical::isGamepadButtonReleasedEngine(Events::Key key)
{
    if (!key.isGamepadKey())
        return false;

    if (key.get() >= Events::Key::GAMEPAD_LEFT_FACE_UP && key.get() <= Events::Key::GAMEPAD_RIGHT_THUMB) {
        if (raylib->isGamepadButtonReleased(0, toRaylibKey(key)))
            return true;
        if (raylib->isGamepadButtonReleased(1, toRaylibKey(key)))
            return true;
    }
    if (key.get() >= Events::Key::GAMEPAD0_LEFT_FACE_UP && key.get() <= Events::Key::GAMEPAD0_RIGHT_THUMB)
        return raylib->isGamepadButtonReleased(0, toRaylibKey(key));
    if (key.get() >= Events::Key::GAMEPAD1_LEFT_FACE_UP && key.get() <= Events::Key::GAMEPAD1_RIGHT_THUMB)
        return raylib->isGamepadButtonReleased(1, toRaylibKey(key));
    return false;
}

bool KapEngine::Graphical::RaylibGraphical::isGamepadButtonPressedEngine(Events::Key key)
{
    if (!key.isGamepadKey())
        return false;

    if (key.get() >= Events::Key::GAMEPAD_LEFT_FACE_UP && key.get() <= Events::Key::GAMEPAD_RIGHT_THUMB) {
        if (raylib->isGamepadButtonPressed(0, toRaylibKey(key)))
            return true;
        if (raylib->isGamepadButtonPressed(1, toRaylibKey(key)))
            return true;
    }
    if (key.get() >= Events::Key::GAMEPAD0_LEFT_FACE_UP && key.get() <= Events::Key::GAMEPAD0_RIGHT_THUMB)
        return raylib->isGamepadButtonPressed(0, toRaylibKey(key));
    if (key.get() >= Events::Key::GAMEPAD1_LEFT_FACE_UP && key.get() <= Events::Key::GAMEPAD1_RIGHT_THUMB)
        return raylib->isGamepadButtonPressed(1, toRaylibKey(key));
    return false;
}

bool KapEngine::Graphical::RaylibGraphical::isGamepadButtonReleasedEngine(Events::Key::EKey key)
{
    Events::Key k;

    k = key;
    return isGamepadButtonReleasedEngine(k);
}

bool KapEngine::Graphical::RaylibGraphical::isGamepadButtonPressedEngine(Events::Key::EKey key)
{
    Events::Key k;

    k = key;
    return isGamepadButtonPressedEngine(k);
}
