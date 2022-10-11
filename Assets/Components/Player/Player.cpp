#include "Player.hpp"

using namespace RType;

Player::Player(std::shared_ptr<KapEngine::GameObject> _gameObject) : KapMirror::NetworkComponent(_gameObject, "Player") {
    addRequireComponent("Image");
}

void Player::setLocalPlayer(bool _isLocalPlayer) {
    isLocalPlayer = _isLocalPlayer;
}

void Player::onUpdate() {
    if (isLocalPlayer || isServer()) {
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

        if (getInput().getKeyDown(KapEngine::Events::Key::SPACE)) {
            shoot();
        }
    }
}

void Player::shoot() {
    if (isLocalPlayer) {
        auto& scene = getGameObject().getScene();
        std::shared_ptr<KapEngine::GameObject> bullet;
        getGameObject().getEngine().getPrefabManager()->instantiatePrefab("Bullet", scene, bullet);
        bullet->getComponent<KapEngine::Transform>().setPosition(getTransform().getLocalPosition());
    } else if (isServer()) {
        std::shared_ptr<KapEngine::GameObject> bullet;
        getServer()->spawnObject("Bullet", getTransform().getLocalPosition(), bullet);
    }
}
