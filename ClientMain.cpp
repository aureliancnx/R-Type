#include "KapEngine.hpp"
#include "GameObject.hpp"
#include "Factory.hpp"
#include "UiFactory.hpp"
#include "Entity.hpp"
#include "Graphical/RaylibGraphical.hpp"
#include "Debug.hpp"
#include "Button/Button.hpp"
#include "GUI/MenuManager.hpp"
#include "InputField/Inputfield.hpp"
#include "Animation/SpriteAnimation/SpriteAnimation.hpp"

/*
 * @brief Cette fonction permet de créer l'animation du Choose Ship Skin
 * @param const std::shared_ptr<KapEngine::GameObject>& shipObj
 * @return void
 */
void shipAnimation(const std::shared_ptr<KapEngine::GameObject>& shipObj)
{
    auto animator = std::make_shared<KapEngine::Animator>(shipObj);
    shipObj->addComponent(animator);
    auto shipAn = std::make_shared<KapEngine::RType::SpriteAnimation>(shipObj);
    shipObj->addComponent(shipAn);
    KapEngine::Time::ETime timer;
    timer.setSeconds(0.6f);
    shipAn->setTiming(timer);
    shipAn->loop(true);
    shipAn->setRect(KapEngine::Tools::Rectangle(0, 0, 263, 116));
    shipAn->setNbAnimations(5);
    animator->addAnim(shipAn, "Choose Skin");
    animator->addLink("Choose Skin", "Choose Skin", "Link");
}

/*
 * @brief Cette fonction permet de créer la phase où on rentre les informations du joueur.
 * @param KapEngine::KapEngine *engine
 * @return void
 */
