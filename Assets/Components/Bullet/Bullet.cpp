#include "Bullet.hpp"

using namespace RType;

Bullet::Bullet(std::shared_ptr<KapEngine::GameObject> gameObject) : Component(gameObject, "Bullet") {
    addRequireComponent("Image");
}

void Bullet::onStart() {
    initialX = getTransform().getLocalPosition().getX();
}

void Bullet::onUpdate() {
    auto& transform = getTransform();

    KapEngine::Tools::Vector3 nPos = transform.getLocalPosition();
    nPos.setX(nPos.getX() + speed);

    transform.setPosition(nPos);

    if (nPos.getX() > initialX + 500) {
        getTransform().getParent()->destroy();
    }
}
