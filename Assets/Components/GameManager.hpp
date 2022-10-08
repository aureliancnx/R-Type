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

        private:
        void registerMenus();
        void registerPrefabsPlayer();
        void registerAxises();
        void initSplashScreens();

        void initSinglePlayer();
        void initMultiPlayer();
    };
}
