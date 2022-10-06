//
// Created by leq on 03/10/22.
//

#ifndef GAMEEXAMPLE_MENUMANAGER_HPP
#define GAMEEXAMPLE_MENUMANAGER_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"

#include <iostream>
#include <utility>

namespace KapEngine::RType {
        class MenuManager : public Component {
        public:
            enum canvasManagerE {
                CANVAS_MAIN_MENU,
                CANVAS_OPTION,
                CANVAS_SINGLE,
                CANVAS_MULTI,
                CANVAS_EXIT,
            };
            enum sceneManagerE {
                SCENE_DEFAULT,
                SCENE_SOLO_GAME,
                SCENE_MULTI_GAME,
            };
            explicit MenuManager(std::shared_ptr<GameObject> go);
            ~MenuManager();
            void onAwake() override;
            void onUpdate() override;
            void setSpaceshipSelection(std::shared_ptr<GameObject> go) {
                _spaceshipSelection = std::move(go);
            }
        protected:
        private:
            std::shared_ptr<GameObject> _spaceshipSelection;
            std::vector<std::string> _shipModels;
            void _btnChangeMenu(std::string const& btnName, canvasManagerE selection);
            void _btnChangeScene(std::string const& btnName, sceneManagerE selection);
            static std::string getCanvasNames(canvasManagerE);
            static std::string getSceneNames(sceneManagerE);
        };
    }

#endif //GAMEEXAMPLE_MENUMANAGER_HPP
