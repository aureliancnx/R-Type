#include "TentaclesBossEnemy.hpp"
#include "Bullet/Bullet.hpp"

using namespace RType;

TentaclesBossEnemy::TentaclesBossEnemy(std::shared_ptr<KapEngine::GameObject> _gameObject)
    : KapMirror::NetworkComponent(_gameObject, "TentaclesBossEnemy") {
    addRequireComponent("Image");
}

void TentaclesBossEnemy::setLife(int _life) { life = _life; }

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
        auto& scene = getScene();
        std::shared_ptr<KapEngine::GameObject> bullet;
        getEngine().getPrefabManager()->instantiatePrefab("Bullet", scene, bullet);
        bullet->getComponent<KapEngine::Transform>().setPosition(pos);
        bullet->getComponent<Bullet>().setDirection(Bullet::Direction::LEFT);
    } else if (isServer()) {
        std::shared_ptr<KapEngine::GameObject> bullet;
        getServer()->spawnObject(
            "Bullet", pos,
            [this](std::shared_ptr<KapEngine::GameObject> go) { go->getComponent<Bullet>().setDirection(Bullet::Direction::LEFT); },
            bullet);
    }
}

void TentaclesBossEnemy::onTriggerEnter(std::shared_ptr<KapEngine::GameObject> other) {
    if (isClient()) {
        return;
    }

    collidedObjects.push_back(other);
}

void TentaclesBossEnemy::serialize(KapMirror::NetworkWriter& writer) { writer.write(life); }

void TentaclesBossEnemy::deserialize(KapMirror::NetworkReader& reader) { life = reader.read<int>(); }

void TentaclesBossEnemy::onSceneUpdated() {
    if (isClient()) {
        return;
    }
    for (auto& other : collidedObjects) {
        if (other.use_count() > 1 && other->getName() == "Bullet Player") {
            life -= 1;
            if (life <= 0) {
                if (isLocal()) {
                    getGameObject().destroy();
                } else {
                    getServer()->destroyObject(getScene().getGameObject(getGameObject().getId()));
                }
            }
            if (isLocal()) {
                std::shared_ptr<KapEngine::GameObject> explosion;
                if (getEngine().getPrefabManager()->instantiatePrefab("BulletExplode", getScene(),
                                                                                      explosion)) {
                    explosion->getComponent<KapEngine::Transform>().setPosition(
                        other->getComponent<KapEngine::Transform>().getWorldPosition());
                } else {
                    KAP_DEBUG_ERROR("Cannot instantiate prefab BulletExplode");
                }
                other->destroy();
            } else if (isServer()) {
                getServer()->destroyObject(other);
            }
        } else if (other.use_count() > 1 && other->getName() == "Missile Player") {
            life -= 10;
            if (life <= 0) {
                if (isLocal()) {
                    getGameObject().destroy();
                } else {
                    getServer()->destroyObject(getScene().getGameObject(getGameObject().getId()));
                }
            }
            if (isLocal()) {
                std::shared_ptr<KapEngine::GameObject> explosion;
                if (getEngine().getPrefabManager()->instantiatePrefab("MissileExplode", getScene(),
                                                                                      explosion)) {
                    explosion->getComponent<KapEngine::Transform>().setPosition(
                        other->getComponent<KapEngine::Transform>().getWorldPosition());
                } else {
                    KAP_DEBUG_ERROR("Cannot instantiate prefab MissiletExplode");
                }
                other->destroy();
            } else if (isServer()) {
                getServer()->destroyObject(other);
            }
        }
    }
    collidedObjects.clear();
}