void singleScene(KapEngine::KapEngine *engine, KapEngine::RType::MenuManager &manager)
{
    // Creation des PlayerPrefs pour les path du choose skin

    try {
        auto &scene = engine->getSceneManager()->getScene(1);

        // Creation du canvas single player

        auto singleCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "CanvasSingle");
        singleCanvas->setActive(false);

        // Creation d'une image

        auto imgKap = KapEngine::UI::UiFactory::createImage(scene, "Single BG");
        auto compImgKap = std::make_shared<KapEngine::UI::Image>(imgKap);
        compImgKap->setPathSprite("../Assets/Textures/otherBG.png");
        compImgKap->setRectangle(KapEngine::Tools::Rectangle(0, 0, 755, 448));
        imgKap->addComponent(compImgKap);
        auto &trImgKap = (KapEngine::Transform &)imgKap->getTransform();
        trImgKap.setPosition(KapEngine::Tools::Vector3(0, 0, 0));
        trImgKap.setScale(KapEngine::Tools::Vector3(720, 480, 0));
        trImgKap.setParent(singleCanvas);

        // Creation d'un bouton pour lancer la partie

        auto buttonPlay = scene.createGameObject("Single BtnStart");
        auto compButtonPlay = std::make_shared<KapEngine::UI::Button>(buttonPlay, "Start");
        compButtonPlay->setBackground("../Assets/Textures/button.png", {5, 9, 655, 213});
        buttonPlay->addComponent(compButtonPlay);
        auto &trBtnPlay = buttonPlay->getComponent<KapEngine::Transform>().getTransform();
        trBtnPlay.setPosition(KapEngine::Tools::Vector3(449, 350, 0));
        trBtnPlay.setScale(KapEngine::Tools::Vector3(222, 39, 0));
        compButtonPlay->setTextPosition(KapEngine::Tools::Vector2(90, 12));
        compButtonPlay->setTextColor(KapEngine::Tools::Color::white());
        trBtnPlay.setParent(singleCanvas);

        // Creation d'un bouton pour revenir au menu
        auto buttonMenu = scene.createGameObject("Single BtnMenu");
        auto compButtonMenu = std::make_shared<KapEngine::UI::Button>(buttonMenu, "Back");
        compButtonMenu->setBackground("../Assets/Textures/button.png", {5, 9, 655, 213});
        buttonMenu->addComponent(compButtonMenu);
        auto &trBtnMenu = buttonMenu->getComponent<KapEngine::Transform>();
        trBtnMenu.setPosition(KapEngine::Tools::Vector3(449, 400, 0));
        compButtonMenu->setTextPosition(KapEngine::Tools::Vector2(90, 12));
        compButtonMenu->setTextColor(KapEngine::Tools::Color::white());
        trBtnMenu.setScale(KapEngine::Tools::Vector3(222, 39, 0));

        trBtnMenu.setParent(singleCanvas);

        // Creation d'un text devant le inputField Pseudo

        auto txtPseudo = KapEngine::UI::UiFactory::createText(scene, "Solo Text Pseudo");
        auto compTextPs = std::make_shared<KapEngine::UI::Text>(txtPseudo, "Enter your name : ");
        txtPseudo->addComponent(compTextPs);
        auto &trTxtPs = txtPseudo->getComponent<KapEngine::Transform>().getTransform();
        trTxtPs.setPosition(KapEngine::Tools::Vector3(50, 100, 0));
        trTxtPs.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        trTxtPs.setParent(singleCanvas);

        // Creation d'un inputField pour ajouter un pseudo au single player

        auto inputPseudo = scene.createGameObject("Solo InputField");
        auto compInputPs = std::make_shared<KapEngine::UI::Inputfield>(inputPseudo);
        inputPseudo->addComponent(compInputPs);
        auto &trField = inputPseudo->getComponent<KapEngine::Transform>();
        trField.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        trField.setPosition(KapEngine::Tools::Vector3(200, 100, 0));
        trField.setParent(singleCanvas);

        // Creation d'une animation Choose Ship

        auto shipAn = scene.createGameObject("Animation Ship");
        manager.setSpaceshipSelection(shipAn);
        auto compShipImg = std::make_shared<KapEngine::UI::Image>(shipAn);
        compShipImg->setPathSprite("../Assets/Textures/ship1.png");
        compShipImg->setRectangle(KapEngine::Tools::Rectangle(0, 0, 263, 116));
        shipAn->addComponent(compShipImg);
        auto &trImgShip = (KapEngine::Transform &)shipAn->getTransform();
        trImgShip.setScale({132, 58, 0});
        trImgShip.setPosition({200, 200, 0});
        trImgShip.setParent(singleCanvas);
        shipAnimation(shipAn);

        // Creation d'un Btn pour changer les skin ship

        auto btnChoose = scene.createGameObject("Choose Btn");
        auto compBtnChoose = std::make_shared<KapEngine::UI::Button>(btnChoose, " ");
        btnChoose->addComponent(compBtnChoose);
        auto &trBtnChoose = (KapEngine::Transform &)btnChoose->getTransform();
        trBtnChoose.setPosition(KapEngine::Tools::Vector3(350, 200, 0));
        trBtnChoose.setScale(KapEngine::Tools::Vector3(40, 39, 0));
        trBtnChoose.setParent(singleCanvas);

        compBtnChoose->getOnClick().registerAction([]() {
            int currentID = 0;
            try {
                if (!KapEngine::PlayerPrefs::getString("shipID").empty()) {
                    currentID = KapEngine::PlayerPrefs::getInt("shipID");
                }
            } catch(...) {}
            currentID++;
            if (currentID > 4)
                currentID = 0;
            KapEngine::PlayerPrefs::setInt("shipID", currentID);
        });

        // Creation d'un text pour le Choose Skin

        auto txtChoose = scene.createGameObject("Choose Txt");
        auto compTxtChoose = std::make_shared<KapEngine::UI::Text>(txtChoose, "Choose your skin : ");
        txtChoose->addComponent(compTxtChoose);
        auto &trTxtChoose = (KapEngine::Transform &)txtChoose->getTransform();
        trTxtChoose.setPosition(KapEngine::Tools::Vector3(50, 215, 0));
        trTxtChoose.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        trTxtChoose.setParent(singleCanvas);


    } catch (...) {}
}

