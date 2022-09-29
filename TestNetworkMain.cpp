#include "KapEngine.hpp"
#include "Graphical/RaylibGraphical.hpp"
#include "Factory.hpp"
#include "Debug.hpp"
#include "TestNetworkManager.hpp"
#include <iostream>

int main(int ac, char **av) {
    bool isServer = false;

    if (ac > 1) {
        if (std::string(av[1]) == "server") {
            isServer = true;
        }
    }

    if (isServer) {
        std::cout << "Starting R-Type Server..." << std::endl;
    } else {
        std::cout << "Starting R-Type Client..." << std::endl;
    }

    KapEngine::KapEngine engine(true, "RType", "Alpha Client", "Epitech tkt on gère");

    KapEngine::Tools::Vector2 screenSize(720, 480);
    engine.setScreenSize(screenSize);

    auto raylib = std::make_shared<KapEngine::Graphical::Raylib::RaylibGraphical>(*engine.getGraphicalLibManager(), false);
    engine.getSplashScreen()->setDisplayKapEngineLogo(false);
    engine.getGraphicalLibManager()->addLib(raylib);
    engine.getGraphicalLibManager()->changeLib("raylib");

    try {
        auto &scene = engine.getSceneManager()->getScene(1);
        auto go = KapEngine::Factory::createEmptyGameObject(scene, "TestNetworkManager");
        auto testNetworkManager = std::make_shared<RType::Component::TestNetworkManager>(go, isServer);
        go->addComponent(testNetworkManager);
    } catch(...) {}

    engine.run();

    return 0;
}
