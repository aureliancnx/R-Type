#include "BasicEnemy.hpp"
#include "Bullet/Bullet.hpp"

using namespace RType;

BasicEnemy::BasicEnemy(std::shared_ptr<KapEngine::GameObject> _gameObject) : KapMirror::NetworkComponent(_gameObject, "BasicEnemy") {
    addRequireComponent("Image");
}

void BasicEnemy::setType(Type _type) {
    type = _type;
}

void BasicEnemy::setLife(int _life) {
    life = _life;
}

void BasicEnemy::onFixedUpdate() {
    auto& transform = getTransform();

    transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-1.0f, 0, 0));

    auto time = KapMirror::NetworkTime::localTime();
    if (time - lastShootTime > 1000) {
        lastShootTime = time;
        shoot();
    }

    if (transform.getWorldPosition().getX() < -100) {
        getGameObject().destroy();
    }
}

void BasicEnemy::onStartClient() {
    initSkin();
}

void BasicEnemy::shoot() {
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

void BasicEnemy::initSkin() {
    try {
        auto& image = getGameObject().getComponent<KapEngine::UI::Image>();
        image.setPathSprite("Assets/Textures/Ship/ship_" + std::to_string((int)type) + ".png");
    } catch (...) {
        KAP_DEBUG_ERROR("PlayerSkin::setSkinId: Image component not found");
    }
}

void BasicEnemy::customPayloadSerialize(KapMirror::NetworkWriter& writer) {
    writer.write(type);
    writer.write(life);
}

void BasicEnemy::customPayloadDeserialize(KapMirror::NetworkReader& reader) {
    type = reader.read<Type>();
    life = reader.read<int>();
}
