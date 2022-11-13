#include "EnemyController.hpp"

using namespace RType;

EnemyController::EnemyController(std::shared_ptr<KapEngine::GameObject> _gameObject) : KapMirror::NetworkComponent(_gameObject, "Enemy") {
    addRequireComponent("Image");
}

void EnemyController::setMapScript(MapScript* _mapScript) { mapScript = _mapScript; }

void EnemyController::setEnemyName(const std::string& _enemyName) { enemyName = _enemyName; }

void EnemyController::setHp(int _hp) { hp = _hp; }

void EnemyController::onFixedUpdate() {
    auto& transform = getTransform();
    if (mapScript != nullptr) {
        auto newPosition = mapScript->_updateEnemy(enemyName, transform.getLocalPosition());
        transform.setPosition(newPosition);
    }

    // Destroy enemy if his position is out of the screen
    KapEngine::Tools::Vector3 xOut;
    xOut.setX(transform.getWorldPosition().getX() + transform.getWorldScale().getX());
    xOut.setY(transform.getWorldPosition().getX());

    KapEngine::Tools::Vector3 yOut;
    yOut.setX(transform.getWorldPosition().getY() + transform.getWorldScale().getY());
    yOut.setY(transform.getWorldPosition().getY());

    if (xOut.getX() < 0 || xOut.getY() > 1280 + 200) {
        getGameObject().destroy();
    }
    if (yOut.getX() < 0  || yOut.getY() > 720 + 200) {
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
                    getServer()->destroyObject(getScene().getGameObject(getGameObject().getId()));
                }
            }

            if (isLocal()) {
                std::shared_ptr<KapEngine::GameObject> explosion;
                if (getEngine().getPrefabManager()->instantiatePrefab("BulletExplode", getScene(), explosion)) {
                    explosion->getComponent<KapEngine::Transform>().setPosition(
                        other->getComponent<KapEngine::Transform>().getWorldPosition());
                } else {
                    KAP_DEBUG_ERROR("Cannot instantiate prefab BulletExplode");
                }
                other->destroy();
            } else if (isServer()) {
                std::shared_ptr<KapEngine::GameObject> explosion;
                getServer()->spawnObject(
                    "BulletExplode", other->getComponent<KapEngine::Transform>().getWorldPosition(),
                    [&other](const std::shared_ptr<KapEngine::GameObject>& go) {
                        go->getComponent<KapEngine::Transform>().setPosition(
                            other->getComponent<KapEngine::Transform>().getWorldPosition());
                    },
                    explosion);
                getServer()->destroyObject(other);
            }
        } else if (other.use_count() > 1 && other->getName() == "Missile Player") {
            hp -= 10;
            if (hp <= 0) {
                if (isLocal()) {
                    getGameObject().destroy();
                } else {
                    getServer()->destroyObject(getScene().getGameObject(getGameObject().getId()));
                }
            }

            if (isLocal()) {
                std::shared_ptr<KapEngine::GameObject> explosion;
                if (getEngine().getPrefabManager()->instantiatePrefab("MissileExplode", getScene(), explosion)) {
                    explosion->getComponent<KapEngine::Transform>().setPosition(
                        other->getComponent<KapEngine::Transform>().getWorldPosition());
                } else {
                    KAP_DEBUG_ERROR("Cannot instantiate prefab MissiletExplode");
                }
                other->destroy();
            } else if (isServer()) {
                std::shared_ptr<KapEngine::GameObject> explosion;
                getServer()->spawnObject(
                    "MissileExplode", other->getComponent<KapEngine::Transform>().getWorldPosition(),
                    [&other](const std::shared_ptr<KapEngine::GameObject>& go) {
                        go->getComponent<KapEngine::Transform>().setPosition(
                            other->getComponent<KapEngine::Transform>().getWorldPosition());
                    },
                    explosion);
                getServer()->destroyObject(other);
            }
        }
    }

    collidedObjects.clear();
}
