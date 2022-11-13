//
// Created by leq on 03/11/22.
//

#include "EndMenu.hpp"
#include "KapUI/KapUI.hpp"
#include "Keys/UpdateStartGameKeys.hpp"

using namespace RType;

EndMenu::EndMenu(KapEngine::SceneManagement::Scene &_scene, GameManager &_gameManager) : Menu(_scene), gameManager(_gameManager) {}

void EndMenu::init() {

    // Change type of display for canvas
    {
        try {
            auto &can = canvas->getComponent<KapEngine::UI::Canvas>();
            can.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
            can.setScreenCompare(KapEngine::Tools::Vector2(720, 480));
        } catch (...) { KAP_DEBUG_ERROR("Failed to resize canvas"); }
    }

    // Create background
    {
        auto background = KapEngine::UI::UiFactory::createImage(scene, "Background");
        auto imageComp = std::make_shared<KapEngine::UI::Image>(background);
        imageComp->setPathSprite("Assets/Textures/background_1.png");
        imageComp->setRectangle({0, 0, 755, 448});
        background->addComponent(imageComp);

        auto &transform = background->getComponent<KapEngine::Transform>();
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

        transform.setPosition({369, 366, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            scene.getEngine().getSceneManager()->loadScene(1);
        });
    }

    // Create Title Scene
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text End Menu");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        // KapEngine::PlayerPrefs::setBool("Finish", false); // SET LORS DE LA FINAL ACTION DU JEU
        if (KapEngine::PlayerPrefs::getBool("Finish") && KapEngine::PlayerPrefs::hasKey("Finish"))
            compText->setText("You Win !");
        if (!KapEngine::PlayerPrefs::getBool("Finish") && KapEngine::PlayerPrefs::hasKey("Finish"))
            compText->setText("You Loose !");
        compText->setPoliceSize(30);
        txt->addComponent(compText);

        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(280, 50, 0));
        transform.setParent(canvas);
    }

    // Create Score Text
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "End Score Text");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Your final score : ");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(20);
        txt->addComponent(compText);
        transform.setScale({150, 35, 0});
        transform.setPosition({50, 250, 0});
        transform.setParent(canvas);
    }

    // Create Value score
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Value Score Text");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(20);
        if (KapEngine::PlayerPrefs::hasKey("ScorePlayer"))
            compText->setText(std::to_string(KapEngine::PlayerPrefs::getInt("ScorePlayer")));
        else
            compText->setText("NaN");
        txt->addComponent(compText);
        transform.setScale({150, 35, 0});
        transform.setPosition({250, 250, 0});
        transform.setParent(canvas);
    }

    // Create Final text
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Final Text");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Your game is over, here is your score from the previous game.");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        txt->addComponent(compText);
        transform.setScale({150, 35, 0});
        transform.setPosition({120, 150, 0});
        transform.setParent(canvas);
    }
}