/*
 * @brief Cette fonction permet de créer la phase où on rentre les informations des joueurs.
 * @param KapEngine::KapEngine *engine
 * @return void
 */
void multipleScene(KapEngine::KapEngine *engine)
{
    try {
        auto &scene = engine->getSceneManager()->getScene(1);

        // Creation du canvas Multi

        auto multiCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "CanvasMulti");
        multiCanvas->setActive(false);

        // Creation d'un BG multi

        auto imgKap = KapEngine::UI::UiFactory::createImage(scene, "Multi BG");
        auto compImgKap = std::make_shared<KapEngine::UI::Image>(imgKap);
        compImgKap->setPathSprite("../Assets/Textures/otherBG.png");
        compImgKap->setRectangle(KapEngine::Tools::Rectangle(0, 0, 755, 448));
        imgKap->addComponent(compImgKap);
        auto &trImgKap = (KapEngine::Transform &)imgKap->getTransform();
        trImgKap.setPosition(KapEngine::Tools::Vector3(0, 0, 0));
        trImgKap.setScale(KapEngine::Tools::Vector3(720, 480, 0));
        trImgKap.setParent(multiCanvas);

        // Creation d'un Input Field setIP

        auto inputFieldIP = scene.createGameObject("Multi InputField IP");
        auto compInputFieldIP = std::make_shared<KapEngine::UI::Inputfield>(inputFieldIP);
        compInputFieldIP->setInputType(KapEngine::UI::Inputfield::InputType::IPV4);
        inputFieldIP->addComponent(compInputFieldIP);
        auto &trFieldIP = inputFieldIP->getComponent<KapEngine::Transform>(); //(KapEngine::Transform &)inputField->getTransform();
        trFieldIP.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        trFieldIP.setPosition(KapEngine::Tools::Vector3(200, 150, 0));
        trFieldIP.setParent(multiCanvas);

        // Creation d'un Text devant InputField ID

        auto txtIp = KapEngine::UI::UiFactory::createText(scene, "Multi Text Pseudo");
        auto compTextIp = std::make_shared<KapEngine::UI::Text>(txtIp, "Enter your IP : ");
        txtIp->addComponent(compTextIp);
        auto &trTxtIp = txtIp->getComponent<KapEngine::Transform>().getTransform();
        trTxtIp.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        trTxtIp.setPosition(KapEngine::Tools::Vector3(50, 150, 0));
        trTxtIp.setParent(multiCanvas);

        // Creation d'un Input Field setPseudo

        auto inputFieldName = scene.createGameObject("Multi InputField name");
        auto compInputFieldName = std::make_shared<KapEngine::UI::Inputfield>(inputFieldName);
        inputFieldName->addComponent(compInputFieldName);
        auto &trFieldName = inputFieldName->getComponent<KapEngine::Transform>(); //(KapEngine::Transform &)inputField->getTransform();
        trFieldName.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        trFieldName.setPosition(KapEngine::Tools::Vector3(200, 100, 0));
        trFieldName.setParent(multiCanvas);

        // Creation d'un Text devant InputField Pseudo

        auto txtPseudo = KapEngine::UI::UiFactory::createText(scene, "Multi Text Pseudo");
        auto compTextPs = std::make_shared<KapEngine::UI::Text>(txtPseudo, "Enter your name : ");
        txtPseudo->addComponent(compTextPs);
        auto &trTxtPs = txtPseudo->getComponent<KapEngine::Transform>().getTransform();
        trTxtPs.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        trTxtPs.setPosition(KapEngine::Tools::Vector3(50, 100, 0));
        trTxtPs.setParent(multiCanvas);

        // Creation du Btn pour revenir au menu

        auto buttonMenu = scene.createGameObject("Multi BtnMenu");
        auto compButtonMenu = std::make_shared<KapEngine::UI::Button>(buttonMenu, "Back");
        compButtonMenu->setBackground("../Assets/Textures/button.png", {5, 9, 655, 213});
        buttonMenu->addComponent(compButtonMenu);
        auto &trBtnMenu = buttonMenu->getComponent<KapEngine::Transform>();
        trBtnMenu.setPosition(KapEngine::Tools::Vector3(449, 400, 0));
        trBtnMenu.setScale(KapEngine::Tools::Vector3(222, 39, 0));
        compButtonMenu->setTextPosition(KapEngine::Tools::Vector2(90, 12));
        compButtonMenu->setTextColor(KapEngine::Tools::Color::white());
        trBtnMenu.setParent(multiCanvas);

        // Creation d'un bouton start

        auto buttonPlay = scene.createGameObject("Multi BtnStart");
        auto compButtonPlay = std::make_shared<KapEngine::UI::Button>(buttonPlay, "Start");
        compButtonPlay->setBackground("../Assets/Textures/button.png", {5, 9, 655, 213});
        buttonPlay->addComponent(compButtonPlay);
        auto &trBtnPlay = buttonPlay->getComponent<KapEngine::Transform>().getTransform();
        trBtnPlay.setPosition(KapEngine::Tools::Vector3(449, 350, 0));
        trBtnPlay.setScale(KapEngine::Tools::Vector3(222, 39, 0));
        compButtonPlay->setTextPosition(KapEngine::Tools::Vector2(90, 12));
        compButtonPlay->setTextColor(KapEngine::Tools::Color::white());
        trBtnPlay.setParent(multiCanvas);

    } catch (...) {
        KAP_DEBUG_ERROR("Unknow erreur");
    }
}

