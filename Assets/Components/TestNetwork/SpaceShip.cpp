#include "SpaceShip.hpp"
#include "Transform.hpp"
#include "Debug.hpp"

using namespace RType::Component;

SpaceShip::SpaceShip(std::shared_ptr<KapEngine::GameObject> go) : KapMirror::Experimental::NetworkComponent(go, "SpaceShip") {
}

void SpaceShip::onStart() {
}

void SpaceShip::onUpdate() {
    getUserInput();
}

void SpaceShip::onStartServer() {
    KapEngine::Debug::log("SpaceShip::onStartServer");
}

void SpaceShip::onStartClient() {
    KapEngine::Debug::log("SpaceShip::onStartClient");
}

void SpaceShip::getUserInput() {
    auto& transform = getGameObject().getComponent<KapEngine::Transform>();
    if (getInput().getKey(KapEngine::Events::Key::DOWN)) {
        transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0.f, 1.f * speed, 0.f));
    }
    if (getInput().getKey(KapEngine::Events::Key::UP)) {
        transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0.f, -1.f * speed, 0.f));
    }
    if (getInput().getKey(KapEngine::Events::Key::LEFT)) {
        transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-1.f * speed, 0.f, 0.f));
    }
    if (getInput().getKey(KapEngine::Events::Key::RIGHT)) {
        transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(1.f * speed, 0.f, 0.f));
    }
    if (getInput().getKeyDown(KapEngine::Events::Key::SPACE)) {

    }
}
