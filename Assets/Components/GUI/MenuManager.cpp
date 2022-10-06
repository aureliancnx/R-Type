//
// Created by leq on 03/10/22.
//

#include "MenuManager.hpp"
#include "KapEngineUi.hpp"

#include "Button/Button.hpp"

namespace KapEngine::RType {
        MenuManager::MenuManager(std::shared_ptr<GameObject> go ) : Component(go, "Menu Manager")
        {
        }

        MenuManager::~MenuManager() = default;

        void MenuManager::onAwake() {
            _btnChangeMenu("Button Play", CANVAS_SINGLE); // MENU CANVAS to SINGLE PLAY CANVAS
            _btnChangeMenu("Button Opt", CANVAS_OPTION); // MENU CANVAS to OPTION CANVAS
            _btnChangeMenu("Button Multi", CANVAS_MULTI); // MENU CANVAS to OPTION CANVAS
            _btnChangeMenu("Option BtnMenu", CANVAS_MAIN_MENU); // MENU CANVAS to OPTION CANVAS
            _btnChangeMenu("Button Exit", CANVAS_EXIT); // STOP PROGRAM
            _btnChangeMenu("Multi BtnMenu", CANVAS_MAIN_MENU); // MULTI CANVAS TO MENU CANVAS
            _btnChangeMenu("Single BtnMenu", CANVAS_MAIN_MENU); // SINGLE CANVAS to MENU CANVAS
            _btnChangeScene("GameM BtnMenu", SCENE_DEFAULT); // BTN DANS GAME SOLO POUR REVENIR AU MENU
            _btnChangeScene("GameS BtnMenu", SCENE_DEFAULT); // BTN DANS GAME MULTI POUR REVENIR AU MENU
            _btnChangeScene("Single BtnStart", SCENE_SOLO_GAME); // SOLO BTN POUR START LE JEU
            _btnChangeScene("Multi BtnStart", SCENE_MULTI_GAME), // MULTI BTN POUR START LE JEU
            _shipModels.emplace_back("../Assets/Textures/ship1.png");
            _shipModels.emplace_back("../Assets/Textures/ship2.png");
            _shipModels.emplace_back("../Assets/Textures/ship3.png");
            _shipModels.emplace_back("../Assets/Textures/ship4.png");
            _shipModels.emplace_back("../Assets/Textures/ship5.png");
        }

        /*
        * @brief Cette fonction permet de retourner le std::string de la scene
        * @param selection
        * @return string
        */
        std::string MenuManager::getSceneNames(sceneManagerE selection) {
            switch (selection) {
                case SCENE_DEFAULT:
                    return "Default Scene";
                    break;
                case SCENE_SOLO_GAME:
                    return "Solo Game";
                    break;
                case SCENE_MULTI_GAME:
                    return "Multi Game";
                    break;
                default:
                    break;
            };
            return "";
        }
        /*
         * brief Cette fonction permet de faire le changement de Scene.
         * @param btnName, selection
         * @return void
         */
        void MenuManager::_btnChangeScene(std::string const& btnName, sceneManagerE selection)
        {
            auto currentBtn = getGameObjectConst().getScene().getGameObjects(btnName);

            if (!currentBtn.empty()) {
                auto &buttonObj = *currentBtn[0];
                if (!buttonObj.hasComponent("Button"))
                    return;
                if (selection == sceneManagerE::SCENE_DEFAULT) {
                    buttonObj.getComponent<UI::Button>().getOnClick().registerAction([this](){
                        if (getGameObject().getScene().getName() == getSceneNames(SCENE_SOLO_GAME))
                            getGameObject().getScene().getEngine().getSceneManager()->loadScene(getSceneNames(SCENE_DEFAULT));
                    });
                }
                if (selection == sceneManagerE::SCENE_DEFAULT) {
                    buttonObj.getComponent<UI::Button>().getOnClick().registerAction([this](){
                        if (getGameObject().getScene().getName() == getSceneNames(SCENE_MULTI_GAME))
                            getGameObject().getScene().getEngine().getSceneManager()->loadScene(getSceneNames(SCENE_MULTI_GAME));
                    });
                }
                if (selection == sceneManagerE::SCENE_SOLO_GAME) {
                    buttonObj.getComponent<UI::Button>().getOnClick().registerAction([this](){
                        if (getGameObject().getScene().getName() == getSceneNames(SCENE_DEFAULT))
                            getGameObject().getScene().getEngine().getSceneManager()->loadScene(getSceneNames(SCENE_SOLO_GAME));
                    });
                }
                if (selection == sceneManagerE::SCENE_MULTI_GAME) {
                    buttonObj.getComponent<UI::Button>().getOnClick().registerAction([this](){
                        if (getGameObject().getScene().getName() == getSceneNames(SCENE_DEFAULT))
                            getGameObject().getScene().getEngine().getSceneManager()->loadScene(getSceneNames(SCENE_MULTI_GAME));
                    });
                }
            }
        }