/*
 * @brief Cette fonction permet de créer l'option du jeu
 * @param KapEngine::KapEngine *engine
 * @return void
 */
void optionScene(KapEngine::KapEngine *engine)
{
    try {
        auto &scene = engine->getSceneManager()->getScene(1);

        // Creation du Canvas

        auto optionCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "CanvasOption");
        optionCanvas->setActive(false);

        // Creation de l'image Background

        auto imgBg = KapEngine::UI::UiFactory::createImage(scene, "otherBG");
        auto compImgBg = std::make_shared<KapEngine::UI::Image>(imgBg);
        compImgBg->setPathSprite("../Assets/Textures/otherBG.png");
        compImgBg->setRectangle(KapEngine::Tools::Rectangle(0, 0, 503, 388));
        imgBg->addComponent(compImgBg);
        auto &trImgBg = (KapEngine::Transform &)imgBg->getTransform();
        trImgBg.setPosition(KapEngine::Tools::Vector3(0, 0, 0));
        trImgBg.setScale(KapEngine::Tools::Vector3(720, 480, 0));
        trImgBg.setParent(optionCanvas);

        // Creation du Btn Volume

        auto buttonVolume = scene.createGameObject("Volume Button");
        auto compButtonV = std::make_shared<KapEngine::UI::Button>(buttonVolume, "Volume");
        compButtonV->setBackground("../Assets/Textures/button.png", {5, 9, 655, 213});
        buttonVolume->addComponent(compButtonV);
        auto &trButtonV = (KapEngine::Transform &)buttonVolume->getTransform();
        trButtonV.setPosition(KapEngine::Tools::Vector3(249, 234, 0));
        trButtonV.setScale(KapEngine::Tools::Vector3(222, 39, 0));
        compButtonV->setTextPosition(KapEngine::Tools::Vector2(90, 12));
        compButtonV->setTextColor(KapEngine::Tools::Color::white());
        trButtonV.setParent(optionCanvas);

        // Creation du Btn KeyBoard

        auto buttonKeyBoard = scene.createGameObject("Keyboard Button");
        auto compButtonKB = std::make_shared<KapEngine::UI::Button>(buttonKeyBoard, "Key Board");
        compButtonKB->setBackground("../Assets/Textures/button.png", {5, 9, 655, 213});
        buttonKeyBoard->addComponent(compButtonKB);
        auto &trButtonKB = (KapEngine::Transform &)buttonKeyBoard->getTransform();
        trButtonKB.setPosition(KapEngine::Tools::Vector3(249, 300, 0));
        trButtonKB.setScale(KapEngine::Tools::Vector3(222, 39, 0));
        compButtonKB->setTextPosition(KapEngine::Tools::Vector2(90, 12));
        compButtonKB->setTextColor(KapEngine::Tools::Color::white());
        trButtonKB.setParent(optionCanvas);

        // Creation du Btn Menu

        auto buttonMenu = scene.createGameObject("Option BtnMenu");
        auto compMenu = std::make_shared<KapEngine::UI::Button>(buttonMenu, "Menu");
        compMenu->setBackground("../Assets/Textures/button.png", {5, 9, 655, 213});
        buttonMenu->addComponent(compMenu);
        auto &trButtonM = (KapEngine::Transform &)buttonMenu->getTransform();
        trButtonM.setPosition(KapEngine::Tools::Vector3(249, 366, 0));
        trButtonM.setScale(KapEngine::Tools::Vector3(222, 39, 0));
        compMenu->setTextPosition(KapEngine::Tools::Vector2(90, 12));
        compMenu->setTextColor(KapEngine::Tools::Color::white());
        trButtonM.setParent(optionCanvas);
    } catch (...) {}
}

