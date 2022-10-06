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
        //get default scene
        auto &scene = engine->getSceneManager()->getScene(1);
        //create canvas object
        auto canvasObject = KapEngine::Factory::createEmptyGameObject(scene, "Canvas");
        //create image object
        auto imageObject = KapEngine::Factory::createEmptyGameObject(scene, "Image");
        //create text object
        auto textObject = KapEngine::Factory::createEmptyGameObject(scene, "Text");

        //get transform of image
        auto &trImage = (KapEngine::Transform &)imageObject->getTransform();
        trImage.setParent(canvasObject->getId());

        //get transform of text
        auto &trText = (KapEngine::Transform &)textObject->getTransform();
        trText.setParent(canvasObject->getId());

        //create Canvas component
        auto canvasComponent = std::make_shared<KapEngine::UI::Canvas>(canvasObject);
        canvasObject->addComponent(canvasComponent);

        //create Image component
        auto imageComponent = std::make_shared<KapEngine::UI::Image>(imageObject);
        imageObject->addComponent(imageComponent);

        //create text component
        auto textComponent = std::make_shared<KapEngine::UI::Text>(textObject);
        textObject->addComponent(textComponent);

        //set values for image
        KapEngine::Tools::Vector3 pos(0.f, 0.f, 10.f);
        KapEngine::Tools::Vector3 scale(0.3f, 1.f, 1.f);
        KapEngine::Tools::Rectangle crop(0, 0, 1436, 1080);
        //set image color
        imageComponent->setColor(KapEngine::Tools::Color::white());
        //set image sprite path
        imageComponent->setPathSprite("./Library/KapEngine/Documentation/images/KapEngineBannerNeg.png");
        //set image crop
        imageComponent->setRectangle(crop);
        //set image position
        trImage.setPosition(pos);
        //set image scale
        trImage.setScale(scale);

        //set text position
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

    //create raylib graphic
    auto raylib = std::make_shared<KapEngine::Graphical::Raylib::RaylibGraphical>(*engine.getGraphicalLibManager());
    //add raylib in KapEngine
    engine.getGraphicalLibManager()->addLib(raylib);
    //change current graphical lib of KapEngine to raylib
    engine.getGraphicalLibManager()->changeLib("raylib");

    try {
        //get default scene
        auto &scene = engine.getSceneManager()->getScene(1);
        //create Lol GameObject
        auto go = KapEngine::Factory::createEmptyGameObject(scene, "Lol");
        //create test component
        auto testComp = std::make_shared<RType::Component::TestComponent>(go);
        //add component test to Lol object
        go->addComponent(testComp);

    } catch(...) {}

    testCanvas(&engine);
    setPlayerAxis(&engine);

    engine.run();

    return 0;
}