        /*
         * @brief Cette fonction permet de retourner le std::string du canvas
         * @param selection
         * @return string
         */
        std::string MenuManager::getCanvasNames(canvasManagerE selection) {
            switch (selection) {
                case CANVAS_MAIN_MENU:
                    return "CanvasMenu";
                    break;
                case CANVAS_OPTION:
                    return "CanvasOption";
                    break;
                case CANVAS_SINGLE:
                    return "CanvasSingle";
                    break;
                case CANVAS_MULTI:
                    return "CanvasMulti";
                    break;
                default:
                    break;
            };
            return "";
        }
        /*
         * @brief Cette fonction permet de faire le changement de Canvas dans le menu.
         * @param btnName, selection
         * @return void
         */
        void MenuManager::_btnChangeMenu(std::string const& btnName, canvasManagerE selection)
        {
            auto currentBtn = getGameObjectConst().getScene().getGameObjects(btnName);
            if (!currentBtn.empty()) {
                auto &buttonObj = *currentBtn[0];
                if (!buttonObj.hasComponent("Button"))
                    return;
                if (selection == canvasManagerE::CANVAS_MAIN_MENU) {
                    buttonObj.getComponent<UI::Button>().getOnClick().registerAction([this]() {
                        std::vector<std::shared_ptr<GameObject>> gameObjects = getGameObject().getScene().getAllObjects();
                        for (auto &i : gameObjects)
                            if (i->hasComponent("Canvas"))
                                i->setActive(false);
                        //get canvas to active
                        auto newCanvasObj = getGameObjectConst().getSceneConst().getGameObjects(getCanvasNames(CANVAS_MAIN_MENU));
                        if (newCanvasObj.empty())
                            return;
                        newCanvasObj[0]->setActive(true);
                    });
                }
                if (selection == canvasManagerE::CANVAS_OPTION) {
                    buttonObj.getComponent<UI::Button>().getOnClick().registerAction([this]() {
                        std::vector<std::shared_ptr<GameObject>> gameObjects = getGameObject().getScene().getAllObjects();
                        for (auto &i : gameObjects)
                            if (i->hasComponent("Canvas"))
                                i->setActive(false);
                        //get canvas to active
                        auto newCanvasObj = getGameObjectConst().getSceneConst().getGameObjects(getCanvasNames(CANVAS_OPTION));
                        if (newCanvasObj.empty())
                            return;
                        newCanvasObj[0]->setActive(true);
                    });
                }
                if (selection == canvasManagerE::CANVAS_SINGLE) {
                    buttonObj.getComponent<UI::Button>().getOnClick().registerAction([this]() {
                        std::vector<std::shared_ptr<GameObject>> gameObjects = getGameObject().getScene().getAllObjects();

                        for (auto &i : gameObjects)
                            if (i->hasComponent("Canvas"))
                                i->setActive(false);
                        //get canvas to active
                        auto newCanvasObj = getGameObjectConst().getSceneConst().getGameObjects(getCanvasNames(CANVAS_SINGLE));
                        if (newCanvasObj.empty())
                            return;
                        newCanvasObj[0]->setActive(true);
                    });
                }
                if (selection == canvasManagerE::CANVAS_MULTI) {
                    buttonObj.getComponent<UI::Button>().getOnClick().registerAction([this]() {
                        std::vector<std::shared_ptr<GameObject>> gameObjects = getGameObject().getScene().getAllObjects();

                        for (auto &i : gameObjects)
                            if (i->hasComponent("Canvas"))
                                i->setActive(false);
                        //get canvas to active
                        auto newCanvasObj = getGameObjectConst().getSceneConst().getGameObjects(getCanvasNames(CANVAS_MULTI));
                        if (newCanvasObj.empty())
                            return;
                        newCanvasObj[0]->setActive(true);
                    });
                }
                if (selection == canvasManagerE::CANVAS_EXIT) {
                    buttonObj.getComponent<UI::Button>().getOnClick().registerAction([this]() {
                        std::vector<std::shared_ptr<GameObject>> gameObjects = getGameObject().getScene().getAllObjects();
                        for (auto &i : gameObjects)
                            i->getEngine().stop();
                    });
                }
            }
        }

        /*
         * @brief Cette fonction permet de changer le path du Spaceship (img)
         * @param void
         * return void
         */
        void MenuManager::onUpdate() {
            int shipID = 0;

            if (!PlayerPrefs::getString("shipID").empty())
                shipID = PlayerPrefs::getInt("shipID");
            else
                PlayerPrefs::setInt("shipID", 0);
            if (shipID >= _shipModels.size() && shipID < 0)
                return;
            std::string path = _shipModels[shipID];
            _spaceshipSelection->getComponent<UI::Image>().setPathSprite(path);
        }
}