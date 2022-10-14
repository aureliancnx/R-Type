#include "BoubouleEnemy.hpp"
#include "Bullet/Bullet.hpp"

using namespace RType;

BoubouleEnemy::BoubouleEnemy(std::shared_ptr<KapEngine::GameObject> _gameObject) : KapMirror::NetworkComponent(_gameObject, "BoubouleEnemy") {
    addRequireComponent("Image");
}

void BoubouleEnemy::setLife(int _life) {
    life = _life;
}

void BoubouleEnemy::onFixedUpdate() {
    auto& transform = getTransform();

    transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-1.0f, 0, 0));

    auto time = KapMirror::NetworkTime::localTime();
    if (time - lastShootTime > 3000) {
        lastShootTime = time;
        shoot();
    }

    if (transform.getWorldPosition().getX() < -100) {
        getGameObject().destroy();
    }
}

void BoubouleEnemy::shoot() {
    KapEngine::Tools::Vector3 pos = getTransform().getLocalPosition() + KapEngine::Tools::Vector3(70, 15, 0);

    if (getTransform().getWorldPosition().getX() <= 0) {
        return;
    }

    if (isLocal()) {
        auto& scene = getGameObject().getScene();
        std::shared_ptr<KapEngine::GameObject> bullet;
        getGameObject().getEngine().getPrefabManager()->instantiatePrefab("Bullet", scene, bullet);
        bullet->getComponent<KapEngine::Transform>().setPosition(pos);
        bullet->getComponent<Bullet>().setDirection(Bullet::Direction::LEFT);
    } else if (isServer()) {
        std::shared_ptr<KapEngine::GameObject> bullet;
        getServer()->spawnObject("Bullet", pos, [this](std::shared_ptr<KapEngine::GameObject> go) {
            go->getComponent<Bullet>().setDirection(Bullet::Direction::LEFT);
        }, bullet);
    }
}

void BoubouleEnemy::onTriggerEnter(std::shared_ptr<KapEngine::GameObject> other) {
    if (isClient()) {
        return;
    }

    KAP_DEBUG_LOG("BoubouleEnemy::onTriggerEnter: " + other->getName());

    if (other->getName() == "Bullet") {
        life -= 1;
        if (life <= 0) {
            getGameObject().destroy();
        }
    }
}

void BoubouleEnemy::customPayloadSerialize(KapMirror::NetworkWriter& writer) {
    writer.write(life);
}

void BoubouleEnemy::customPayloadDeserialize(KapMirror::NetworkReader& reader) {
    life = reader.read<int>();
}
