//
// Created by leq on 12/10/22.
//

#include "HowToPlayMenu.hpp"

#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"
#include "Animations/SpriteAnimation.hpp"
// #include "Animations/HowToPlayAnimation.hpp"

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
            imageComp.setRectangle({0, 0, 17, 18});

            auto& transform = bubulle->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(600, 200, 0));
            transform.setScale({40, 40});
            transform.setParent(fight);
        } catch (...) {
            KAP_DEBUG_ERROR("Failed to set bubulle img");
        }

        // try {
        //     ship->getComponent<KapEngine::UI::Image>();
        //     KAP_DEBUG_WARNING("SUCCESS");
        // } catch (...) {
        //     KAP_DEBUG_ERROR("Failed to set bubulle img");
        // }

        //fight animation
        // auto shipAnimation = std::make_shared<SpriteAnimation>(ship, 5, (KapEngine::Tools::Rectangle){0, 0, 263, 116}, 1);
        // auto bulletAnimation = std::make_shared<HowToPlayAnimation>(bullet);
        // auto bubulleAnimation = std::make_shared<HowToPlayAnimation>(bubulle);
        // auto explosionAnimation = std::make_shared<HowToPlayAnimation>(explosion);
        // fight->addComponent(shipAnimation);
        // fight->addComponent(bulletAnimation);
        // fight->addComponent(bubulleAnimation);
        // fight->addComponent(explosionAnimation);

        //fight animation
        {
            auto shipAnimation = std::make_shared<SpriteAnimation>(ship);
            KapEngine::Time::ETime timer;
            timer.setSeconds(.8);
            ship->addComponent(shipAnimation);
            shipAnimation->setTiming(timer);
            shipAnimation->loop(true);
            shipAnimation->setRect({0, 0, 263, 116});
            shipAnimation->setNbAnimations(6);

            auto animator = std::make_shared<KapEngine::Animator>(ship);
            ship->addComponent(animator);
            animator->addAnim(shipAnimation, "idle");
            animator->addLink("idle", "idle");
        }

        {
            auto bubulleAnimation = std::make_shared<SpriteAnimation>(bubulle);
            KapEngine::Time::ETime timer;
            timer.setSeconds(.8);
            bubulle->addComponent(bubulleAnimation);
            bubulleAnimation->setTiming(timer);
            bubulleAnimation->loop(true);
            bubulleAnimation->setRect({0, 0, 17, 18});
            bubulleAnimation->setNbAnimations(12);

            auto animator = std::make_shared<KapEngine::Animator>(bubulle);
            bubulle->addComponent(animator);
            animator->addAnim(bubulleAnimation, "idle");
            animator->addLink("idle", "idle");
        }

        {
            auto bulletAnimation = std::make_shared<SpriteAnimation>(bullet);
            KapEngine::Time::ETime timer;
            timer.setSeconds(.8);
            bullet->addComponent(bulletAnimation);
            bulletAnimation->setTiming(timer);
            bulletAnimation->loop(true);
            bulletAnimation->setRect({0, 0, 19, 6});
            bulletAnimation->setNbAnimations(2);

            auto animator = std::make_shared<KapEngine::Animator>(bullet);
            bullet->addComponent(animator);
            animator->addAnim(bulletAnimation, "idle");
            animator->addLink("idle", "idle");
        }
    }

    // create text for Move Up
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Move Up");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Move Up");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(150, 100, 0));
        transform.setParent(canvas);
    }

    // create text keyboard for Move Up
    {
        std::string inputUp = "UNDEFINED";
        int value = KapEngine::PlayerPrefs::getInt("upInput");
        if (KapEngine::Events::Key::intInEnum(value)) {
            KapEngine::Events::Key inputKey;
            inputKey = (KapEngine::Events::Key::EKey)value;
            inputUp = inputKey.toString();
        }
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Keyboard Move up");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, inputUp);
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(25, 100, 0));
        transform.setParent(canvas);
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

    // create text keyboard for Move Down
    {
        std::string inputDown = "UNDEFINED";
        int value = KapEngine::PlayerPrefs::getInt("downInput");
        if (KapEngine::Events::Key::intInEnum(value)) {
            KapEngine::Events::Key inputKey;
            inputKey = (KapEngine::Events::Key::EKey)value;
            inputDown = inputKey.toString();
        }
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Keyboard Move Down");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, inputDown);
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(25, 150, 0));
        transform.setParent(canvas);
    }

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

    // create text keyboard for Move Left
    {
        std::string inputLeft = "UNDEFINED";
        int value = KapEngine::PlayerPrefs::getInt("leftInput");
        if (KapEngine::Events::Key::intInEnum(value)) {
            KapEngine::Events::Key inputKey;
            inputKey = (KapEngine::Events::Key::EKey)value;
            inputLeft = inputKey.toString();
        }
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Keyboard Move Left");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, inputLeft);
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(25, 200, 0));
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

    // create text keyboard for Move Right
    {
        std::string inputRight = "UNDEFINED";
        int value = KapEngine::PlayerPrefs::getInt("rightInput");
        if (KapEngine::Events::Key::intInEnum(value)) {
            KapEngine::Events::Key inputKey;
            inputKey = (KapEngine::Events::Key::EKey)value;
            inputRight = inputKey.toString();
        }
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Keyboard Move Right");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, inputRight);
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(25, 250, 0));
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

    //create text keyboard for Shoot
    {
        std::string inputShoot = "UNDEFINED";
        int value = KapEngine::PlayerPrefs::getInt("shootInput");
        if (KapEngine::Events::Key::intInEnum(value)) {
            KapEngine::Events::Key inputKey;
            inputKey = (KapEngine::Events::Key::EKey)value;
            inputShoot = inputKey.toString();
        }
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Keyboard Move Shoot");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, inputShoot);
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(25, 300, 0));
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