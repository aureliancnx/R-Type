/*
** EPITECH PROJECT, 2022
** RType2
** File description:
** Bullet
*/

#include "Bullet.hpp"

using namespace RType;
using namespace KapEngine;

Bullet::Bullet(std::shared_ptr<GameObject> go) : KapMirror::Experimental::NetworkComponent(go, "Bullet") {
}

void Bullet::onStart() {
    initialX = getGameObject().getComponent<Transform>().getLocalPosition().getX();
}

void Bullet::onUpdate() {
    auto& transform = getGameObject().getComponent<KapEngine::Transform>();

    Tools::Vector3 nPos = transform.getLocalPosition();
    nPos.setX(nPos.getX() + speed);

    transform.setPosition(nPos);

    if (nPos.getX() > initialX + 500) {
        getGameObject().destroy();
    }
}

