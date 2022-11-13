//
// Created by leq on 12/10/22.
//

#include "SettingsMenu.hpp"

#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"

#include "Animations/SpriteAnimation.hpp"

RType::SettingsMenu::SettingsMenu(KapEngine::SceneManagement::Scene &_scene) : Menu(_scene) {}

void RType::SettingsMenu::init() {

    // Change type of display for canvas
    {
        try {
            auto &can = canvas->getComponent<KapEngine::UI::Canvas>();
            can.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
            can.setScreenCompare(KapEngine::Tools::Vector2(720, 480));
        } catch (...) { KAP_DEBUG_ERROR("Failed to resise canvas"); }
    }

    // Create background
    {
        auto background = KapEngine::UI::UiFactory::createImage(scene, "Background");
        auto imageComp = std::make_shared<KapEngine::UI::Image>(background);
        imageComp->setPathSprite("Assets/Textures/setting_bg.png");
        imageComp->setRectangle({0, 0, 558, 360});
        background->addComponent(imageComp);

        auto &transform = background->getComponent<KapEngine::Transform>();
        transform.setPosition(KapEngine::Tools::Vector3(0, 0, 0));
        transform.setScale({720, 480, 0});
        transform.setParent(canvas);
    }

    // Create button back menu
    {
        auto btn = scene.createGameObject("ButtonBack");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Back");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 356, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("MainMenu");
        });
    }
    // Create button volume

    {
        auto btn = scene.createGameObject("ButtonVolume");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Volume");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 92, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("VolumeMenu");
        });
    }
    // Create button keyboard

    {
        auto btn = scene.createGameObject("ButtonKeyBoard");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("KeyBoard");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 158, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("KeysMenu");
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

        transform.setPosition({249, 224, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("HowToPlayMenu");
        });
    }

    // Create button Setting Player
    {
        auto btn = scene.createGameObject("ButtonSettingPlayer");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Setting Player");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 290, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("SettingPlayerMenu");
        });
    }
}
