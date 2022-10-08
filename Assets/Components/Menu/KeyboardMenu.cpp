/*
** EPITECH PROJECT, 2022
** RType
** File description:
** KeyboardMenu
*/

#include "KeyboardMenu.hpp"

#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

#include "Button/Button.hpp"
#include "InputField/Inputfield.hpp"

#include "Keys/ChangeKey.hpp"

using namespace KapEngine;

RType::KeyboardMenu::KeyboardMenu(SceneManagement::Scene &scene) : Menu(scene)
{
}

RType::KeyboardMenu::~KeyboardMenu()
{
}

void RType::KeyboardMenu::init() {
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
        imageComp->setRectangle(KapEngine::Tools::Rectangle(0, 0, 755, 448));
        background->addComponent(imageComp);

        auto& transform = background->getComponent<KapEngine::Transform>();
        transform.setPosition(KapEngine::Tools::Vector3(0, 0, 0));
        transform.setScale(KapEngine::Tools::Vector3(720, 480, 0));
        transform.setParent(canvas);
    }
    //create parent inputs
    {
        _goInputs = scene.createGameObject("InputsParent");
        _goInputs->setActive(false);

        try {
            _goInputs->getComponent<Transform>().setParent(canvas);
        } catch(...) {}
    }
    //create parent settings
    {
        _goSettings = scene.createGameObject("SettingsParent");

        try {
            _goSettings->getComponent<Transform>().setParent(canvas);
        } catch(...) {}
    }
    //init chnage Key Component
    {
        _chgKey = std::make_shared<ChangeKey>(canvas);

        canvas->addComponent(_chgKey);

        _chgKey->setCanvasInputSentence(_goInputs->getId());
        _chgKey->setCanvasSettings(_goSettings->getId());
    }
    //create button change up input
    {
        auto btn = scene.createGameObject("ButtonInput1");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Move Up");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({60, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 150, 0});
        transform.setScale({222, 40, 0});
        transform.setParent(_goSettings);

        btnComp->getOnClick().registerAction([this](){
            _chgKey->startSelect("upInput");
        });
    }
    //create button change down input
    {
        auto btn = scene.createGameObject("ButtonInput2");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Move Down");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({60, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 200, 0});
        transform.setScale({222, 40, 0});
        transform.setParent(_goSettings);

        btnComp->getOnClick().registerAction([this](){
            _chgKey->startSelect("downInput");
        });
    }
    //create button change left input
    {
        auto btn = scene.createGameObject("ButtonInput3");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Move Left");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({60, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 250, 0});
        transform.setScale({222, 40, 0});
        transform.setParent(_goSettings);

        btnComp->getOnClick().registerAction([this](){
            _chgKey->startSelect("leftInput");
        });
    }
    //create button change right input
    {
        auto btn = scene.createGameObject("ButtonInput4");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Move Right");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({60, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 300, 0});
        transform.setScale({222, 40, 0});
        transform.setParent(_goSettings);

        btnComp->getOnClick().registerAction([this](){
            _chgKey->startSelect("rightInput");
        });
    }
    //create button change shoot input
    {
        auto btn = scene.createGameObject("ButtonInput5");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Shoot");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({60, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 350, 0});
        transform.setScale({222, 40, 0});
        transform.setParent(_goSettings);

        btnComp->getOnClick().registerAction([this](){
            _chgKey->startSelect("shootInput");
        });
    }
    // create button back
    {
        auto btn = scene.createGameObject("ButtonBack");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Back");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({460, 410, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(_goSettings);

        btnComp->getOnClick().registerAction([this]() {
            goToMenu("MainMenu");
        });
    }
    //create instruction
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Change input");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Pressed a key to change it's value");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(20);

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(190, 200, 0));
        transform.setParent(_goInputs);
    }
    //create title
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Change input");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Change your keys");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(20);

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(270, 50, 0));
        transform.setParent(_goSettings);
    }
}

void RType::KeyboardMenu::goToMenu(std::string const& name) {
    auto objs = scene.getGameObjects("Canvas" + name);
    auto objCurr = scene.getGameObjects("CanvasKeysMenu");
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
