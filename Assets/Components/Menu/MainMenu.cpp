#include "MainMenu.hpp"
#include "KapUI/KapUI.hpp"

using namespace RType;

MainMenu::MainMenu(KapEngine::SceneManagement::Scene &_scene) : Menu(_scene) {}

void MainMenu::init() {
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
        imageComp->setPathSprite("Assets/Textures/background_1.png");
        imageComp->setRectangle(KapEngine::Tools::Rectangle(0, 0, 755, 448));
        background->addComponent(imageComp);

        auto &transform = background->getComponent<KapEngine::Transform>();
        transform.setPosition(KapEngine::Tools::Vector3(0, 0, 0));
        transform.setScale(KapEngine::Tools::Vector3(720, 480, 0));
        transform.setParent(canvas);
    }

    // create title
    {
        auto title = KapEngine::UI::UiFactory::createImage(scene, "Title");
        auto imageComp = std::make_shared<KapEngine::UI::Image>(title);
        imageComp->setPathSprite("Assets/Textures/R-Type.png");
        imageComp->setRectangle(KapEngine::Tools::Rectangle(0, 0, 762, 225));
        title->addComponent(imageComp);

        auto &transform = title->getComponent<KapEngine::Transform>();
        transform.setPosition(KapEngine::Tools::Vector3(90, 20, 0));
        transform.setScale(KapEngine::Tools::Vector3(550, 180, 0));
        transform.setParent(canvas);
    }

    // create button play Solo
    {
        auto btn = scene.createGameObject("ButtonPlay");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Campaign");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({80, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 234, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("SoloMenu");
        });
    }

    // create button play multi
    {
        auto btn = scene.createGameObject("ButtonMulti");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Multiplayer");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 300, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("MultiMenu");
        });
    }

    // create button settings
    {
        auto btn = scene.createGameObject("ButtonSettings");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Settings");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({80, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({105, 375, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("SettingsMenu");
        });
    }

    // create button quit
    {
        auto btn = scene.createGameObject("ButtonQuit");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Quit");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({95, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({405, 375, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            KAP_DEBUG_LOG("QUITING GAME !");
            engine.stop();
        });
    }
}