/*
 * @brief Cette fonction permet de créer le menu du jeu
 * @param KapEngine::KapEngine *engine
 * @return void
 */
void createMenu(KapEngine::KapEngine *engine)
{
    try {
        auto &scene = engine->getSceneManager()->getScene(1);

        // Creation du Canvas

        auto mainMenuCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "CanvasMenu");


        // Creation de l'image MenuBG

        auto imgBg = KapEngine::UI::UiFactory::createImage(scene, "ImgMenuBG");
        auto compImgBg = std::make_shared<KapEngine::UI::Image>(imgBg);
        compImgBg->setPathSprite("../Assets/Textures/menuBG.png");
        compImgBg->setRectangle(KapEngine::Tools::Rectangle(0, 0, 755, 448));
        imgBg->addComponent(compImgBg);
        auto &trImgBg = (KapEngine::Transform &)imgBg->getTransform();
        trImgBg.setPosition(KapEngine::Tools::Vector3(0, 0, 0));
        trImgBg.setScale(KapEngine::Tools::Vector3(720, 480, 0));
        trImgBg.setParent(mainMenuCanvas);

        // Creation de l'image Title
        auto imgTitle = KapEngine::UI::UiFactory::createImage(scene, "ImgTitle");
        auto compImgTitle = std::make_shared<KapEngine::UI::Image>(imgTitle);
        compImgTitle->setPathSprite("../Assets/Textures/R-Type.png");
        compImgTitle->setRectangle(KapEngine::Tools::Rectangle(0,0,762, 225));
        imgTitle->addComponent(compImgTitle);
        auto &trImgTitle = (KapEngine::Transform &)imgTitle->getTransform();
        trImgTitle.setPosition(KapEngine::Tools::Vector3(90, 20, 0));
        trImgTitle.setScale(KapEngine::Tools::Vector3(550, 180, 0));
        trImgTitle.setParent(mainMenuCanvas);

        // Creation du Btn Single

        auto buttonPlay = scene.createGameObject("Button Play");
        auto compButtonPlay = std::make_shared<KapEngine::UI::Button>(buttonPlay, "Play");
        compButtonPlay->setBackground("../Assets/Textures/button.png", {5, 9, 655, 213});
        buttonPlay->addComponent(compButtonPlay);
        auto &trPlay = (KapEngine::Transform &)buttonPlay->getTransform();
        trPlay.setPosition(KapEngine::Tools::Vector3(249, 234, 0));
        trPlay.setScale(KapEngine::Tools::Vector3(222, 39, 0));
        compButtonPlay->setTextPosition(KapEngine::Tools::Vector2(90, 12));
        compButtonPlay->setTextColor(KapEngine::Tools::Color::white());
        trPlay.setParent(mainMenuCanvas);

        // Creation du Btn Multi
        auto buttonMulti = scene.createGameObject("Button Multi");
        auto compButtonMulti = std::make_shared<KapEngine::UI::Button>(buttonMulti, "Multi");
        compButtonMulti->setBackground("../Assets/Textures/button.png", {5, 9, 655, 213});
        buttonMulti->addComponent(compButtonMulti);
        auto &trMulti = (KapEngine::Transform &)buttonMulti->getTransform();
        trMulti.setPosition(KapEngine::Tools::Vector3(249, 300, 0));
        trMulti.setScale(KapEngine::Tools::Vector3(222, 39, 0));
        compButtonMulti->setTextPosition(KapEngine::Tools::Vector2(90, 12));
        compButtonMulti->setTextColor(KapEngine::Tools::Color::white());
        trMulti.setParent(mainMenuCanvas);

        // Creation du Btn Option

        auto buttonOpt = scene.createGameObject("Button Opt");
        auto compButtonOpt = std::make_shared<KapEngine::UI::Button>(buttonOpt, "Option");
        compButtonOpt->setBackground("../Assets/Textures/button.png", {5, 9, 655, 213});
        buttonOpt->addComponent(compButtonOpt);
        auto &trOpt = (KapEngine::Transform &)buttonOpt->getTransform();
        trOpt.setPosition(KapEngine::Tools::Vector3(105, 375, 0));
        trOpt.setScale(KapEngine::Tools::Vector3(222, 39, 0));
        compButtonOpt->setTextPosition(KapEngine::Tools::Vector2(90, 12));
        compButtonOpt->setTextColor(KapEngine::Tools::Color::white());
        trOpt.setParent(mainMenuCanvas);

        // Creation du Btn Exit

        auto buttonExit = scene.createGameObject("Button Exit");
        auto compButtonExit = std::make_shared<KapEngine::UI::Button>(buttonExit, "Exit");
        compButtonExit->setBackground("../Assets/Textures/button.png", {5, 9, 655, 213});
        buttonExit->addComponent(compButtonExit);
        auto &trExit = (KapEngine::Transform &)buttonExit->getTransform();
        trExit.setPosition(KapEngine::Tools::Vector3(405, 375, 0));
        trExit.setScale((KapEngine::Tools::Vector3(222, 39, 0)));
        compButtonExit->setTextPosition(KapEngine::Tools::Vector2(90, 12));
        compButtonExit->setTextColor(KapEngine::Tools::Color::white());
        trExit.setParent(mainMenuCanvas);
    }
    catch (...) {
        KAP_DEBUG_ERROR("Failed somaething");
    }
}

