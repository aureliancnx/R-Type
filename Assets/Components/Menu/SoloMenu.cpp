#include "SoloMenu.hpp"
#include "KapUI/KapUI.hpp"
#include "Campaign/MenuCampaignSelector.hpp"

#include "KapEngine.hpp"

#ifndef BENJI_MODIF
#define BENJI_MODIF true
#endif

using namespace RType;

SoloMenu::SoloMenu(KapEngine::SceneManagement::Scene &_scene, GameManager &_gameManager) : Menu(_scene), gameManager(_gameManager) {}

void SoloMenu::init() {

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

        transform.setPosition({250, 400, 0});
        transform.setScale({222, 39, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            switchMenu("MainMenu");
        });
    }

    // Create text instruction Choose map
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Change level");
        auto compText = std::make_shared<KapEngine::UI::Text>(txt, "Select your level");
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();

        compText->setPoliceSize(20);

        txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(280, 20, 0));
        transform.setParent(canvas);
    }

#if !BENJI_MODIF
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
            int currentID = 0;

            try {
                if (!KapEngine::PlayerPrefs::getString("campaignID").empty())
                    currentID = KapEngine::PlayerPrefs::getInt("campaignID");
                currentID = currentID - 1;
                if (currentID < 0)
                    currentID = KapEngine::PlayerPrefs::getInt("Nb Map");
                KapEngine::PlayerPrefs::setInt("campaignID", currentID);
            } catch (...) {}
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
            int currentID = 0;

            try {
                if (!KapEngine::PlayerPrefs::getString("campaignID").empty())
                    currentID = KapEngine::PlayerPrefs::getInt("campaignID");
                currentID = currentID + 1;
                if (currentID > KapEngine::PlayerPrefs::getInt("Nb Map"))
                    currentID = 0;
                KapEngine::PlayerPrefs::setInt("campaignID", currentID);
            } catch (...) {}
        });
    }

    // Create button level 1
    {
        auto btn = scene.createGameObject("ButtonLevel1");
        auto btnComp = std::make_shared<KapEngine::UI::Button>(btn);
        auto &transform = btn->getComponent<KapEngine::Transform>();

        btn->addComponent(btnComp);
        btnComp->setText("");
        btnComp->setBackground("", {0, 0, 430, 433});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({90, 150, 0});
        transform.setScale({245, 230, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            MapScript script(&engine);

            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            try {
                canvas->getComponent<UpdateStartGameKeys>().checkInputs();
            } catch (...) { KAP_DEBUG_ERROR("Failed to update inputs"); }

            try {
                auto objName = canvas->getScene().findFirstGameObject("Text Name");
                auto compName = objName->getComponent<KapEngine::UI::Text>();
                auto name = compName.getText();

                if (name == KapEngine::PlayerPrefs::getString("Current Name Button1")) {
                    engine.getSceneManager()->loadScene("SinglePlayer");
                    script.loadScript(KapEngine::PlayerPrefs::getString("Current Path Button1"));
                    // script.closeScript();
                    // gameManager.startCampaign();
                }
            } catch (LuaException &e) { KapEngine::Debug::error(e.what()); } catch (std::exception &e) {
                KapEngine::Debug::error(e.what());
            }
        });
    }

    // Creation Name lvl 1
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Name");
        auto &compText = txt->getComponent<KapEngine::UI::Text>();
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();
        auto compDateCampaign = std::make_shared<MenuCampaign>(txt, &engine);

        compText.setPoliceSize(15);

        txt->addComponent(compDateCampaign);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(130, 260, 0));
        transform.setParent(canvas);
    }

    // Creation Auteur level 1
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Author");
        auto &compText = txt->getComponent<KapEngine::UI::Text>();
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();
        auto compAuthorCampaign = std::make_shared<MenuCampaign>(txt, &engine);

        compText.setPoliceSize(15);

        txt->addComponent(compAuthorCampaign);
        // txt->addComponent(compText);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(110, 300, 0));
        transform.setParent(canvas);
    }

    // Creation Description level 1
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text Description");
        auto &compText = txt->getComponent<KapEngine::UI::Text>();
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();
        auto compDateCampaign = std::make_shared<MenuCampaign>(txt, &engine);

        compText.setPoliceSize(15);

        txt->addComponent(compDateCampaign);
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
        btnComp->setBackground("", {0, 0, 430, 433});
        btnComp->setTextColor(KapEngine::Tools::Color::white());

        transform.setPosition({380, 150, 0});
        transform.setScale({245, 230, 0});
        transform.setParent(canvas);

        btnComp->getOnClick().registerAction([this]() {
            MapScript script(&engine);

            engine.getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
            try {
                canvas->getComponent<UpdateStartGameKeys>().checkInputs();
            } catch (...) { KAP_DEBUG_ERROR("Failed to update inputs"); }

            try {
                auto objName = canvas->getScene().findFirstGameObject("Text NameBis");
                auto compName = objName->getComponent<KapEngine::UI::Text>();
                auto name = compName.getText();

                if (name == KapEngine::PlayerPrefs::getString("Current Name Button2")) {
                    engine.getSceneManager()->loadScene("SinglePlayer");
                    script.loadScript(KapEngine::PlayerPrefs::getString("Current Path Button2"));
                    // script.closeScript();
                    // gameManager.startCampaign();
                }
            } catch (LuaException &e) { KapEngine::Debug::error(e.what()); } catch (std::exception &e) {
                KapEngine::Debug::error(e.what());
            }
        });
    }

    // Creation Name lvl 2
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text NameBis");
        auto &compText = txt->getComponent<KapEngine::UI::Text>();
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();
        auto compDateCampaign = std::make_shared<MenuCampaign>(txt, &engine);

        compText.setPoliceSize(15);

        txt->addComponent(compDateCampaign);
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(420, 260, 0));
        transform.setParent(canvas);
    }

    // Creation Auteur level 2
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text AuthorBis");
        auto &compText = txt->getComponent<KapEngine::UI::Text>();
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();
        auto compDateCampaign = std::make_shared<MenuCampaign>(txt, &engine);

        compText.setPoliceSize(15);

        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(400, 300, 0));
        transform.setParent(canvas);
    }

    // Creation Description level 2
    {
        auto txt = KapEngine::UI::UiFactory::createText(scene, "Text DescriptionBis");
        auto &compText = txt->getComponent<KapEngine::UI::Text>();
        auto &transform = txt->getComponent<KapEngine::Transform>().getTransform();
        auto compDateCampaign = std::make_shared<MenuCampaign>(txt, &engine);

        compText.setPoliceSize(15);

        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(400, 330, 0));
        transform.setParent(canvas);
    }
