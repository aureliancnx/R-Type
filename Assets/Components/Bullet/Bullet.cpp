#include "Bullet.hpp"

using namespace RType;

Bullet::Bullet(std::shared_ptr<KapEngine::GameObject> gameObject) : KapMirror::NetworkComponent(gameObject, "Bullet") {
    addRequireComponent("Image");
    direction = Direction::RIGHT;
}

void Bullet::setDirection(Direction _direction) {
    direction = _direction;
}

Bullet::Direction Bullet::getDirection() const {
    return direction;
}

void Bullet::onStart() {
    initialX = getTransform().getLocalPosition().getX();
}

void Bullet::onUpdate() {
    auto& transform = getTransform();

    KapEngine::Tools::Vector3 nPos = transform.getLocalPosition();
    if (direction == Direction::RIGHT) {
        nPos.setX(nPos.getX() + speed);
    } else if (direction == Direction::LEFT) {
        nPos.setX(nPos.getX() - speed);
    }

    transform.setPosition(nPos);

    if (nPos.getX() > initialX + 500) {
        getGameObject().destroy();
    }
}

void Bullet::customPayloadSerialize(KapMirror::NetworkWriter& writer) {
    writer.write(direction);
}

void Bullet::customPayloadDeserialize(KapMirror::NetworkReader& reader) {
    direction = reader.read<Direction>();
}
