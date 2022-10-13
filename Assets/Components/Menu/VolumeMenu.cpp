//
// Created by leq on 12/10/22.
//

#include "VolumeMenu.hpp"
#include "KapEngineUi.hpp"
#include "Button/Button.hpp"
#include "InputField/Inputfield.hpp"
#include "Volume/MenuVolume.hpp"
#include "Animations/SpriteAnimation.hpp"

RType::VolumeMenu::VolumeMenu(KapEngine::SceneManagement::Scene &_scene) : Menu(_scene) {}

void RType::VolumeMenu::init() {
    // Change type of display for canvas
    {
        try {
            auto &can = canvas->getComponent<KapEngine::UI::Canvas>();
            can.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
            can.setScreenCompare(KapEngine::Tools::Vector2(720, 480));
        } catch (...) {
            KAP_DEBUG_ERROR("Failed to resize canvas");
        }
    }

    // Create background
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

    // Create button back settings menu
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
            switchMenu("SettingsMenu");
        });
    }


    // Create text "volume :"
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Volume Text");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Volume : ");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale({150, 35, 0});
        transform.setPosition({250, 150, 0});
        transform.setParent(canvas);
    }

    // Create text volume value
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Volume Value Text");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, KapEngine::PlayerPrefs::getString("volumeID"));
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale({150, 35, 0});
        transform.setPosition({350, 150, 0});
        transform.setParent(canvas);
    }

    // Create button change volume up
    {
        auto btn = scene.createGameObject("ButtonVolumeUp");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();
        auto compTypeVolume = std::make_shared<MenuVolume>(btn);

        btn->addComponent(compTypeVolume);
        btn->addComponent(btnComp);
        btnComp->setText("UP");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({18, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({379, 206, 0});
        transform.setScale({50, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            int currentID = 0;

            try {
                if (!KapEngine::PlayerPrefs::getString("volumeValue").empty())
                    currentID = KapEngine::PlayerPrefs::getInt("volumeValue");
                currentID = currentID + 10;
                if (currentID > 100)
                    currentID = 100;
                KapEngine::PlayerPrefs::setInt("volumeValue", currentID);
            } catch (...) {}
        });
    }

    // Create button change volume down
    {
        auto btn = scene.createGameObject("ButtonVolumeDown");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();
        auto compTypeVolume = std::make_shared<MenuVolume>(btn);

        btn->addComponent(compTypeVolume);
        btn->addComponent(btnComp);
        btnComp->setText("DOWN");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({5, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({319, 206, 0});
        transform.setScale({50, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            int currentID = 0;

            try {
                if (!KapEngine::PlayerPrefs::getString("volumeValue").empty())
                    currentID = KapEngine::PlayerPrefs::getInt("volumeValue");
                currentID = currentID - 10;
                if (currentID < 0)
                    currentID = 0;
                KapEngine::PlayerPrefs::setInt("volumeValue", currentID);
            } catch (...) {}
        });

    }
}
