#include "PlayerController.hpp"
#include "Bullet/Bullet.hpp"
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

    checkCollisions();

    if (!isLocalAuthority) {
        return;
    }

    if (getInput().getKeyDown(debugKey)) {
        GameManager::getInstance()->toggleDebugMode();
    }

    // Movement
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

    // Movement Animation
    if (getInput().getKeyDown(upKey)) {
        getGameObject().getComponent<KapEngine::Animator>().setTrigger("IdleToUp");
    } else if (getInput().getKeyUp(upKey)) {
        getGameObject().getComponent<KapEngine::Animator>().setTrigger("UpToIdle");
    } else if (getInput().getKeyDown(downKey)) {
        getGameObject().getComponent<KapEngine::Animator>().setTrigger("IdleToDown");
    } else if (getInput().getKeyUp(downKey)) {
        getGameObject().getComponent<KapEngine::Animator>().setTrigger("DownToIdle");
    }

    // Shoot
    if (getInput().getKeyDown(shootKey)) {
        prepareShoot();
    } else if (getInput().getKeyUp(shootKey)) {
        playShootSound();
        shoot();
    }
}

void PlayerController::setConnectionId(unsigned int _connectionId) { connectionId = _connectionId; }

void PlayerController::sendPingUpdate() {
    if (KapMirror::NetworkTime::localTime() - lastPingTime > 2000) {
        unsigned int clientId = connectionId;
        lastPingTime = KapMirror::NetworkTime::localTime();
        auto &pingDict = GameManager::getInstance()->getNetworkManager()->pingRequests;

        unsigned int id = std::rand();
        KapEngine::Dictionary<unsigned int, long long> requests;

        if (!pingDict.tryGetValue(clientId, requests)) {
            pingDict[clientId] = requests;
        }
        pingDict[clientId][id] = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        PlayerPingRequest req;

        req.id = id;
        getServer()->sendToClient(req, clientId);
    }
}

#pragma region Movement

