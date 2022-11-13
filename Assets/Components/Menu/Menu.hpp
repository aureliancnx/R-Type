#pragma once

#include "KapEngine.hpp"
#include "UiFactory.hpp"

namespace RType {
    class Menu {
      protected:
        KapEngine::KEngine &engine;
        KapEngine::SceneManagement::Scene &scene;
        std::shared_ptr<KapEngine::GameObject> canvas;

        std::string tmpCanvasToDisplay = "";

      public:
        explicit Menu(KapEngine::SceneManagement::Scene &_scene) : engine(_scene.getEngine()), scene(_scene) {}

        ~Menu() = default;

        void __initCanvas(const std::string &name) {
            canvas = KapEngine::UI::UiFactory::createCanvas(scene, "Canvas" + name);
            canvas->setActive(false);
        }

        virtual void init() = 0;

        void show() { canvas->setActive(true); }

        void hide() {
            canvas->setActive(false);
            canvas->getScene().dump(false);
        }

      protected:
        void switchMenu(std::string const &menuName) {
            tmpCanvasToDisplay = "Canvas" + menuName;
            hide();
            scene.registerTmpActionAfterUpdate([this](KapEngine::SceneManagement::Scene &scene) {
                try {
                    auto menuCanvas = scene.findFirstGameObject(tmpCanvasToDisplay);
                    menuCanvas->setActive(true);
                } catch (...) {
                    show();
                    KAP_DEBUG_ERROR("Failed to switch menu: " + tmpCanvasToDisplay);
                }
            });
        }
    };
} // namespace RType
