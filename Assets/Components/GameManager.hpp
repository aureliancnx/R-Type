#pragma once

#include "KapEngine.hpp"
#include "MenuManager.hpp"

namespace RType {
    class GameManager {
        private:
        KapEngine::KapEngine& engine;

        MenuManager menuManager;

        public:
        GameManager(KapEngine::KapEngine& _engine);
        ~GameManager() = default;

        void launchGame();

        void showMenu();

        private:
        void registerScenes();
        void registerMenus();
    };
}
