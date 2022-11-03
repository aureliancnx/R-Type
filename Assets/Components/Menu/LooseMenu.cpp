//
// Created by leq on 03/11/22.
//

#include "LooseMenu.hpp"
#include "KapUI/KapUI.hpp"
#include "Keys/UpdateStartGameKeys.hpp"

using namespace RType;

LooseMenu::LooseMenu(KapEngine::SceneManagement::Scene &_scene) : Menu(_scene){}

void LooseMenu::init() {

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
        imageComp->setPathSprite("Assets/Textures/background_1.png");
        imageComp->setRectangle({0, 0, 755, 448});
        background->addComponent(imageComp);

        auto& transform = background->getComponent<KapEngine::Transform>();
        transform.setPosition(KapEngine::Tools::Vector3(0, 0, 0));
        transform.setScale({720, 480, 0});
        transform.setParent(canvas);
    }

    // Create Button back menu
    {
        auto btn = scene.createGameObject("ButtonBack");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("Back Menu");
        btnComp->setBackground("Assets/Textures/button.png", {5, 9, 655, 213});
        btnComp->setTextPosition({75, 12});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({249, 366, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("MainMenu");
        });
    }

    // Create Title Scene
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Loose Menu");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "You Loose !");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(30);

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(280, 50, 0));
        transform.setParent(canvas);
    }

    // Create Score Text
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Loose Score Text");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Your final score : ");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale({150, 35, 0});
        transform.setPosition({50, 150, 0});
        transform.setParent(canvas);
    }
}