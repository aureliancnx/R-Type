/*
** EPITECH PROJECT, 2022
** RType
** File description:
** MultiMenu
*/

#include "MultiMenu.hpp"

#include "KapEngineUi.hpp"
#include "Button/Button.hpp"
#include "InputField/Inputfield.hpp"

#include "Spaceship/MenuSpaceShip.hpp"

#include "Animations/SpriteAnimation.hpp"

using namespace KapEngine;

RType::MultiMenu::MultiMenu(SceneManagement::Scene& _scene) : Menu(_scene) {}

void RType::MultiMenu::init() {
    //change type of display for canvas
    {
        try {
            auto &can = canvas->getComponent<UI::Canvas>();

            can.setResizeType(UI::Canvas::RESIZE_WITH_SCREEN);
        } catch(...) {
            KAP_DEBUG_ERROR("Failed to resize canvas");
        }
    }

    //create background
    {
        auto background = UI::UiFactory::createImage(scene, "Background");
        auto imageComp = std::make_shared<UI::Image>(background);
        imageComp->setPathSprite("Assets/Textures/background_2.png");
        imageComp->setRectangle({0, 0, 755, 448});
        background->addComponent(imageComp);

        auto& transform = background->getComponent<Transform>();
        transform.setPosition(Tools::Vector3(0, 0, 0));
        transform.setScale({720, 480, 0});
        transform.setParent(canvas);
    }
    //create inputfield for ip
    {
        auto inpt = scene.createGameObject("InputFieldIp");
        auto inptComp = std::make_shared<UI::Inputfield>(inpt);

        inpt->addComponent(inptComp);

        inptComp->setInputType(UI::Inputfield::InputType::IPV4);

        auto &transform = inpt->getComponent<Transform>();
        transform.setScale({150, 35, 0});
        transform.setPosition({200, 150, 0});
        transform.setParent(canvas);
    }
    //create text for ip
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Multi Text Ip");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Enter your IP : ");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(50, 150, 0));
        transform.setParent(canvas);
    }
    //create inputfield for pseudo
    {
        auto inpt = scene.createGameObject("InputFieldPseudoMulti");
        auto inptComp = std::make_shared<KapEngine::UI::Inputfield>(inpt);

        inpt->addComponent(inptComp);

        auto &transform = inpt->getComponent<KapEngine::Transform>();
        transform.setScale({150, 35, 0});
        transform.setPosition({200, 100, 0});
        transform.setParent(canvas);
    }
    //create text for pseudo
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Multi Text Pseudo");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Enter your Pseudo : ");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(50, 100, 0));
        transform.setParent(canvas);
    }
    //create button back
    {
        auto btn = scene.createGameObject("ButtonBackMulti");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Back");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({449, 350, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this](){
            goToMenu("MainMenu");
        });
    }
    
}

void RType::MultiMenu::goToMenu(std::string const& name) {
    auto objs = scene.getGameObjects("Canvas" + name);
    auto objCurr = scene.getGameObjects("CanvasMultiMenu");
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
        KAP_DEBUG_ERROR("Canvas called CanvasMultiMenu not found to hide it");
        return;
    }
    _found->setActive(true);
    _foundCurrent->setActive(false);
}