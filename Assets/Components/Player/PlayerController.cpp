#include "PlayerController.hpp"
#include "Bullet/Bullet.hpp"
#include "Messages.hpp"

using namespace RType;

PlayerController::PlayerController(std::shared_ptr<KapEngine::GameObject> _gameObject) : KapMirror::NetworkComponent(_gameObject, "Player") {
    addRequireComponent("Image");
    addRequireComponent("NetworkTransform");
}

void PlayerController::setLocalAuthoriy(bool _isLocalAuthoriy) {
    isLocalAuthoriy = _isLocalAuthoriy;
}

void PlayerController::onUpdate() {
    if (isMoving) {
        if (getTransform().getLocalPosition() == posToMove) {
            isMoving = false;
        }
    }

    if (!isLocalAuthoriy) {
        return;
    }

    if (!isMoving) {
        if (getInput().getKeyDown(rightKey)) {
            movePlayer(KapEngine::Tools::Vector2(1, 0));
        } else if (getInput().getKeyDown(leftKey)) {
            movePlayer(KapEngine::Tools::Vector2(-1, 0));
        } else if (getInput().getKeyDown(upKey)) {
            movePlayer(KapEngine::Tools::Vector2(0, -1));
        } else if (getInput().getKeyDown(downKey)) {
            movePlayer(KapEngine::Tools::Vector2(0, 1));
        }
    }

    if (getInput().getKeyDown(shootKey)) {
        playShootSound();
        shoot();
    }
}

void PlayerController::onFixedUpdate() {
    if (!isMoving) {
        return;
    }

    auto& transform = getTransform();

    int moveRate = 30;
    if (KapMirror::NetworkTime::localTime() - lastRefreshTime > 1000 / moveRate) {
        lastRefreshTime = KapMirror::NetworkTime::localTime();
        if (transform.getLocalPosition() != posToMove) {
            transform.setPosition(transform.getLocalPosition() + inputToMove * 10);
        } else {
            isMoving = false;
        }
    }
}

void PlayerController::movePlayer(KapEngine::Tools::Vector2 input) {
    if (isMoving) {
        return;
    }

    isMoving = true;

    sendInput(input);

    posToMove = getTransform().getLocalPosition() + KapEngine::Tools::Vector3(input.getX(), input.getY(), 0) * 100;
    inputToMove = input;
}

void PlayerController::shoot() {
    KapEngine::Tools::Vector3 pos = getTransform().getLocalPosition() + KapEngine::Tools::Vector3(70, 15, 0);

    if (isLocal()) {
        auto& scene = getGameObject().getScene();
        std::shared_ptr<KapEngine::GameObject> bullet;
        getGameObject().getEngine().getPrefabManager()->instantiatePrefab("Bullet", scene, bullet);
        bullet->getComponent<KapEngine::Transform>().setPosition(pos);
    } else if (isClient() && isLocalAuthoriy) {
        PlayerShootMessage message;
        message.networkId = getNetworkId();
        getClient()->send(message);
    } else if (isServer()) {
        std::shared_ptr<KapEngine::GameObject> bullet;
        getServer()->spawnObject("Bullet", pos, bullet);
    }
}

void PlayerController::sendInput(KapEngine::Tools::Vector2 input) {
    if (!isClient() || !isLocalAuthoriy) {
        return;
    }

    PlayerInputMessage message;
    message.networkId = getNetworkId();
    message.x = input.getX();
    message.y = input.getY();
    getClient()->send(message);
}

void PlayerController::playShootSound() {
    long long currentTime = KapMirror::NetworkTime::localTime();
    if (currentTime % 2 == 0) {
        getGameObject().getEngine().getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/shot1.wav");
    } else {
        getGameObject().getEngine().getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/shot2.wav");
    }
}

void PlayerController::initSettings() {
    if (!KapEngine::PlayerPrefs::getString("upInput").empty()) {
        int value = KapEngine::PlayerPrefs::getInt("upInput");
        if (KapEngine::Events::Key::intInEnum(value)) {
            upKey = static_cast<KapEngine::Events::Key::EKey>(value);
        }
    }
    if (!KapEngine::PlayerPrefs::getString("downInput").empty()) {
        int value = KapEngine::PlayerPrefs::getInt("downInput");
        if (KapEngine::Events::Key::intInEnum(value)) {
            downKey = static_cast<KapEngine::Events::Key::EKey>(value);
        }
    }
    if (KapEngine::PlayerPrefs::getString("leftInput").empty()) {
        int value = KapEngine::PlayerPrefs::getInt("leftInput");
        if (KapEngine::Events::Key::intInEnum(value)) {
            leftKey = static_cast<KapEngine::Events::Key::EKey>(value);
        }
    }
    if (!KapEngine::PlayerPrefs::getString("rightInput").empty()) {
        int value = KapEngine::PlayerPrefs::getInt("rightInput");
        if (KapEngine::Events::Key::intInEnum(value)) {
            rightKey = static_cast<KapEngine::Events::Key::EKey>(value);
        }
    }
    if (!KapEngine::PlayerPrefs::getString("shootInput").empty()) {
        int value = KapEngine::PlayerPrefs::getInt("shootInput");
        if (KapEngine::Events::Key::intInEnum(value)) {
            shootKey = static_cast<KapEngine::Events::Key::EKey>(value);
        }
    }
}

void PlayerController::onStartClient() {
    initSettings();
}
