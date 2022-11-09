#include "EnemyController.hpp"

using namespace RType;

EnemyController::EnemyController(MapScript* _mapScript, std::shared_ptr<KapEngine::GameObject> _gameObject)
    : KapMirror::NetworkComponent(_gameObject, "Enemy"), mapScript(_mapScript) {
    addRequireComponent("Image");
}

void EnemyController::setEnemyName(const std::string& _enemyName) { enemyName = _enemyName; }

void EnemyController::setHp(int _hp) { hp = _hp; }

void EnemyController::onFixedUpdate() {
    auto& transform = getTransform();
    auto newPosition = mapScript->_updateEnemy(enemyName, transform.getLocalPosition());
    transform.setPosition(newPosition);

    // Destroy enemy if his position is out of the screen
    if (transform.getWorldPosition().getX() < -100 || transform.getWorldPosition().getX() > 1280 + 200) {
        getGameObject().destroy();
    }
    if (transform.getWorldPosition().getY() < -100 || transform.getWorldPosition().getY() > 720 + 200) {
        getGameObject().destroy();
    }
}

void EnemyController::onTriggerEnter(std::shared_ptr<KapEngine::GameObject> other) {
    if (isClient()) {
        return;
    }

    collidedObjects.push_back(other);
}

void EnemyController::onSceneUpdated() {
    if (isClient() && !isLocal()) {
        return;
    }

    for (auto& other : collidedObjects) {
        if (other.use_count() > 1 && other->getName() == "Bullet Player") {
            hp -= 1;
            if (hp <= 0) {
                if (isLocal()) {
                    getGameObject().destroy();
                } else {
                    getServer()->destroyObject(getGameObject().getScene().getGameObject(getGameObject().getId()));
                }
            }
            if (isLocal()) {
                std::shared_ptr<KapEngine::GameObject> explosion;
                if (getGameObject().getEngine().getPrefabManager()->instantiatePrefab("BulletExplode", getGameObject().getScene(),
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
            hp -= 10;
            if (hp <= 0) {
                if (isLocal()) {
                    getGameObject().destroy();
                } else {
                    getServer()->destroyObject(getGameObject().getScene().getGameObject(getGameObject().getId()));
                }
            }
            if (isLocal()) {
                std::shared_ptr<KapEngine::GameObject> explosion;
                if (getGameObject().getEngine().getPrefabManager()->instantiatePrefab("MissileExplode", getGameObject().getScene(),
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
