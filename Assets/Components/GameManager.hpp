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

        void swichMenu(std::string const& currentMenu, std::string const& menuName);

        KapEngine::KapEngine &getEngine() {
            return engine;
        }

        private:
        void registerScenes();
        void registerMenus();
    };
}
