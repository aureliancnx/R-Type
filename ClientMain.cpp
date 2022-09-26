#include <iostream>

#include "KapEngine.hpp"
#include "Graphical/RaylibGraphical.hpp"
#include "TestComponent.hpp"
#include "Factory.hpp"
#include "UiCanvas.hpp"
#include "UiImage.hpp"
#include "UiText.hpp"
#include "Debug.hpp"

void testCanvas(KapEngine::KapEngine *engine) {
    try {

        KapEngine::Debug::log("Create canvas");

        auto &scene = engine->getSceneManager()->getScene(1);
        auto canvasObject = KapEngine::Factory::createEmptyGameObject(scene, "Canvas");
        auto imageObject = KapEngine::Factory::createEmptyGameObject(scene, "Image");
        auto textObject = KapEngine::Factory::createEmptyGameObject(scene, "Text");

        auto &trImage = (KapEngine::Transform &)imageObject->getTransform();
        trImage.setParent(canvasObject->getId());

        auto &trText = (KapEngine::Transform &)textObject->getTransform();
        trText.setParent(canvasObject->getId());

        auto canvasComponent = std::make_shared<KapEngine::UI::Canvas>(canvasObject);
        canvasObject->addComponent(canvasComponent);

        auto imageComponent = std::make_shared<KapEngine::UI::Image>(imageObject);
        imageObject->addComponent(imageComponent);

        auto textComponent = std::make_shared<KapEngine::UI::Text>(textObject);
        textObject->addComponent(textComponent);

        //set values for image
        KapEngine::Tools::Vector3 pos(0.f, 0.f, 10.f);
        KapEngine::Tools::Vector3 scale(0.3f, 1.f, 1.f);
        KapEngine::Tools::Rectangle crop(0, 0, 1436, 1080);
        imageComponent->setColor(KapEngine::Tools::Color::white());
        imageComponent->setPathSprite("./Library/KapEngine/Documentation/images/KapEngineBannerNeg.png");
        imageComponent->setRectangle(crop);
        trImage.setPosition(pos);
        trImage.setScale(scale);

        trText.setPosition(KapEngine::Tools::Vector3(200.f, 100.f, 0.f));

        //edit text
        textComponent->setText("enter text here...");

    } catch(KapEngine::Errors::Error e) {
        KapEngine::Debug::error("Error while create canvas: \"" + std::string(e.what()) + "\"");
    }
}

void setPlayerAxis(KapEngine::KapEngine *engine) {
    KapEngine::Events::Input::Axis _axisV("Vertical");
    KapEngine::Events::Input::Axis _axisH("Horizontal");
    KapEngine::Events::Input::Axis _axisM("Mouseinput");


    //init vertical axis
    _axisV.positiveButton = KapEngine::Events::Key::UP;
    _axisV.negativeButton = KapEngine::Events::Key::DOWN;

    //init horizontal axis
    _axisH.positiveButton = KapEngine::Events::Key::RIGHT;
    _axisH.negativeButton = KapEngine::Events::Key::LEFT;

    //init mouse axis
    _axisM.positiveButton = KapEngine::Events::Key::MOUSE_LEFT;
    _axisM.negativeButton = KapEngine::Events::Key::MOUSE_RIGHT;

    //add axis
    engine->getEventManager().getInput().addAxis(_axisH);
    engine->getEventManager().getInput().addAxis(_axisV);
    engine->getEventManager().getInput().addAxis(_axisM);
}

int main(int ac, char **av) {
    std::cout << "Starting R-Type Client..." << std::endl;

    KapEngine::KapEngine engine(true, "RType", "Alpha Client", "Epitech tkt on gère");

    KapEngine::Time::ETime timeFixed;

    timeFixed.setMicroseconds(25);

    engine.setFixedTime(timeFixed);

    engine.getSplashScreen()->setDisplayKapEngineLogo(false);

    KapEngine::Tools::Vector2 screenSize(720, 480);

    engine.setScreenSize(screenSize);

    auto raylib = std::make_shared<KapEngine::Graphical::Raylib::RaylibGraphical>(*engine.getGraphicalLibManager());

    engine.getGraphicalLibManager()->addLib(raylib);
    engine.getGraphicalLibManager()->changeLib("raylib");

    try {
        auto &scene = engine.getSceneManager()->getScene(1);
    
        auto go = KapEngine::Factory::createEmptyGameObject(scene, "Lol");
        auto testComp = std::make_shared<RType::Component::TestComponent>(go);
        go->addComponent(testComp);

    } catch(...) {}

    testCanvas(&engine);
    setPlayerAxis(&engine);

    engine.run();

    return 0;
}
