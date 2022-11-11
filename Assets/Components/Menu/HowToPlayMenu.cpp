//
// Created by leq on 12/10/22.
//

#include "HowToPlayMenu.hpp"

#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"
#include "Animations/SpriteAnimation.hpp"
#include "Animations/HowToPlayAnimation.hpp"

// using namespace KapEngine;

RType::HowToPlayMenu::HowToPlayMenu(KapEngine::SceneManagement::Scene& _scene) : Menu(_scene) {}

void RType::HowToPlayMenu::init() {

    // Change type of display for canvas
    {
        try {
            auto& can = canvas->getComponent<KapEngine::UI::Canvas>();
            can.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
            can.setScreenCompare(KapEngine::Tools::Vector2(720, 480));
        } catch (...) { KAP_DEBUG_ERROR("Failed to resize canvas"); }
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
        auto& transform = btn->getComponent<KapEngine::Transform>();

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
        auto& transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(300, 30, 0));
        transform.setParent(canvas);
    }

    // create htp animation with canvas
    {
        auto fight = scene.createGameObject("Fight");

        try {
            auto& tr = fight->getComponent<KapEngine::Transform>();
            tr.setParent(canvas);
        } catch (...) { KAP_DEBUG_ERROR("Failed to get Transform of parent"); }

        auto ship = KapEngine::UI::UiFactory::createImage(scene, "Ship");
        auto bullet = KapEngine::UI::UiFactory::createImage(scene, "Bullet");
        auto bouboule = KapEngine::UI::UiFactory::createImage(scene, "Bouboule");
        auto bouboule2 = KapEngine::UI::UiFactory::createImage(scene, "Bouboule2");
        auto explosion = KapEngine::UI::UiFactory::createImage(scene, "Explosion");

        try {
            auto& imageComp = ship->getComponent<KapEngine::UI::Image>();
            imageComp.setPathSprite("Assets/Textures/Ship/ship_1.png");
            imageComp.setRectangle({0, 0, 263, 116});

            auto& transform = ship->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(300, 50, 0));
            transform.setScale({79, 35, 0});
            transform.setParent(fight);
        } catch (...) { KAP_DEBUG_ERROR("Failed to set ship img"); }

        try {
            auto& imageComp = bullet->getComponent<KapEngine::UI::Image>();
            imageComp.setPathSprite("Assets/Textures/Bullet/bullet_1.png");
            imageComp.setRectangle({0, 0, 19, 6});

            auto& transform = bullet->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(380, 266, 0));
            transform.setScale({19, 6});
            transform.setParent(fight);
        } catch (...) { KAP_DEBUG_ERROR("Failed to set bullet img"); }

        try {
            auto& imageComp = bouboule->getComponent<KapEngine::UI::Image>();
            imageComp.setPathSprite("Assets/Textures/bubulle.png");
            imageComp.setRectangle({0, 0, 17, 18});

            auto& transform = bouboule->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(600, 50, 0));
            transform.setScale({40, 40});
            transform.setParent(fight);
        } catch (...) { KAP_DEBUG_ERROR("Failed to set bouboule img"); }

        try {
            auto& imageComp = bouboule2->getComponent<KapEngine::UI::Image>();
            imageComp.setPathSprite("Assets/Textures/bubulle.png");
            imageComp.setRectangle({0, 0, 17, 18});

            auto& transform = bouboule2->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(500, 50, 0));
            transform.setScale({40, 40});
            transform.setParent(fight);
        } catch (...) { KAP_DEBUG_ERROR("Failed to set bouboule2 img"); }

        // try {
        //     auto& imageComp = explosion->getComponent<KapEngine::UI::Image>();
        //     imageComp.setPathSprite("Assets/Textures/Explosion.png");
        //     imageComp.setRectangle({0, 50, 30, 35});

        //     auto& transform = explosion->getComponent<KapEngine::Transform>();
        //     transform.setPosition(KapEngine::Tools::Vector3(400, 50, 0));
        //     transform.setScale({50, 70});
        //     transform.setParent(fight);
        // } catch (...) { KAP_DEBUG_ERROR("Failed to set explosion img"); }

        try {
            auto& imageComp = explosion->getComponent<KapEngine::UI::Image>();
            imageComp.setPathSprite("Assets/Textures/Explosion/wills_pixel_explosions_sample/round_explosion/spritesheet/spritesheet.png");
            imageComp.setRectangle({0, 0, 100, 100});

            auto& transform = explosion->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(600, 230, 0));
            transform.setScale({50, 70});
            transform.setParent(fight);
        } catch (...) { KAP_DEBUG_ERROR("Failed to set explosion img"); }

        try {
            auto shipIdle = std::make_shared<SpriteAnimation>(ship);
            ship->addComponent(shipIdle);

            KapEngine::Time::ETime timer;
            timer.setSeconds(.1f);
            shipIdle->setTiming(timer);
            shipIdle->setRect({263 * 2, 0, 263, 116});
            shipIdle->setNbAnimations(1);

            auto shipUp = std::make_shared<SpriteAnimation>(ship);
            ship->addComponent(shipUp);

            shipUp->setTiming(timer);
            shipUp->setRect({263 * 4, 0, 263, 116});
            shipUp->setNbAnimations(1);

            auto shipDown = std::make_shared<SpriteAnimation>(ship);
            ship->addComponent(shipDown);

            shipDown->setTiming(timer);
            shipDown->setRect({263 * 0, 0, 263, 116});
            shipDown->setNbAnimations(1);

            auto animator = std::make_shared<KapEngine::Animator>(ship);
            ship->addComponent(animator);

            animator->addAnim(shipIdle, "Idle");
            animator->addAnim(shipUp, "Up");
            animator->addAnim(shipDown, "Down");

            animator->addLink("Idle", "Idle", "IdleToIdle");

            animator->addLink("Idle", "Up", "IdleToUp");
            animator->addLink("Up", "Idle", "UpToIdle");

            animator->addLink("Idle", "Down", "IdleToDown");
            animator->addLink("Down", "Idle", "DownToIdle");
        } catch (...) { KAP_DEBUG_ERROR("Failed to set shipAnimation img"); }

        try {
            auto boubouleAnimation = std::make_shared<SpriteAnimation>(bouboule);
            KapEngine::Time::ETime timer;
            timer.setSeconds(.8);
            bouboule->addComponent(boubouleAnimation);
            boubouleAnimation->setTiming(timer);
            boubouleAnimation->loop(true);
            boubouleAnimation->setRect({0, 0, 17, 18});
            boubouleAnimation->setNbAnimations(12);

            auto animator = std::make_shared<KapEngine::Animator>(bouboule);
            bouboule->addComponent(animator);
            animator->addAnim(boubouleAnimation, "Idle");
            animator->addLink("Idle", "Idle");
        } catch (...) { KAP_DEBUG_ERROR("Failed to set boubouleAnimation img"); }

        try {
            auto boubouleAnimation = std::make_shared<SpriteAnimation>(bouboule2);
            KapEngine::Time::ETime timer;
            timer.setSeconds(.8);
            bouboule2->addComponent(boubouleAnimation);
            boubouleAnimation->setTiming(timer);
            boubouleAnimation->loop(true);
            boubouleAnimation->setRect({0, 0, 17, 18});
            boubouleAnimation->setNbAnimations(12);

            auto animator = std::make_shared<KapEngine::Animator>(bouboule2);
            bouboule2->addComponent(animator);
            animator->addAnim(boubouleAnimation, "Idle");
            animator->addLink("Idle", "Idle");
        } catch (...) { KAP_DEBUG_ERROR("Failed to set boubouleAnimation 2 img"); }

        try {
            auto littleBullet = std::make_shared<SpriteAnimation>(bullet);
            bullet->addComponent(littleBullet);

            KapEngine::Time::ETime timer;
            timer.setSeconds(.8);
            littleBullet->setTiming(timer);
            littleBullet->setRect({0, 0, 19, 6});
            littleBullet->setNbAnimations(1);

            auto bigBullet = std::make_shared<SpriteAnimation>(bullet);
            bullet->addComponent(bigBullet);

            bigBullet->setTiming(timer);
            bigBullet->setRect({19, 0, 19, 6});
            bigBullet->setNbAnimations(1);

            auto animator = std::make_shared<KapEngine::Animator>(bullet);
            bullet->addComponent(animator);

            animator->addAnim(littleBullet, "LittleBullet");
            animator->addAnim(bigBullet, "BigBullet");

            animator->addLink("LittleBullet", "LittleBullet", "LittleBulletToLittleBullet");
            animator->addLink("BigBullet", "BigBullet", "BigBulletToBigBullet");

            animator->addLink("LittleBullet", "BigBullet", "LittleBulletToBigBullet");
            animator->addLink("BigBullet", "LittleBullet", "BigBulletToLittleBullet");
            bullet->setActive(false);
        } catch (...) { KAP_DEBUG_ERROR("Failed to set bulletAnimation img"); }

        // try {
        //     auto explosionAnimation = std::make_shared<SpriteAnimation>(explosion);
        //     KapEngine::Time::ETime timer;
        //     timer.setSeconds(.8);
        //     explosion->addComponent(explosionAnimation);
        //     explosionAnimation->setTiming(timer);
        //     explosionAnimation->loop(true);
        //     explosionAnimation->setRect({0, 50, 30, 35});
        //     explosionAnimation->setNbAnimations(12);

        //     auto animator = std::make_shared<KapEngine::Animator>(explosion);
        //     explosion->addComponent(animator);
        //     animator->addAnim(explosionAnimation, "Idle");
        //     animator->addLink("Idle", "Idle");
        // } catch (...) { KAP_DEBUG_ERROR("Failed to set explosionAnimation img"); }

        try {
            auto explosionAnimation = std::make_shared<SpriteAnimation>(explosion);
            float totalTimeAnim = 5.5f;
            KapEngine::Time::ETime timer;
            timer.setSeconds(1.0f);
            explosion->addComponent(explosionAnimation);
            explosionAnimation->setTiming(timer);
            explosionAnimation->loop(true);
            explosionAnimation->setRect({0, 0, 100, 100});
            explosionAnimation->setNbAnimations(71, 10, 8);

            auto animator = std::make_shared<KapEngine::Animator>(explosion);
            explosion->addComponent(animator);
            animator->addAnim(explosionAnimation, "Explosion");
            animator->addLink("Explosion", "Explosion");
            explosion->setActive(false);
        } catch (...) { KAP_DEBUG_ERROR("Failed to set explosionAnimation img"); }

        auto fightAnim = std::make_shared<HowToPlayAnimation>("Bouboule", bouboule);
        fightAnim->addSpriteAnimation("Bouboule", bouboule);
        fightAnim->setRect("Bouboule", {0, 0, 17, 18});
        fightAnim->setResetPosition("Bouboule", KapEngine::Tools::Vector3(600, 50, 0));
        fightAnim->addSpriteAnimation("Bouboule2", bouboule2);
        fightAnim->setRect("Bouboule2", {0, 0, 17, 18});
        fightAnim->setResetPosition("Bouboule2", KapEngine::Tools::Vector3(500, 50, 0));
        fightAnim->addSpriteAnimation("Ship", ship);
        fightAnim->setRect("Ship", {0, 0, 263, 116});
        fightAnim->setResetPosition("Ship", KapEngine::Tools::Vector3(300, 200, 0));
        fightAnim->addSpriteAnimation("Bullet", bullet);
        fightAnim->setRect("Bullet", {0, 0, 19, 6});
        fightAnim->setResetPosition("Bullet", KapEngine::Tools::Vector3(380, 266, 0));
        fightAnim->addSpriteAnimation("Explosion", explosion);
        fightAnim->setRect("Explosion", {0, 0, 100, 100});
        fightAnim->setResetPosition("Explosion", KapEngine::Tools::Vector3(600, 230, 0));
        Time::ETime timeAnim;
        timeAnim.setSeconds(3.0f);
        fightAnim->setTiming(timeAnim);
        fight->addComponent(fightAnim);
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
    
    // create bouton keyboard for Move Up
    {
        auto img = KapEngine::UI::UiFactory::createImage(scene, "Key Move Up Background");
        try {
            auto &imageComp = img->getComponent<KapEngine::UI::Image>();
            imageComp.setPathSprite("Assets/Textures/button.png");
            imageComp.setRectangle({5, 9, 655, 213});

            auto& transform = img->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(25, 87, 0));
            transform.setScale({110, 40, 0});
            transform.setParent(canvas);
        } catch (...) {
            KAP_DEBUG_ERROR("Failed to set keyboard up key img");
        }
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
        transform.setPosition(KapEngine::Tools::Vector3(25 + ((110 - inputUp.size()) / 2), 100, 0));
        transform.setParent(canvas);
    }

    // create text for Move Down
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Move Down");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Move Down");
        auto& transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(150, 150, 0));
        transform.setParent(canvas);
    }  

    // create bouton keyboard for Move Down
    {
        auto img = KapEngine::UI::UiFactory::createImage(scene, "Key Move Down Background");
        try {
            auto &imageComp = img->getComponent<KapEngine::UI::Image>();
            imageComp.setPathSprite("Assets/Textures/button.png");
            imageComp.setRectangle({5, 9, 655, 213});

            auto& transform = img->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(25, 137, 0));
            transform.setScale({110, 40, 0});
            transform.setParent(canvas);
        } catch (...) {
            KAP_DEBUG_ERROR("Failed to set keyboard down key img");
        }
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
        transform.setPosition(KapEngine::Tools::Vector3(8 + ((110 - inputDown.size()) / 2), 150, 0));
        transform.setParent(canvas);
    }

    // create text for Move Left
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Move Left");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Move Left");
        auto& transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(150, 200, 0));
        transform.setParent(canvas);
    }

    // create bouton keyboard for Move Left
    {
        auto img = KapEngine::UI::UiFactory::createImage(scene, "Key Move Left Background");
        try {
            auto &imageComp = img->getComponent<KapEngine::UI::Image>();
            imageComp.setPathSprite("Assets/Textures/button.png");
            imageComp.setRectangle({5, 9, 655, 213});

            auto& transform = img->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(25, 187, 0));
            transform.setScale({110, 40, 0});
            transform.setParent(canvas);
        } catch (...) {
            KAP_DEBUG_ERROR("Failed to set keyboard left key img");
        }
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
        transform.setPosition(KapEngine::Tools::Vector3((655 - inputLeft.size()) / 2 - 256, 200, 0));
        transform.setParent(canvas);
    }

    // create text for Move Right
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Move Right");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Move Right");
        auto& transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(150, 250, 0));
        transform.setParent(canvas);
    }

    // create bouton keyboard for Move Right
    {
        auto img = KapEngine::UI::UiFactory::createImage(scene, "Key Move Right Background");
        try {
            auto &imageComp = img->getComponent<KapEngine::UI::Image>();
            imageComp.setPathSprite("Assets/Textures/button.png");
            imageComp.setRectangle({5, 9, 655, 213});

            auto& transform = img->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(25, 237, 0));
            transform.setScale({110, 40, 0});
            transform.setParent(canvas);
        } catch (...) {
            KAP_DEBUG_ERROR("Failed to set keyboard right key img");
        }
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
        transform.setPosition(KapEngine::Tools::Vector3((655 - inputRight.size()) / 2 - 256, 250, 0));
        transform.setParent(canvas);
    }

    // create text for Shoot
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Shoot");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Shoot");
        auto& transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(150, 300, 0));
        transform.setParent(canvas);
    }

    // create bouton keyboard for Move Shoot
    {
        auto img = KapEngine::UI::UiFactory::createImage(scene, "Key Move Shoot Background");
        try {
            auto &imageComp = img->getComponent<KapEngine::UI::Image>();
            imageComp.setPathSprite("Assets/Textures/button.png");
            imageComp.setRectangle({5, 9, 655, 213});

            auto& transform = img->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(25, 287, 0));
            transform.setScale({110, 40, 0});
            transform.setParent(canvas);
        } catch (...) {
            KAP_DEBUG_ERROR("Failed to set keyboard shoot key img");
        }
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
        transform.setPosition(KapEngine::Tools::Vector3((655 - inputShoot.size()) / 2 - 256, 300, 0));
        transform.setParent(canvas);
    }
}