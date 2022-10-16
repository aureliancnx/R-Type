//
// Created by leq on 13/10/22.
//

#include "SettingPlayerMenu.hpp"

#include "KapEngineUi.hpp"
#include "Button/Button.hpp"
#include "InputField/Inputfield.hpp"
#include "Animations/SpriteAnimation.hpp"
#include "Player/PlayerController.hpp"
#include "Player/PlayerSkin.hpp"

RType::SettingPlayerMenu::SettingPlayerMenu(KapEngine::SceneManagement::Scene &_scene) : Menu(_scene){}

void RType::SettingPlayerMenu::init() {

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
        imageComp->setPathSprite("Assets/Textures/background_2.png");
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
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("SettingsMenu");
        });
    }

    // Create text Instruction setting player
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Change setting player");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Change your settings");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(20);

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(230, 50, 0));
        transform.setParent(canvas);
    }

    // create text choose pseudo
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Choose pseudo Text");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Enter your pseudo : ");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale({150, 35, 0});
        transform.setPosition({20, 100, 0});
        transform.setParent(canvas);
    }

    // create inputfield for pseudo
    {
        auto inpt = scene.createGameObject("InputFieldPseudo");
        auto inptComp = std::make_shared<KapEngine::UI::Inputfield>(inpt);

        inpt->addComponent(inptComp);

        auto &transform = inpt->getComponent<KapEngine::Transform>();
        transform.setScale({150, 35, 0});
        transform.setPosition({200, 100, 0});
        transform.setParent(canvas);
    }

    // create text choose spaceship
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Choose pseudo Text");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Select your spaceship : ");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale({150, 35, 0});
        transform.setPosition({20, 210, 0});
        transform.setParent(canvas);
    }

    // create button to change spaceship
    {
        auto btn = scene.createGameObject("Choose Ship");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn, ">");
        btnComp->setTextColor(KapEngine::Tools::Color::white());
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btn->addComponent(btnComp);

        auto& transform = btn->getComponent<KapEngine::Transform>();
        transform.setPosition(KapEngine::Tools::Vector3(350, 200, 0));
        transform.setScale(KapEngine::Tools::Vector3(40, 39, 0));
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            int currentID = 0;

            auto &compSkin = player->getComponent<PlayerSkin>();
            player->getComponent<KapEngine::Transform>().setPosition({200, 200, 0});
            player->getComponent<KapEngine::Transform>().setParent(canvas);

            try {
                player->getComponent<KapEngine::UI::Canvas>().setActive(false);
                if (!KapEngine::PlayerPrefs::getString("shipID").empty()) {
                    currentID = KapEngine::PlayerPrefs::getInt("shipID");
                }
            } catch(...) {}

            currentID++;
            if (currentID > 5)
                currentID = 1;
            KapEngine::PlayerPrefs::setInt("shipID", currentID);
            compSkin.setSkinId(KapEngine::PlayerPrefs::getInt("shipID"));
        });
    }
    // create spaceship animated
    {
        engine.getPrefabManager()->instantiatePrefab("Player", scene, player);
        auto &compSkin = player->getComponent<PlayerSkin>();

        player->getComponent<KapEngine::Transform>().setPosition({200, 200, 0});
        player->getComponent<KapEngine::Transform>().setParent(canvas);
        try {
            player->getComponent<KapEngine::UI::Canvas>().setActive(false);
        } catch (...) {}
    }
}