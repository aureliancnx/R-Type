#pragma once

#include "KapEngine.hpp"
#include "MenuManager.hpp"

#include "Player/Player.hpp"
#include "Animations/SpriteAnimation.hpp"

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
        void initSoloPlayer();
        void registerPrefabsPlayer();
        void registerAxises();
    };
}
