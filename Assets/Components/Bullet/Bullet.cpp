#include "Bullet.hpp"

using namespace RType;

Bullet::Bullet(std::shared_ptr<KapEngine::GameObject> gameObject)
    : KapMirror::NetworkComponent(gameObject, "Bullet"), engine(gameObject->getEngine()) {
    addRequireComponent("Image");
    direction = Direction::RIGHT;
}

void Bullet::setDirection(Direction _direction) { direction = _direction; }

Bullet::Direction Bullet::getDirection() const { return direction; }

void Bullet::onStart() { initialX = getTransform().getWorldPosition().getX(); }

void Bullet::onFixedUpdate() {
    auto &transform = getTransform();
    KapEngine::Tools::Vector3 nPos = transform.getWorldPosition();

    float xMove = 0.0f;
    // cross calcul for 1s bullet move x value
    /**
     * | 1 | Y |
     * +---+---+
     * | X |X*Y|
     */
    xMove = (speed / 10000) * (float) engine.getElapsedTime().asMicroSecond();

    if (direction == Direction::RIGHT) {
        nPos.setX(nPos.getX() + xMove);
    } else if (direction == Direction::LEFT) {
        nPos.setX(nPos.getX() - xMove);
    }

    transform.setPosition(nPos);

    if (nPos.getX() > initialX + 1280 || nPos.getX() < 0) {
        getGameObject().destroy();
    }
}

void Bullet::serialize(KapMirror::NetworkWriter &writer) { writer.write(direction); }

void Bullet::deserialize(KapMirror::NetworkReader &reader) { direction = reader.read<Direction>(); }
