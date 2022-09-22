#include <iostream>

#include "KapEngine.hpp"
#include "Graphical/RaylibGraphical.hpp"
#include "TestComponent.hpp"
#include "Factory.hpp"

int main(int ac, char **av) {
    // std::cout << "Starting R-Type Client..." << std::endl;

    KapEngine::KapEngine engine(true, "RType", "Alpha", "Epitech tkt on gère");

    KapEngine::Tools::Vector2 screenSize(720, 480);

    engine.setScreenSize(screenSize);

    auto raylib = std::make_shared<KapEngine::Graphical::RaylibGraphical>(*engine.getGraphicalLibManager());

    engine.getGraphicalLibManager()->addLib(raylib);
    engine.getGraphicalLibManager()->changeLib("raylib");

    try {
        auto &scene = engine.getSceneManager()->getCurrentScene();
    
        auto go = KapEngine::Factory::createEmptyGameObject(scene, "Lol");
        auto testComp = std::make_shared<RType::Component::TestComponent>(go);
        go->addComponent(testComp);

    } catch(...) {}

    engine.run();

    return 0;
}

// int main(int ac, char **av) {
//     std::cout << "Starting R-Type Client..." << std::endl;
//     return 0;
// }
