#pragma once

#include "KapEngine.hpp"
#include "MenuManager.hpp"

#include "Player/Player.hpp"
#include "Animations/SpriteAnimation.hpp"
#include "RtypeNetworkManager.hpp"

namespace RType {
    class GameManager {
        private:
        KapEngine::KEngine* engine;

        MenuManager menuManager;

        std::shared_ptr<RtypeNetworkManager> networkManager;

        public:
        GameManager(KapEngine::KEngine* _engine);
        ~GameManager() = default;

        void launchGame();

        private:
        void registerMenus();
        void registerPrefabsPlayer();
        void registerAxises();
        void initSplashScreens();

        void initSinglePlayer();
        void initMultiPlayer();

        public:
        void startMultiPlayer();
    };
}