void PlayerController::onFixedUpdate() {
    if (isServer()) {
        sendPingUpdate();
    }

    if (!isMoving) {
        return;
    }

    auto &transform = getTransform();

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

void PlayerController::movePlayer(const KapEngine::Tools::Vector2 &input) {
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

void PlayerController::sendInput(const KapEngine::Tools::Vector2 &input) {
    if (!isClient() || !isLocalAuthority) {
        return;
    }

    PlayerInputMessage message;
    message.networkId = getNetworkId();
    message.x = input.getX();
    message.y = input.getY();
    getClient()->send(message);
}

#pragma endregion

#pragma region Shoot

void PlayerController::prepareShoot() {
    clockMissile.restart();

    if (isLocal()) {
        if (menuManager != nullptr) {
            menuManager->getMissileAnimator()->setTrigger("Load");
        }
    } else if (isClient() && isLocalAuthority) {
        if (menuManager != nullptr) {
            menuManager->getMissileAnimator()->setTrigger("Load");
        }

        PlayerPrepareShootMessage message;
        message.networkId = getNetworkId();
        getClient()->send(message);
    }
}

void PlayerController::shoot() {
    KapEngine::Tools::Vector3 pos = getTransform().getLocalPosition() + KapEngine::Tools::Vector3(90, 15, 0);
    bool isMissile = false;

    if (clockMissile.getElapseTime().asSecond() >= 4.5f) {
        isMissile = true;
    }

    if (isClient() && isLocalAuthority) {
        if (menuManager != nullptr) {
            menuManager->getMissileAnimator()->setTrigger("Unload");
        }

        PlayerShootMessage message;
        message.networkId = getNetworkId();
        getClient()->send(message);
        return;
    } else if (isLocal()) {
        if (menuManager != nullptr) {
            menuManager->getMissileAnimator()->setTrigger("Unload");
        }
    }

    if (!isMissile) {
        spawnBullet(pos);
    } else {
        spawnMissile(pos);
    }
}

void PlayerController::spawnBullet(const KapEngine::Tools::Vector3 &pos) {
    if (isLocal()) {
        auto &scene = getScene();
        std::shared_ptr<KapEngine::GameObject> bullet;
        getEngine().getPrefabManager()->instantiatePrefab("Bullet", scene, bullet);
        bullet->setName("Bullet Player");
        bullet->getComponent<KapEngine::Transform>().setPosition(pos);
        bullet->getComponent<Bullet>().setDirection(Bullet::Direction::RIGHT);
    } else if (isServer()) {
        std::shared_ptr<KapEngine::GameObject> bullet;
        getServer()->spawnObject(
            "Bullet", pos,
            [](const std::shared_ptr<KapEngine::GameObject> &bullet) {
                bullet->setName("Bullet Player");
                bullet->getComponent<Bullet>().setDirection(Bullet::Direction::RIGHT);
            },
            bullet);
    }
}

void PlayerController::spawnMissile(const KapEngine::Tools::Vector3 &pos) {
    if (isLocal()) {
        auto &scene = getScene();
        std::shared_ptr<KapEngine::GameObject> missile;
        getEngine().getPrefabManager()->instantiatePrefab("Missile", scene, missile);
        missile->setName("Missile Player");
        missile->getComponent<KapEngine::Transform>().setPosition(pos);
        missile->getComponent<Bullet>().setDirection(Bullet::Direction::RIGHT);
    } else if (isServer()) {
        std::shared_ptr<KapEngine::GameObject> missile;
        getServer()->spawnObject(
            "Missile", pos,
            [](const std::shared_ptr<KapEngine::GameObject> &missile) {
                missile->setName("Missile Player");
                missile->getComponent<Bullet>().setDirection(Bullet::Direction::RIGHT);
            },
            missile);
    }
}

void PlayerController::playShootSound() {
    if (isServer()) {
        return;
    }

    long long currentTime = KapMirror::NetworkTime::localTime();
    if (currentTime % 2 == 0) {
        getEngine().getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/shot1.wav");
    } else {
        getEngine().getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/shot2.wav");
    }
}

#pragma endregion

#pragma region collisions

void PlayerController::onTriggerEnter(std::shared_ptr<KapEngine::GameObject> collider) { collisions.push_back(collider); }

void PlayerController::checkCollisions() {
    if (collisions.empty()) {
        return;
    }

    for (auto &collision : collisions) {
        int damage = 0;
        if (collision->getName() == "Bullet") {
            damage = 4;
        } else if (collision->getName() == "Missile") {
            damage = 10;
        }
        if (collision->getName() == "Bullet" || collision->getName() == "Missile") {
            if (isLocal()) {
                collision->destroy();
            } else if (isServer()) {
                collision->destroy();
            }
            takeDamage(damage);
        }
    }

    collisions.clear();
}

#pragma endregion

void PlayerController::takeDamage(int damage) {
    life -= damage;
    KAP_DEBUG_LOG("Player[" + std::to_string(getNetworkId()) + "] Player life update: " + std::to_string(life));
    if (life <= 0) {
        life = 0;
        isDead = true;
        // TODO: do something on death
        if (isLocal() || isClient()) {
            menuManager->displayEndMenu(false);
        }
    }

    if (isServer()) {
        getServer()->updateObject(getNetworkId());
    }

    if (isLocal()) {
        menuManager->updateHealth(life);
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
    if (!KapEngine::PlayerPrefs::getString("debugInput").empty()) {
        int value = KapEngine::PlayerPrefs::getInt("debugInput");
        if (KapEngine::Events::Key::intInEnum(value)) {
            debugKey = static_cast<KapEngine::Events::Key::EKey>(value);
        }
    }
}

void PlayerController::onStartClient() {
    life = 100;
    initSettings();
    try {
        auto go = getScene().findFirstGameObject("MenuManager");
        if (go) {
            auto menuManagers = go->getComponents<GameMenuManager>();
            if (!menuManagers.empty()) {
                menuManager = menuManagers[0];
            }
        }
    } catch (...) { KAP_DEBUG_LOG("MenuManager not found"); }
    try {
        auto go = getScene().findFirstGameObject("LobbyManager");
        if (go) {
            auto lobbyManagers = go->getComponents<LobbyMenuManager>();
            if (!lobbyManagers.empty()) {
                lobbyManager = lobbyManagers[0];
            }
        }
    } catch (...) { KAP_DEBUG_LOG("LobbyManager not found"); }
}

void PlayerController::onStart() {
    life = 100;
    if (isLocal()) {
        initSettings();
        try {
            auto go = getScene().findFirstGameObject("MenuManager");
            if (go) {
                auto menuManagers = go->getComponents<GameMenuManager>();
                if (!menuManagers.empty()) {
                    menuManager = menuManagers[0];
                }
            }
        } catch (...) { KAP_DEBUG_LOG("MenuManager not found"); }
        try {
            auto go = getScene().findFirstGameObject("LobbyManager");
            if (go) {
                auto lobbyManagers = go->getComponents<LobbyMenuManager>();
                if (!lobbyManagers.empty()) {
                    lobbyManager = lobbyManagers[0];
                }
            }
        } catch (...) { KAP_DEBUG_LOG("LobbyManager not found"); }
    }
}

void PlayerController::onObjectUpdate() {
    if (isClient()) {
        if (menuManager) {
            menuManager->updateHealth(life);
        }
    }
}

void PlayerController::serialize(KapMirror::NetworkWriter &writer) {
    writer.write(life);
    writer.write(isDead);
}

void PlayerController::deserialize(KapMirror::NetworkReader &reader) {
    int _life = reader.read<int>();
    bool _isDead = reader.read<bool>();

    if (isClient()) {
        life = _life;
        isDead = _isDead;
    }
}

int PlayerController::getLife() const { return life; }

bool PlayerController::dead() const { return isDead; }