#else
    // create MenuCampaigne
    {
        auto menuCampaignComp = std::make_shared<MenuCampaignSelector>(canvas, gameManager);
        canvas->addComponent(menuCampaignComp);
    }

    KapEngine::Tools::Vector3 posBtn = {90, 150, 0};
    KapEngine::Tools::Vector3 sizeBtn = {245, 230, 0};
    // create first button
    {
        auto btnObj = scene.createGameObject("ButtonLevel1");

        // set transform values
        try {
            auto &transform = btnObj->getComponent<KapEngine::Transform>();
            transform.setPosition(posBtn);
            transform.setScale(sizeBtn);
            transform.setParent(canvas);
        } catch (std::exception &e) { KAP_DEBUG_ERROR(e.what()); } catch (...) {
        }

        auto button = KapEngine::UI::KapUiFactory::createButton(btnObj, "");

        // set Title
        {
            auto txt = KapEngine::UI::UiFactory::createText(scene, "LevelName");

            auto &compText = txt->getComponent<KapEngine::UI::Text>();
            compText.setPoliceSize(15);

            auto &transform = txt->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(40, 110, 0));
            transform.setParent(btnObj);
        }
        // set Author
        {
            auto txt = KapEngine::UI::UiFactory::createText(scene, "LevelAuthor");

            auto &compText = txt->getComponent<KapEngine::UI::Text>();
            compText.setPoliceSize(15);

            auto &transform = txt->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(20, 150, 0));
            transform.setParent(btnObj);
        }
        // set description
        {
            auto txt = KapEngine::UI::UiFactory::createText(scene, "LevelDescription");

            auto &compText = txt->getComponent<KapEngine::UI::Text>();
            compText.setPoliceSize(15);

            auto &transform = txt->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(20, 180, 0));
            transform.setParent(btnObj);
        }
        canvas->getComponent<MenuCampaignSelector>().setButtonLevel1(btnObj);
    }

    posBtn = {380, 150, 0};
    // create second button
    {
        auto btnObj = scene.createGameObject("ButtonLevel2");

        // set transform values
        try {
            auto &transform = btnObj->getComponent<KapEngine::Transform>();
            transform.setPosition(posBtn);
            transform.setScale(sizeBtn);
            transform.setParent(canvas);
        } catch (std::exception &e) { KAP_DEBUG_ERROR(e.what()); } catch (...) {
        }

        auto button = KapEngine::UI::KapUiFactory::createButton(btnObj, "");

        // set Title
        {
            auto txt = KapEngine::UI::UiFactory::createText(scene, "LevelName");

            auto &compText = txt->getComponent<KapEngine::UI::Text>();
            compText.setPoliceSize(15);

            auto &transform = txt->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(40, 110, 0));
            transform.setParent(btnObj);
        }
        // set Author
        {
            auto txt = KapEngine::UI::UiFactory::createText(scene, "LevelAuthor");

            auto &compText = txt->getComponent<KapEngine::UI::Text>();
            compText.setPoliceSize(15);

            auto &transform = txt->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(20, 150, 0));
            transform.setParent(btnObj);
        }
        // set description
        {
            auto txt = KapEngine::UI::UiFactory::createText(scene, "LevelDescription");

            auto &compText = txt->getComponent<KapEngine::UI::Text>();
            compText.setPoliceSize(15);

            auto &transform = txt->getComponent<KapEngine::Transform>();
            transform.setPosition(KapEngine::Tools::Vector3(20, 180, 0));
            transform.setParent(btnObj);
        }

        canvas->getComponent<MenuCampaignSelector>().setButtonLevel2(btnObj);
    }

    // create button left
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

        canvas->getComponent<MenuCampaignSelector>().setButtonLeft(btn);
    }

    // create button right
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

        canvas->getComponent<MenuCampaignSelector>().setButtonRight(btn);
    }
#endif
}
