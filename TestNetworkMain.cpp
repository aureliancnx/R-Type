#include "TestNetwork/NetworkManager.hpp"
#include "TestNetwork/SpaceShip.hpp"
#include "Graphical/RaylibGraphical.hpp"
#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"
#include "Factory.hpp"
#include "UiCanvas.hpp"
#include "UiText.hpp"
#include "UiImage.hpp"
#include "Debug.hpp"
#include <iostream>

void registerPrefabs(KapEngine::KapEngine& engine) {
    KapEngine::Debug::log("Registering prefabs");
    engine.getPrefabManager()->createPrefab("SpaceShip", [](KapEngine::SceneManagement::Scene& scene) {
        auto object = KapEngine::Factory::createEmptyGameObject(scene, "SpaceShip");

        auto networkIdentityComponent = std::make_shared<KapMirror::Experimental::NetworkIdentity>(object);
        object->addComponent(networkIdentityComponent);

        auto networkTransformComponent = std::make_shared<KapMirror::Experimental::NetworkTransform>(object);
        networkTransformComponent->setClientAuthority(false);
        networkTransformComponent->setSendRate(1);
        object->addComponent(networkTransformComponent);

        auto shipComponent = std::make_shared<RType::Component::SpaceShip>(object);
        object->addComponent(shipComponent);

        auto imageComponent = std::make_shared<KapEngine::UI::Image>(object);
        object->addComponent(imageComponent);
        imageComponent->setPathSprite("Assets/Textures/SpaceShip.png");
        imageComponent->setRectangle({0, 0, 99, 75});

        auto& shipTransform = object->getComponent<KapEngine::Transform>();
        shipTransform.setScale(KapEngine::Tools::Vector3(50.f, 50.f, 0.f));
        shipTransform.setParent(3);
        return object;
    });
}

void initSceneServer(KapEngine::KapEngine& engine) {
    auto& scene = engine.getSceneManager()->getScene(1);

    auto networkManagerObject = KapEngine::Factory::createEmptyGameObject(scene, "NetworkManager");
    auto networkManagerComponent = std::make_shared<RType::Component::TestNetworkManager>(networkManagerObject, true);
    networkManagerObject->addComponent(networkManagerComponent);

    auto canvasObject = KapEngine::Factory::createEmptyGameObject(scene, "Canvas");
    auto canvasComponent = std::make_shared<KapEngine::UI::Canvas>(canvasObject);
    canvasObject->addComponent(canvasComponent);
}

void initSceneClient(KapEngine::KapEngine& engine) {
    auto& scene = engine.getSceneManager()->getScene(1);

    auto networkManagerObject = KapEngine::Factory::createEmptyGameObject(scene, "NetworkManager");
    auto networkManagerComponent = std::make_shared<RType::Component::TestNetworkManager>(networkManagerObject, false);
    networkManagerObject->addComponent(networkManagerComponent);

    auto canvasObject = KapEngine::Factory::createEmptyGameObject(scene, "Canvas");
    auto canvasComponent = std::make_shared<KapEngine::UI::Canvas>(canvasObject);
    canvasObject->addComponent(canvasComponent);
}

int main(int ac, char **av) {
    KapEngine::Debug::log("Starting R-Type - Test Network...");

    bool isServer = false;
    if (ac > 1) {
        if (std::string(av[1]) == "server") {
            isServer = true;
        }
    }

    if (isServer) {
        KapEngine::Debug::log("Starting Server...");
    } else {
        KapEngine::Debug::log("Starting Client...");
    }

    KapEngine::KapEngine engine(true, "RType - TestNetwork", "Dev", "Epitech");

    KapEngine::Time::ETime timeFixed;
    timeFixed.setMicroseconds(25);
    engine.setFixedTime(timeFixed);

    engine.getSplashScreen()->setDisplayKapEngineLogo(false);

    KapEngine::Tools::Vector2 screenSize(1280, 720);
    engine.setScreenSize(screenSize);

    auto raylib = std::make_shared<KapEngine::Graphical::Raylib::RaylibGraphical>(*engine.getGraphicalLibManager());
    engine.getGraphicalLibManager()->addLib(raylib);
    engine.getGraphicalLibManager()->changeLib("raylib");

    registerPrefabs(engine);

    try {
        if (isServer) {
            initSceneServer(engine);
        } else {
            initSceneClient(engine);
        }
    } catch(KapEngine::Errors::Error e) {
        KapEngine::Debug::error("Error while init default scene: \"" + std::string(e.what()) + "\"");
    }
    engine.run();
    return 0;
}
