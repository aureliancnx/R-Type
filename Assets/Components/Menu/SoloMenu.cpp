#include "SoloMenu.hpp"
#include "Button/Button.hpp"
#include "Keys/UpdateStartGameKeys.hpp"

using namespace RType;

SoloMenu::SoloMenu(KapEngine::SceneManagement::Scene& _scene) : Menu(_scene) {}

void SoloMenu::init() {
    // change type of display for canvas
    {
        try {
            auto &can = canvas->getComponent<KapEngine::UI::Canvas>();
            can.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
            can.setScreenCompare(KapEngine::Tools::Vector2(720, 480));
        } catch(...) {
            KAP_DEBUG_ERROR("Failed to resize canvas");
        }
    }

    // create background
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

    // create button play
    {
        auto btn = scene.createGameObject("ButtonPlay");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();
        auto updateKeys = std::make_shared<UpdateStartGameKeys>(canvas);

        canvas->addComponent(updateKeys);

        btn->addComponent(btnComp);
        btnComp->setText("Play");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({80, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({449, 350, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            try {
                canvas->getComponent<UpdateStartGameKeys>().checkInputs();
            } catch(...) {
                KAP_DEBUG_ERROR("Failed to update inputs");
            }

            scene.getEngine().getSceneManager()->loadScene("SinglePlayer");
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

        transform.setPosition({449, 400, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("MainMenu");
        });
    }

    //Create text instruction Choose map
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Change level");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Select your level");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(20);

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(230, 50, 0));
        transform.setParent(canvas);
    }


    // Create image lvl campaign
    {
        auto lvlImg = KapEngine::UI::UiFactory::createImage(scene, "Lvl Campaign");
        auto imageComp = std::make_shared<KapEngine::UI::Image>(lvlImg);
        imageComp->setPathSprite("Assets/Textures/lvl1.png");
        imageComp->setRectangle({0, 0, 225, 224});
        lvlImg->addComponent(imageComp);

        auto& transform = lvlImg->getComponent<KapEngine::Transform>();
        transform.setPosition(KapEngine::Tools::Vector3(200, 200, 0));
        transform.setScale({150, 150, 0});
        transform.setParent(canvas);
    }

    // Create button turn left
    {
        auto btn = scene.createGameObject("ButtonLeft");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({130, 250, 0});
        transform.setScale({40, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
        });
    }

    // Create button turn right
    {
        auto btn = scene.createGameObject("ButtonRight");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({350, 250, 0});
        transform.setScale({40, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
        });
    }
}
