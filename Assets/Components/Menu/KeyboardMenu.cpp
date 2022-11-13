
#include "KeyboardMenu.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"
#include "Keys/ChangeKey.hpp"
#include "Keys/ConvertEnum.hpp"

using namespace KapEngine;

RType::KeyboardMenu::KeyboardMenu(SceneManagement::Scene &scene) : Menu(scene) {}

void RType::KeyboardMenu::init() {
    // change type of display for canvas
    {
        try {
            auto &can = canvas->getComponent<KapEngine::UI::Canvas>();
            can.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
            can.setScreenCompare(KapEngine::Tools::Vector2(720, 480));
        } catch (...) { KAP_DEBUG_ERROR("Failed to resize canvas"); }
    }

    // create background
    {
        auto background = KapEngine::UI::UiFactory::createImage(scene, "Background");
        auto imageComp = std::make_shared<KapEngine::UI::Image>(background);
        imageComp->setPathSprite("Assets/Textures/setting_bg_2.png");
        imageComp->setRectangle({0, 0, 381, 200});
        background->addComponent(imageComp);

        auto &transform = background->getComponent<KapEngine::Transform>();
        transform.setPosition(KapEngine::Tools::Vector3(0, 0, 0));
        transform.setScale(KapEngine::Tools::Vector3(720, 480, 0));
        transform.setParent(canvas);
    }

    // create parent inputs
    {
        _goInputs = scene.createGameObject("InputsParent");
        _goInputs->setActive(false);

        try {
            _goInputs->getComponent<Transform>().setParent(canvas);
        } catch (...) {}
    }

    // create parent settings
    {
        _goSettings = scene.createGameObject("SettingsParent");

        try {
            _goSettings->getComponent<Transform>().setParent(canvas);
        } catch (...) {}
    }

    // init change Key Component
    {
        _chgKey = std::make_shared<ChangeKey>(canvas);

        canvas->addComponent(_chgKey);

        _chgKey->setCanvasInputSentence(_goInputs->getId());
        _chgKey->setCanvasSettings(_goSettings->getId());
    }

    // create button change up input
    {
        auto btn = scene.createGameObject("ButtonInput1");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();
        auto compTxt = std::make_shared<ConvertEnum>(btn, "upInput", "Move Up : ", KapEngine::Events::Key::EKey::UP);

        btn->addComponent(compTxt);
        btn->addComponent(btnComp);
        btnComp->setText("");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({40, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({135, 150, 0});
        transform.setScale({200, 40, 0});
        transform.setParent(_goSettings);

        btnComp->getOnClick().registerAction([this]() { _chgKey->startSelect("upInput"); });
    }

    // create button change down input
    {
        auto btn = scene.createGameObject("ButtonInput2");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();
        auto compTxt = std::make_shared<ConvertEnum>(btn, "downInput", "Move Down : ", KapEngine::Events::Key::EKey::DOWN);

        btn->addComponent(compTxt);
        btn->addComponent(btnComp);
        btnComp->setText("");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({40, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({135, 215, 0});
        transform.setScale({200, 40, 0});
        transform.setParent(_goSettings);

        btnComp->getOnClick().registerAction([this]() { _chgKey->startSelect("downInput"); });
    }

    // create button change left input
    {
        auto btn = scene.createGameObject("ButtonInput3");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();
        auto compTxt = std::make_shared<ConvertEnum>(btn, "leftInput", "Move Left : ", KapEngine::Events::Key::EKey::LEFT);

        btn->addComponent(compTxt);
        btn->addComponent(btnComp);
        btnComp->setText("");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({40, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({135, 280, 0});
        transform.setScale({200, 40, 0});
        transform.setParent(_goSettings);

        btnComp->getOnClick().registerAction([this]() { _chgKey->startSelect("leftInput"); });
    }

    // create button change right input
    {
        auto btn = scene.createGameObject("ButtonInput4");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();
        auto compTxt = std::make_shared<ConvertEnum>(btn, "rightInput", "Move Right : ", KapEngine::Events::Key::EKey::RIGHT);

        btn->addComponent(compTxt);
        btn->addComponent(btnComp);
        btnComp->setText("");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({40, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({385, 150, 0});
        transform.setScale({200, 40, 0});
        transform.setParent(_goSettings);

        btnComp->getOnClick().registerAction([this]() { _chgKey->startSelect("rightInput"); });
    }

    // create button change shoot input
    {
        auto btn = scene.createGameObject("ButtonInput5");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();
        auto compTxt = std::make_shared<ConvertEnum>(btn, "shootInput", "Shoot : ", KapEngine::Events::Key::EKey::SPACE);

        btn->addComponent(compTxt);
        btn->addComponent(btnComp);
        btnComp->setText("");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({40, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({385, 215, 0});
        transform.setScale({200, 40, 0});
        transform.setParent(_goSettings);

        btnComp->getOnClick().registerAction([this]() { _chgKey->startSelect("shootInput"); });
    }

    // create button change debug input
    {
        auto btn = scene.createGameObject("ButtonInput6");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();
        auto compTxt = std::make_shared<ConvertEnum>(btn, "debugInput", "Debug : ", KapEngine::Events::Key::EKey::F3);

        btn->addComponent(compTxt);
        btn->addComponent(btnComp);
        btnComp->setText("");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({40, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({385, 280, 0});
        transform.setScale({200, 40, 0});
        transform.setParent(_goSettings);

        btnComp->getOnClick().registerAction([this]() { _chgKey->startSelect("debugInput"); });
    }

    // create button back
    {
        auto btn = scene.createGameObject("ButtonBack");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Back");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({80, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 430, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(_goSettings);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("SettingsMenu");
        });
    }

    // create instruction
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

    // create title
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Change input");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Change your keys");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(20);

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(270, 20, 0));
        transform.setParent(_goSettings);
    }
}