/*
 * @brief Cette fonction permet d'initialiser le window (lib, screenSize)
 * @param KapEngine::KapEngine *engine
 * @return void
 */
void initWindow(KapEngine::KapEngine *engine)
{
    engine->getSplashScreen()->setDisplayKapEngineLogo(false);
    KapEngine::Tools::Vector2 screenSize(720, 480);
    engine->setScreenSize(screenSize);
    auto raylib = std::make_shared<KapEngine::Graphical::Raylib::RaylibGraphical>(*engine->getGraphicalLibManager());
    engine->getGraphicalLibManager()->addLib(raylib);
    engine->getGraphicalLibManager()->changeLib("raylib");
}

int main(int ac, char **av)
{
    KapEngine::KapEngine engine(false);

    initWindow(&engine);
    try {
        engine.getSceneManager()->createScene("Solo Game");
        engine.getSceneManager()->createScene("Multi Game");
        // Creation du manager scene
        auto managerScene = engine.getSceneManager()->getScene(1).createGameObject("Manager Menu");
        auto compMangerScene = std::make_shared<KapEngine::RType::MenuManager>(managerScene);
        managerScene->addComponent(compMangerScene);

        // Appel de fonction
        createMenu(&engine);
        optionScene(&engine);
        singleScene(&engine, *compMangerScene);
        multipleScene(&engine);
    } catch(KapEngine::Errors::Error e) {
        KAP_DEBUG_ERROR("Problem detected: " + std::string(e.what()));
    }
    engine.run();
    return 0;
}