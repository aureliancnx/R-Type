#include "TestNetwork/NetworkManager.hpp"
#include "TestNetwork/SpaceShip.hpp"
#include "Graphical/RaylibGraphical.hpp"
#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"
#include "Factory.hpp"
#include "UiCanvas.hpp"
#include "UiText.hpp"
#include "Debug.hpp"
#include <iostream>

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
