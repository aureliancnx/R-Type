#include "Bullet.hpp"

using namespace RType;

Bullet::Bullet(std::shared_ptr<KapEngine::GameObject> gameObject) : Component(gameObject, "Bullet") {
    addRequireComponent("Image");
}

void Bullet::onFixedUpdate() {
    auto& transform = getTransform();

    transform.getLocalPosition().setX(transform.getLocalPosition().getX() + 0.4f);
}
