//
// Created by leq on 13/10/22.
//

#include "SettingPlayerMenu.hpp"

#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"
#include "Animations/SpriteAnimation.hpp"
#include "Player/PlayerController.hpp"
#include "Player/PlayerSkin.hpp"

RType::SettingPlayerMenu::SettingPlayerMenu(KapEngine::SceneManagement::Scene &_scene) : Menu(_scene) {}

void RType::SettingPlayerMenu::init() {
    // Change type of display for canvas
    {
        try {
            auto &can = canvas->getComponent<KapEngine::UI::Canvas>();

            can.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
            can.setScreenCompare(KapEngine::Tools::Vector2(720, 480));
        } catch (...) { KAP_DEBUG_ERROR("Failed to resize canvas"); }
    }

    // Create background
    {
        auto background = KapEngine::UI::UiFactory::createImage(scene, "Background");
        auto imageComp = std::make_shared<KapEngine::UI::Image>(background);
        imageComp->setPathSprite("Assets/Textures/setting_bg_2.png");
        imageComp->setRectangle({0, 0, 381, 200});
        background->addComponent(imageComp);

        auto &transform = background->getComponent<KapEngine::Transform>();
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

        transform.setPosition({249, 430, 0});
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
        transform.setPosition(KapEngine::Tools::Vector3(230, 20, 0));
        transform.setParent(canvas);
    }

    // create text choose pseudo
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Choose pseudo Text");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Enter your pseudo : ");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale({150, 35, 0});
        transform.setPosition({150, 150, 0});
        transform.setParent(canvas);
    }

    // create inputfield for pseudo
    {
        auto inpt = scene.createGameObject("InputFieldPseudo");
        auto inptComp = std::make_shared<KapEngine::UI::Inputfield>(inpt);

        inpt->addComponent(inptComp);

        auto &transform = inpt->getComponent<KapEngine::Transform>();
        transform.setScale({150, 35, 0});
        transform.setPosition({330, 150, 0});
        transform.setParent(canvas);
    }

    // create text choose spaceship
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Choose pseudo Text");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Select your spaceship : ");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale({150, 35, 0});
        transform.setPosition({150, 250, 0});
        transform.setParent(canvas);
    }

    // create button to change spaceship
    {
        auto btn = scene.createGameObject("Choose Ship");
        std::shared_ptr<KapEngine::UI::Button> btnComp;
        if (IS_MAX_KAPUI_VERSION(0, 1)) {
            btnComp = std::make_shared<KapEngine::UI::Button>(btn, ">");
            btn->addComponent(btnComp);
        } else {
            btnComp = KapEngine::UI::KapUiFactory::createButton(btn, ">");
        }
        btnComp->setTextColor(KapEngine::Tools::Color::white());
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({15, 4});

        auto &transform = btn->getComponent<KapEngine::Transform>();
        transform.setPosition({480, 240, 0});
        transform.setScale({40, 39, 0});
        transform.setParent(canvas);

        auto children = transform.getChildren();
        for (const auto &i : children) {
            if (i->getName() == "Text" && i->hasComponent<KapEngine::UI::Text>()) {
                auto &txt = i->getComponent<KapEngine::UI::Text>();
                txt.setPoliceSize(30);
            }
        }

        btnComp->getOnClick().registerAction([this]() {
            int currentID = 1;

            if (KapEngine::PlayerPrefs::hasKey("shipID")) {
                currentID = KapEngine::PlayerPrefs::getInt("shipID");
            }
            currentID++;
            if (currentID > 5) {
                currentID = 1;
            }
            // KAP_DEBUG_WARNING("currentID = " + std::to_string(currentID));
            KapEngine::PlayerPrefs::setInt("shipID", currentID);
            player->getComponent<PlayerSkin>().setSkinId(currentID);
        });
    }

    // create spaceship animated
    {
        engine.getPrefabManager()->instantiatePrefab("Player", scene, player);
        player->getComponent<KapEngine::Transform>().setPosition({350, 240, 0});
        player->getComponent<KapEngine::Transform>().setParent(canvas);
        try {
            player->getComponent<KapEngine::UI::Canvas>().setActive(false);
        } catch (...) {}
    }
}
