/*
** EPITECH PROJECT, 2022
** RType
** File description:
** SoloMenu
*/

#include "SoloMenu.hpp"

#include "KapEngineUi.hpp"
#include "Button/Button.hpp"
#include "InputField/Inputfield.hpp"

#include "Spaceship/MenuSpaceShip.hpp"

#include "Animations/SpriteAnimation.hpp"

RType::SoloMenu::SoloMenu(KapEngine::SceneManagement::Scene& _scene) : Menu(_scene) {}

void RType::SoloMenu::init() {

    //change type of display for canvas
    {
        try {
            auto &can = canvas->getComponent<KapEngine::UI::Canvas>();

            can.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
        } catch(...) {
            KAP_DEBUG_ERROR("Failed to resize canvas");
        }
    }

    //create background
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
    //create button play
    {
        auto btn = scene.createGameObject("ButtonPlay");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Play");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({80, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({449, 350, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this](){
            scene.getEngine().getSceneManager()->loadScene("Solo Game");
        });
    }
    //create button back
    {
        auto btn = scene.createGameObject("ButtonBack");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Back");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({449, 400, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this](){
            goToMenu("MainMenu");
        });
    }
    //create inputfield for pseudo
    {
        auto inpt = scene.createGameObject("InputFieldPseudo");
        auto inptComp = std::make_shared<KapEngine::UI::Inputfield>(inpt);

        inpt->addComponent(inptComp);

        auto &transform = inpt->getComponent<KapEngine::Transform>();
        transform.setScale({150, 35, 0});
        transform.setPosition({200, 100, 0});
        transform.setParent(canvas);
    }
    //create button to change spaceship
    {
        auto btn = scene.createGameObject("Choose Btn");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn, ">");
        btnComp->setTextColor(KapEngine::Tools::Color::white());
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btn->addComponent(btnComp);

        auto &transform = (KapEngine::Transform &)btn->getTransform();
        transform.setPosition(KapEngine::Tools::Vector3(350, 200, 0));
        transform.setScale(KapEngine::Tools::Vector3(40, 39, 0));
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this](){
            int currentID = 0;
            try {
                if (!KapEngine::PlayerPrefs::getString("shipID").empty()) {
                    currentID = KapEngine::PlayerPrefs::getInt("shipID");
                }
            } catch(...) {}
            currentID++;
            if (currentID > 4)
                currentID = 0;
            KapEngine::PlayerPrefs::setInt("shipID", currentID);
        });
    }

    //create spaceship animated
    {
        auto shipObj = scene.createGameObject("Animation Ship");
        auto compShipImg = std::make_shared<KapEngine::UI::Image>(shipObj);
        auto &transform = (KapEngine::Transform &)shipObj->getTransform();
        auto compSpaceShip = std::make_shared<MenuSpaceShip>(shipObj);

        shipObj->addComponent(compSpaceShip);
        compShipImg->setPathSprite("../Assets/Textures/ship1.png");
        compShipImg->setRectangle(KapEngine::Tools::Rectangle(0, 0, 263, 116));
        shipObj->addComponent(compShipImg);
        transform.setScale({132, 58, 0});
        transform.setPosition({200, 200, 0});
        transform.setParent(canvas);

        //create animation
        {
            auto animator = std::make_shared<KapEngine::Animator>(shipObj);
            auto shipAn = std::make_shared<SpriteAnimation>(shipObj);
            KapEngine::Time::ETime timer;
            timer.setSeconds(0.6f);

            shipObj->addComponent(animator);
            shipObj->addComponent(shipAn);
            shipAn->setTiming(timer);
            shipAn->loop(true);
            shipAn->bouncingVersion(true);
            shipAn->setRect(KapEngine::Tools::Rectangle(0, 0, 263, 116));
            shipAn->setNbAnimations(5);
            animator->addAnim(shipAn, "Choose Skin");
            animator->addLink("Choose Skin", "Choose Skin", "Link");
        }
    }
}

void RType::SoloMenu::goToMenu(std::string const& name) {
    auto objs = scene.getGameObjects("Canvas" + name);
    auto objCurr = scene.getGameObjects("CanvasSoloMenu");
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
        KAP_DEBUG_ERROR("Canvas called CanvasSoloMenu not found to hide it");
        return;
    }
    _found->setActive(true);
    _foundCurrent->setActive(false);
}
