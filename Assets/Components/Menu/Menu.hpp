#pragma once

#include "KapEngine.hpp"
#include "UiFactory.hpp"

namespace RType {
    class Menu {
        protected:
        KapEngine::KapEngine& engine;
        KapEngine::SceneManagement::Scene& scene;
        std::shared_ptr<KapEngine::GameObject> canvas;

        public:
        Menu(KapEngine::SceneManagement::Scene& _scene) : engine(_scene.getEngine()), scene(_scene) {}

        ~Menu() = default;

        void __initCanvas(std::string name) {
            canvas = KapEngine::UI::UiFactory::createCanvas(scene, "Canvas" + name);
            canvas->setActive(false);
        }

        virtual void init() = 0;
        virtual void goToMenu(std::string const& menuName) {}

        void show() {
            canvas->setActive(true);
        }

        void hide() {
            canvas->setActive(false);
        }
    };
}
