//
// Created by leq on 07/10/22.
//

#include "SettingsMenu.hpp"

#include "KapEngineUi.hpp"
#include "Button/Button.hpp"
#include "InputField/Inputfield.hpp"

#include "Spaceship/MenuSpaceShip.hpp"

#include "Animations/SpriteAnimation.hpp"

RType::SettingsMenu::SettingsMenu(KapEngine::SceneManagement::Scene &_scene) : Menu(_scene) {}

void RType::SettingsMenu::init() {

    //Change type of display for canvas
    {
        try {
            auto &can = canvas->getComponent<KapEngine::UI::Canvas>();

            can.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
        } catch (...){
            KAP_DEBUG_ERROR("Failed to resise canvas");
        }
    }

    //Create background
    {
        auto background = KapEngine::UI::UiFactory::createImage(scene, "Background");
        auto imageComp = std::make_shared<KapEngine::UI::Image>(background);
        imageComp->setPathSprite("Assets/Textures/background_2.png");
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
            goToMenu("MainMenu");
        });
    }
    //Create button volume

    {
        auto btn = scene.createGameObject("ButtonVolume");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Volume");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 168, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            goToMenu("VolumeMenu");
        });
    }
    //Create button keyboard

    {
        auto btn = scene.createGameObject("ButtonKeyBoard");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("KeyBoard");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 234, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            goToMenu("KeyboardMenu");
        });
    }

    // Create button HowToPlay
    {
        auto btn = scene.createGameObject("ButtonHowToPlay");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("How to play");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 300, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            goToMenu("HowToPlayMenu");
        });
    }
}

void RType::SettingsMenu::goToMenu(const std::string &name) {
    auto objs = scene.getGameObjects("Canvas" + name);
    auto objCurr = scene.getGameObjects("CanvasSettingsMenu");
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
        KAP_DEBUG_ERROR("Canvas called CanvasSettingsMenu not found to hide it");
        return;
    }
    _found->setActive(true);
    _foundCurrent->setActive(false);
}