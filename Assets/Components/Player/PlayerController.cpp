#include "PlayerController.hpp"
#include "Messages.hpp"
#include "GameManager.hpp"

using namespace RType;

PlayerController::PlayerController(std::shared_ptr<KapEngine::GameObject> _gameObject)
    : KapMirror::NetworkComponent(_gameObject, "Player") {
    addRequireComponent("Image");
    addRequireComponent("NetworkTransform");
}

void PlayerController::setLocalAuthority(bool _isLocalAuthority) { isLocalAuthority = _isLocalAuthority; }

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

    if (getInput().getKeyDown(upKey)) {
        getGameObject().getComponent<KapEngine::Animator>().setTrigger("IdleToUp");
    }
    if (getInput().getKeyUp(upKey)) {
        getGameObject().getComponent<KapEngine::Animator>().setTrigger("UpToIdle");
    }
    if (getInput().getKeyDown(downKey)) {
        getGameObject().getComponent<KapEngine::Animator>().setTrigger("IdleToDown");
    }
    if (getInput().getKeyUp(downKey)) {
        getGameObject().getComponent<KapEngine::Animator>().setTrigger("DownToIdle");
    }

    if (getInput().getKeyDown(shootKey)) {
        prepareShoot();
    }
    if (getInput().getKeyUp(shootKey)) {
        playShootSound();
        shoot();
        shootMissile = false;
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
    PlayerKeepAliveMessage keepAlive;
    keepAlive.timestamp = KapMirror::NetworkTime::localTime();

    if (isLocal()) {
        return;
    }
    KAP_DEBUG_LOG("SEND KEEPALIVE TO " + std::to_string(getNetworkId()));

    GameManager::getInstance()->getNetworkManager()->sendKeepAlive(networkIdentity);
}

void PlayerController::movePlayer(const KapEngine::Tools::Vector2& input) {
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

void PlayerController::prepareShoot() {
    if (isLocal()) {
        clockMissile.restart();
        if (menuManager.use_count() > 0) {
            menuManager->getMissileAnimator()->setTrigger("Load");
            KAP_DEBUG_LOG("Load missile");
        }
    } else if (isClient() && isLocalAuthority) {
        clockMissile.restart();
        if (menuManager.use_count() > 0) {
            menuManager->getMissileAnimator()->setTrigger("Load");
            KAP_DEBUG_LOG("Load missile");
        }
    } else if (isServer()) {
        KAP_DEBUG_LOG("Server prepare shoot");
        clockMissile.restart();
    } else if (isClient() && !isLocalAuthority) {
        if (menuManager.use_count() > 0) {
            menuManager->getMissileAnimator()->setTrigger("Load");
            KAP_DEBUG_LOG("Load missile");
        }
    }
}

void PlayerController::shoot() {
    KapEngine::Tools::Vector3 pos = getTransform().getLocalPosition() + KapEngine::Tools::Vector3(70, 15, 0);

    bool isMissile = false;

    if (isLocal()) {
        if (clockMissile.getElapseTime().asSecond() >= 4.5f) {
            isMissile = true;
        }
        if (menuManager.use_count() > 0) {
            menuManager->getMissileAnimator()->setTrigger("Unload");
        }

        auto& scene = getGameObject().getScene();
        std::shared_ptr<KapEngine::GameObject> bullet;
        if (isMissile) {
            getGameObject().getEngine().getPrefabManager()->instantiatePrefab("Missile", scene, bullet);
            bullet->setName("Missile Player");
        } else {
            getGameObject().getEngine().getPrefabManager()->instantiatePrefab("Bullet", scene, bullet);
            bullet->setName("Bullet Player");
        }
        bullet->getComponent<KapEngine::Transform>().setPosition(pos);
    } else if (isClient() && isLocalAuthority) {
        PlayerShootMessage message;
        message.networkId = getNetworkId();
        getClient()->send(message);
    } else if (isServer()) {
        if (clockMissile.getElapseTime().asSecond() >= 4.5f) {
            isMissile = true;
        }
        std::shared_ptr<KapEngine::GameObject> bullet;
        if (isMissile) {
            getServer()->spawnObject(
                "Missile", pos, [](const std::shared_ptr<KapEngine::GameObject>& bullet) { bullet->setName("Missile Player"); }, bullet);
        } else {
            getServer()->spawnObject(
                "Bullet", pos, [](const std::shared_ptr<KapEngine::GameObject>& bullet) { bullet->setName("Bullet Player"); }, bullet);
        }
    } else if (isClient() && !isLocalAuthority) {
        if (menuManager.use_count() > 0)
            menuManager->getMissileAnimator()->setTrigger("Unload");
    }
}

void PlayerController::takeDamage(int damage) {
    if (isClient()) {
        return;
    }

    life -= damage;
    if (life <= 0) {
        life = 0;
        isDead = true;
    }

    if (isServer()) {
        getServer()->updateObject(getNetworkId());
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
    try {
        auto go = getGameObject().getScene().findFirstGameObject("MenuManager");
        if (go) {
            auto menuManagers = go->getComponents<GameMenuManager>();
            if (!menuManagers.empty()) {
                menuManager = menuManagers[0];
            }
        }
    } catch (...) { KAP_DEBUG_LOG("MenuManager not found"); }
}

void PlayerController::onStart() {
    if (isLocal()) {
        initSettings();
        try {
            auto go = getGameObject().getScene().findFirstGameObject("MenuManager");
            if (go) {
                auto menuManagers = go->getComponents<GameMenuManager>();
                if (!menuManagers.empty()) {
                    menuManager = menuManagers[0];
                }
            }
        } catch (...) { KAP_DEBUG_LOG("MenuManager not found"); }
    }
}

void PlayerController::serialize(KapMirror::NetworkWriter& writer) {
    // TODO: Fix this (setup server and client access before serialize/deserialize)

    // if (!isServer()) {
    //     return;
    // }

    // writer.write(life);
    // writer.write(isDead);
}

void PlayerController::deserialize(KapMirror::NetworkReader& reader) {
    // life = reader.read<int>();
    // isDead = reader.read<bool>();
}
