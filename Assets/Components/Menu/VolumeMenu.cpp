//
// Created by leq on 07/10/22.
//

#include "VolumeMenu.hpp"

#include "KapEngineUi.hpp"
#include "Button/Button.hpp"
#include "InputField/Inputfield.hpp"

#include "Spaceship/MenuSpaceShip.hpp"

#include "Animations/SpriteAnimation.hpp"

RType::VolumeMenu::VolumeMenu(KapEngine::SceneManagement::Scene &_scene) : Menu(_scene) {}

void RType::VolumeMenu::init() {

    //Change type of display for canvas
    {
        try {
            auto &can = canvas->getComponent<KapEngine::UI::Canvas>();

            can.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
        } catch (...) {
            KAP_DEBUG_ERROR("Failed to resize canvas");
        }
    }

    //Create background
    {
        auto background = KapEngine::UI::UiFactory::createImage(scene, "Background");
        auto imageComp = std::make_shared<KapEngine::UI::Image>(background);
        imageComp->setPathSprite("Assets/Textures/background_1.png");
        imageComp->setRectangle({0, 0, 755, 448});
        background->addComponent(imageComp);

        auto& transform = background->getComponent<KapEngine::Transform>();
        transform.setPosition(KapEngine::Tools::Vector3(0, 0, 0));
        transform.setScale({720, 480, 0});
        transform.setParent(canvas);
    }

    //Create button back menu
    {
        auto btn = scene.createGameObject("ButtonBack");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Back");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 366, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            goToMenu("SettingsMenu");
        });
    }

    // Create button change volume up
    {
        auto btn = scene.createGameObject("ButtonVolumeUp");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("UP");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({18, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({319, 136, 0});
        transform.setScale({50, 39, 0});
        transform.setParent(canvas);
    }

    // Create button change volume down
    {
        auto btn = scene.createGameObject("ButtonVolumeDown");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("DOWN");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({5, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({379, 136, 0});
        transform.setScale({50, 39, 0});
        transform.setParent(canvas);
    }
    // Create text Change volume

    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Volume Text Change");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Volume : ");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale({150, 35, 0});
        transform.setPosition({250, 150, 0});
        transform.setParent(canvas);
    }

    // Create button on/off music
    {
        auto btn = scene.createGameObject("ButtonOnOff");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("On");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({100, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 266, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            // Change text ButtonOnOff
        });
    }
    // Create music
    {
//        getGameObject().getEngine().getGraphicalLibManager()->getCurrentLib()->playSound(path);
        //scene

        //auto music = scene.createGameObject("Music test");
        //auto compMusic = std::make_shared<>( )
    }

}

void RType::VolumeMenu::goToMenu(std::string const& name) {
    auto objs = scene.getGameObjects("Canvas" + name);
    auto objCurr = scene.getGameObjects("CanvasVolumeMenu");
    std::shared_ptr<KapEngine::GameObject> _found;
    std::shared_ptr<KapEngine::GameObject> _foundCurrent;

    for (std::size_t i = 0; i < objs.size(); i++) {
        if (objs[i]->hasComponent("Canvas")) {
            _found = objs[i];
            break;
        }
    }

    for (std::size_t i = 0; i < objCurr.size(); i++) {
        if (objCurr[i]->hasComponent("Canvas")) {
            _foundCurrent = objCurr[i];
            break;
        }
    }

    if (_found.use_count() == 0) {
        KAP_DEBUG_ERROR("Canvas called " + name + " not found to display it");
        return;
    }
    if (_foundCurrent.use_count() == 0) {
        KAP_DEBUG_ERROR("Canvas called CanvasVolumeMenu not found to hide it");
        return;
    }
    _found->setActive(true);
    _foundCurrent->setActive(false);
}
