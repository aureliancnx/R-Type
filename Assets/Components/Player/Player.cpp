#include "Player.hpp"

using namespace RType;

Player::Player(std::shared_ptr<KapEngine::GameObject> _gameObject) : KapMirror::Experimental::NetworkComponent(_gameObject, "Player") {
    addRequireComponent("Image");
}

void Player::setLocalPlayer(bool _isLocalPlayer) {
    isLocalPlayer = _isLocalPlayer;
}

void Player::onUpdate() {
    if (!isLocalPlayer) {
        return;
    }

    KapEngine::Tools::Vector3 cPos = getTransform().getLocalPosition();

    KapEngine::Tools::Vector3 pos;
    pos.setX(getInput().getAxis("Horizontal"));
    pos.setY(getInput().getAxis("Vertical"));

    if (pos.getX() != 0 || pos.getY() != 0) {
        pos = pos * 3;
        getTransform().setPosition(cPos + pos);
        lastPos = getTransform().getLocalPosition();
    } else {
        getTransform().setPosition(lastPos);
    }
}
