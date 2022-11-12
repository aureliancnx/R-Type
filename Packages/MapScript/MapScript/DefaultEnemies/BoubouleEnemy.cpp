#include "BoubouleEnemy.hpp"
#include "KapMirror/KapMirror.hpp"
#include "Bullet/Bullet.hpp"

using namespace RType;

BoubouleEnemy::BoubouleEnemy(std::shared_ptr<KapEngine::GameObject> _gameObject) : EnemyController(_gameObject) {}

void BoubouleEnemy::onFixedUpdate() {
    auto& transform = getTransform();
    KapEngine::Tools::Vector3 nPos = transform.getWorldPosition();

    float speed = 0.5f;
    float xMove = (speed / 10000) * (float) getEngine().getElapsedTime().asMicroSecond();
    nPos.setX(nPos.getX() - xMove);
    transform.setPosition(nPos);

    auto time = KapMirror::NetworkTime::localTime();
    if (time - lastShootTime > 3000) {
        lastShootTime = time;
        shoot();
    }

    // Destroy enemy if his position is out of the screen
    if (transform.getWorldPosition().getX() < -100 || transform.getWorldPosition().getX() > 1280 + 200) {
        getGameObject().destroy();
    }
    if (transform.getWorldPosition().getY() < -100 || transform.getWorldPosition().getY() > 720 + 200) {
        getGameObject().destroy();
    }
}

void BoubouleEnemy::shoot() {
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
            [](const std::shared_ptr<KapEngine::GameObject>& go) { go->getComponent<Bullet>().setDirection(Bullet::Direction::LEFT); },
            bullet);
    }
}
