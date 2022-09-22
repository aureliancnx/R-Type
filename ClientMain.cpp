#include <iostream>

#include "KapEngine.hpp"
#include "Graphical/RaylibGraphical.hpp"
#include "TestComponent.hpp"
#include "Factory.hpp"
#include "UiCanvas.hpp"
#include "UiImage.hpp"
#include "Debug.hpp"
void testCanvas(KapEngine::KapEngine *engine) {
    try {

        KapEngine::Debug::log("Create canvas");

        auto &scene = engine->getSceneManager()->getCurrentScene();
        auto canvasObject = KapEngine::Factory::createEmptyGameObject(scene, "Canvas");
        auto imageObject = KapEngine::Factory::createEmptyGameObject(scene, "Image");

        auto &trImage = (KapEngine::Transform &)imageObject->getTransform();
        trImage.setParent(canvasObject->getId());

        auto canvasComponent = std::make_shared<KapEngine::UI::Canvas>(canvasObject);
        canvasObject->addComponent(canvasComponent);

        auto imageComponent = std::make_shared<KapEngine::UI::Image>(imageObject);
        imageObject->addComponent(imageComponent);

        //set values for image
        KapEngine::Tools::Vector3 pos(500.f, 250.f, 10.f);
        KapEngine::Tools::Vector3 scale(15.f, 15.f, 15.f);
        imageComponent->setColor(KapEngine::Tools::Color::green());
        trImage.setPosition(pos);
        trImage.setScale(scale);

    } catch(KapEngine::Errors::Error e) {
        KapEngine::Debug::error("Error while create canvas: \"" + std::string(e.what()) + "\"");
    }
}

int main(int ac, char **av) {
    // std::cout << "Starting R-Type Client..." << std::endl;

    KapEngine::KapEngine engine(true, "RType", "Alpha Client", "Epitech tkt on gère");

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

    testCanvas(&engine);

    engine.run();

    return 0;
}

// int main(int ac, char **av) {
//     std::cout << "Starting R-Type Client..." << std::endl;
//     return 0;
// }
