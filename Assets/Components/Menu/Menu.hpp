#pragma once

#include "KapEngine.hpp"
#include "UiFactory.hpp"
#include "GameManager.hpp"

namespace RType {
    class GameManager;
}

namespace RType {
    class Menu {
        protected:
        GameManager &gameManager;
        KapEngine::SceneManagement::Scene& scene;
        std::shared_ptr<KapEngine::GameObject> canvas;

        public:
        Menu(GameManager &manager, KapEngine::SceneManagement::Scene& _scene) : gameManager(manager), scene(_scene) {}

        ~Menu() = default;

        void __initCanvas(std::string name) {
            canvas = KapEngine::UI::UiFactory::createCanvas(scene, "Canvas" + name);
            canvas->setActive(false);
        }

        virtual void init() = 0;

        void show() {
            canvas->setActive(true);
        }

        void hide() {
            canvas->setActive(false);
        }
    };
}
