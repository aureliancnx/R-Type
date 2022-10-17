#pragma once

#include "KapEngine.hpp"
#include "MenuManager.hpp"

#include "Player/PlayerController.hpp"
#include "Animations/SpriteAnimation.hpp"
#include "RtypeNetworkManager.hpp"

namespace RType
{
    class GameManager
    {
        static GameManager *instance;

      private:
        KapEngine::KEngine *engine;

        MenuManager menuManager;

        std::shared_ptr<RtypeNetworkManager> networkManager;

      public:
        GameManager(KapEngine::KEngine *_engine);
        ~GameManager() = default;

        void launchGame();

        void launchServer();

      private:
        void registerPrefabs();

        void registerMenus();

        void registerPrefabsPlayer();

        void initSplashScreens();

        void initSinglePlayer();

        void initMultiPlayer(bool isServer);

        void initAxis();

      public:
        void startLocalMultiPlayer();

        std::shared_ptr<RtypeNetworkManager> &getNetworkManager();

        static GameManager *getInstance() { return instance; }
    };
} // namespace RType
