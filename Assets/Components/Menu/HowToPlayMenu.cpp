//
// Created by leq on 12/10/22.
//

#include "HowToPlayMenu.hpp"

#include "KapEngineUi.hpp"
#include "Button/Button.hpp"
#include "InputField/Inputfield.hpp"
#include "Player/PlayerSkin.hpp"
#include "Animations/SpriteAnimation.hpp"

//using namespace KapEngine;

RType::HowToPlayMenu::HowToPlayMenu(KapEngine::SceneManagement::Scene &_scene) : Menu(_scene) {}

void RType::HowToPlayMenu::init() {

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

    // create text for How to play title
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "How to play title");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "HOW TO PLAY");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(300, 30, 0));
        transform.setParent(canvas);
    }

    // create htp animation with canvas
    {
        auto fight = scene.createGameObject("Fight");

        try {
            auto &tr = fight->getComponent<KapEngine::Transform>();
            tr.setParent(canvas);
        } catch (...) {
            KAP_DEBUG_ERROR("Failed to get Transform of parent");
        }

        auto ship = KapEngine::UI::UiFactory::createImage(scene, "Ship");
        auto bullet = KapEngine::UI::UiFactory::createImage(scene, "Bullet");
        auto bubulle = KapEngine::UI::UiFactory::createImage(scene, "Bubulle");

        try {
            auto &imageComp = ship->getComponent<KapEngine::UI::Image>();
            imageComp.setPathSprite("Assets/Textures/Ship/ship_1.png");
            imageComp.setRectangle({0, 0, 263, 116});

            auto& transform = ship->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(300, 200, 0));
            transform.setScale({79, 35, 0});
            transform.setParent(fight);
        } catch (...) {
            KAP_DEBUG_ERROR("Failed to set ship img");
        }

        try {
            auto &imageComp = bullet->getComponent<KapEngine::UI::Image>();
            imageComp.setPathSprite("Assets/Textures/Bullet/bullet_1.png");
            imageComp.setRectangle({0, 0, 19, 6});

            auto& transform = bullet->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(400, 215, 0));
            transform.setScale({19, 6});
            transform.setParent(fight);
        } catch (...) {
            KAP_DEBUG_ERROR("Failed to set bullet img");
        }
        
        try {
            auto &imageComp = bubulle->getComponent<KapEngine::UI::Image>();
            imageComp.setPathSprite("Assets/Textures/bubulle.png");
            imageComp.setRectangle({0, 0, 18, 19});

            auto& transform = bubulle->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(600, 200, 0));
            transform.setScale({40, 40});
            transform.setParent(fight);
        } catch (...) {
            KAP_DEBUG_ERROR("Failed to set bubulle img");
        }

        //fight animation
        auto fightAnimation = std::make_shared<HowToPlayAnimation>(fight);
        fight->addComponent(fightAnimation);

        auto animator = std::make_shared<KapEngine::Animator>(fight);
        fight->addComponent(animator);
        animator->addAnim(fightAnimation, "idle");
        animator->addLink("idle", "idle");
    }

    // create text for Move Down
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Move Down");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Move Down");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(150, 150, 0));
        transform.setParent(canvas);
    }

    // // create text for Move Down input command
    // {
    //     auto moveKey = canvas->getComponent<ChangeKey>();
    //     auto txt = KapEngine::UI::UiFactory::createText(scene, "Move Down");
    //     auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Flèche");
    //     auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

    //     txt->addComponent(compText);
    //     transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
    //     transform.setPosition(KapEngine::Tools::Vector3(50, 150, 0));
    //     transform.setParent(canvas);
    // }

    // create text for Move Left
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Move Left");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Move Left");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(150, 200, 0));
        transform.setParent(canvas);
    }

    // create text for Move Right
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Move Right");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Move Right");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(150, 250, 0));
        transform.setParent(canvas);
    }

    // create text for Shoot
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Shoot");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Shoot");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(150, 300, 0));
        transform.setParent(canvas);
    }

        // //create Move Down keyboard img
    // {
    //     auto img = KapEngine::UI::UiFactory::createImage(scene, "Move Down");
    //     auto imageComp = std::make_shared<KapEngine::UI::Image>(img);
    //     imageComp->setPathSprite("Assets/Textures/Keyboard/keyboard.png");
    //     //x = longueur, y = largeur
    //     // imageComp->setRectangle({82, 209, 60, 60});
    //     imageComp->setRectangle({858, 470, 60, 60});
    //     img->addComponent(imageComp);

    //     auto& transform = img->getComponent<KapEngine::Transform>();
    //     // x = longueur, y = largeur
    //     transform.setPosition(KapEngine::Tools::Vector3(90, 130, 0));
    //     // x = longueur, y = largeur 
    //     transform.setScale({50, 50, 0});
    //     transform.setParent(canvas);
    // }
}