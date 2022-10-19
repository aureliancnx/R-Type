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

        transform.setPosition({449, 430, 0});
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

        transform.setPosition({50, 430, 0});
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
        transform.setPosition(KapEngine::Tools::Vector3(280, 50, 0));
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

        transform.setPosition({20, 150, 0});
        transform.setScale({40, 230, 0});
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

        transform.setPosition({660, 150, 0});
        transform.setScale({40, 230, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
        });
    }

    // Create button level 1
    {
        auto btn = scene.createGameObject("ButtonLevel1");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("");
        btnComp->setBackground("Assets/Textures/Level Campaign/lvl1_img.png", {0, 0, 430, 433});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({90, 150, 0});
        transform.setScale({245, 230, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
        });
    }

    // Creation Name lvl 1
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Change level");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "The Lair Of The Aliens");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(15);

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(130, 260, 0));
        transform.setParent(canvas);
    }

    // Creation Auteur level 1
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Change level");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Autor : Paul Dosser");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(15);

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(110, 300, 0));
        transform.setParent(canvas);
    }

    // Creation Date creation level 1
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Change level");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Date : 22/10/2022");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(15);

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(110, 330, 0));
        transform.setParent(canvas);
    }

    // Create button level 2
    {
        auto btn = scene.createGameObject("ButtonLevel2");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("");
        btnComp->setBackground("Assets/Textures/Level Campaign/lvl2_img.png", {0, 0, 430, 433});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({380, 150, 0});
        transform.setScale({245, 230, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
        });
    }

    // Creation Name lvl 1
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Change level");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "The Lair Of The Aliens");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(15);

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(420, 260, 0));
        transform.setParent(canvas);
    }

    // Creation Auteur level 2
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Change level");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Autor : Paul Dosser");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(15);

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(400, 300, 0));
        transform.setParent(canvas);
    }

    // Creation Date creation level 2
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Change level");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Date : 24/10/2022");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(15);

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(400, 330, 0));
        transform.setParent(canvas);
    }
}
