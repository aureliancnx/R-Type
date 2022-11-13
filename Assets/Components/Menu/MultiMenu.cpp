#include "MultiMenu.hpp"
#include "KapUI/KapUI.hpp"
#include "Animations/SpriteAnimation.hpp"

using namespace RType;

MultiMenu::MultiMenu(KapEngine::SceneManagement::Scene &_scene, GameManager &_gameManager) : Menu(_scene), gameManager(_gameManager) {}

void MultiMenu::init() {
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
        imageComp->setPathSprite("Assets/Textures/select_bg.png");
        imageComp->setRectangle({0, 0, 720, 600});
        background->addComponent(imageComp);

        auto &transform = background->getComponent<KapEngine::Transform>();
        transform.setPosition(KapEngine::Tools::Vector3(0, 0, 0));
        transform.setScale({720, 480, 0});
        transform.setParent(canvas);
    }

    // create inputfield for ip
    std::shared_ptr<KapEngine::UI::Inputfield> ipText;
    {
        auto inpt = scene.createGameObject("InputFieldIp");

        ipText = std::make_shared<KapEngine::UI::Inputfield>(inpt);
        inpt->addComponent(ipText);
        ipText->setPlaceholderText("127.0.0.1");

        auto &transform = inpt->getComponent<KapEngine::Transform>();
        transform.setScale({150, 15, 0});
        transform.setPosition({200, 150, 0});
        transform.setParent(canvas);
    }

    // create text for ip
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Multi Text Ip");

        auto txtComp = std::make_shared<KapEngine::UI::Text>(txt, "Enter your IP : ");
        txt->addComponent(txtComp);

        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(50, 150, 0));
        transform.setParent(canvas);
    }

    std::shared_ptr<KapEngine::UI::Inputfield> portText;
    // create inputfield for port
    {
        auto inpt = scene.createGameObject("InputFieldPort");
        portText = std::make_shared<KapEngine::UI::Inputfield>(inpt);
        inpt->addComponent(portText);

        portText->setPlaceholderText("7777");
        portText->setInputType(KapEngine::UI::Inputfield::InputType::NUMBER);

        auto &transform = inpt->getComponent<KapEngine::Transform>();
        transform.setScale({50, 15, 0});
        transform.setPosition({200, 190, 0});
        transform.setParent(canvas);
    }

    // create text for ip
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Multi Text Port");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Enter your Port : ");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(50, 190, 0));
        transform.setParent(canvas);
    }

    // create button join
    {
        auto btn = scene.createGameObject("ButtonPlay");

        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        btn->addComponent(btnComp);

        btnComp->setText("Join");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({80, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());
        btnComp->getOnClick().registerAction([this, ipText, portText]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            gameManager.startLocalMultiPlayer(ipText->getText(), portText->getText());
        });

        auto &transform = btn->getComponent<KapEngine::Transform>();
        transform.setPosition({250, 250, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);
    }

    // create button back
    {
        auto btn = scene.createGameObject("ButtonBackMulti");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Back");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({250, 400, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("MainMenu");
        });
    }
}
