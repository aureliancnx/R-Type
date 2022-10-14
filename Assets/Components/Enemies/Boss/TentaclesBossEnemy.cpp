#include "TentaclesBossEnemy.hpp"
#include "Bullet/Bullet.hpp"

using namespace RType;

TentaclesBossEnemy::TentaclesBossEnemy(std::shared_ptr<KapEngine::GameObject> _gameObject) : KapMirror::NetworkComponent(_gameObject, "TentaclesBossEnemy") {
    addRequireComponent("Image");
}

void TentaclesBossEnemy::setLife(int _life) {
    life = _life;
}

void TentaclesBossEnemy::onFixedUpdate() {
    auto& transform = getTransform();

    if (invert) {
        transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0, -5.0f, 0));
    } else {
        transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0, 5.0f, 0));
    }

    if (transform.getWorldPosition().getY() > 720 - (66 * 2)) {
        invert = true;
    } else if (transform.getWorldPosition().getY() < 0) {
        invert = false;
    }

    auto time = KapMirror::NetworkTime::localTime();
    if (time - lastShootTime > 3000) {
        lastShootTime = time;
        shoot();
    }
}

void TentaclesBossEnemy::shoot() {
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

void TentaclesBossEnemy::onTriggerEnter(std::shared_ptr<KapEngine::GameObject> other) {
    if (isClient()) {
        return;
    }

    KAP_DEBUG_LOG("TentaclesBossEnemy::onTriggerEnter: " + other->getName());

    if (other->getName() == "Bullet") {
        life -= 1;
        if (life <= 0) {
            getGameObject().destroy();
        }
    }
}

void TentaclesBossEnemy::serialize(KapMirror::NetworkWriter& writer) {
    writer.write(life);
}

void TentaclesBossEnemy::deserialize(KapMirror::NetworkReader& reader) {
    life = reader.read<int>();
}
