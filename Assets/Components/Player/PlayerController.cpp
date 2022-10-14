#include "PlayerController.hpp"
#include "Bullet/Bullet.hpp"
#include "Messages.hpp"
#include "GameManager.hpp"

using namespace RType;

PlayerController::PlayerController(std::shared_ptr<KapEngine::GameObject> _gameObject) : KapMirror::NetworkComponent(_gameObject, "Player") {
    addRequireComponent("Image");
    addRequireComponent("NetworkTransform");
}

void PlayerController::setLocalAuthority(bool _isLocalAuthority) {
    isLocalAuthority = _isLocalAuthority;
}

void PlayerController::onUpdate() {
    if (isMoving) {
        if (getTransform().getLocalPosition() == posToMove) {
            isMoving = false;
        }
    }

    if (!isLocalAuthority) {
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

    // Send keep alive packet to the client
    if (KapMirror::NetworkTime::localTime() - lastKeepAliveTime > 1000) {
        lastKeepAliveTime = KapMirror::NetworkTime::localTime();
        sendKeepAlive();
    }
}

void PlayerController::sendKeepAlive() {
    PlayerKeepAlive keepAlive;
    keepAlive.timestamp = KapMirror::NetworkTime::localTime();

    if (isLocal()) {
        return;
    }
    KAP_DEBUG_LOG("SEND KEEPALIVE TO " + std::to_string(getNetworkId()));

    GameManager::getInstance()->getNetworkManager()->sendKeepAlive(networkIdentity);
}

void PlayerController::movePlayer(KapEngine::Tools::Vector2 input) {
    if (isClient()) {
        sendInput(input);
        return;
    }

    if (isMoving) {
        return;
    }

    posToMove = getTransform().getLocalPosition() + KapEngine::Tools::Vector3(input.getX(), input.getY(), 0) * 100;
    if (posToMove.getX() < 0 || posToMove.getX() > 800 || posToMove.getY() < 0 || posToMove.getY() + 116 > 720) {
        return;
    }

    isMoving = true;
    inputToMove = input;
}

void PlayerController::shoot() {
    KapEngine::Tools::Vector3 pos = getTransform().getLocalPosition() + KapEngine::Tools::Vector3(70, 15, 0);

    if (isLocal()) {
        auto& scene = getGameObject().getScene();
        std::shared_ptr<KapEngine::GameObject> bullet;
        getGameObject().getEngine().getPrefabManager()->instantiatePrefab("Bullet", scene, bullet);
        bullet->getComponent<KapEngine::Transform>().setPosition(pos);
    } else if (isClient() && isLocalAuthority) {
        PlayerShootMessage message;
        message.networkId = getNetworkId();
        getClient()->send(message);
    } else if (isServer()) {
        std::shared_ptr<KapEngine::GameObject> bullet;
        getServer()->spawnObject("Bullet", pos, bullet);
    }
}

void PlayerController::sendInput(KapEngine::Tools::Vector2 input) {
    if (!isClient() || !isLocalAuthority) {
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
