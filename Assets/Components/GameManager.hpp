#pragma once

#include "KapEngine.hpp"
#include "MenuManager.hpp"

#include "Player/PlayerController.hpp"
#include "Animations/SpriteAnimation.hpp"
#include "Network/RtypeNetworkManager.hpp"

namespace RType {
    class GameManager {
        static GameManager *instance;

      private:
        KapEngine::KEngine *engine;

        MenuManager menuManager;

        std::shared_ptr<RtypeNetworkManager> networkManager;

        bool displaySplashScreens = true;
        bool debugMode = false;

      public:
        explicit GameManager(KapEngine::KEngine *_engine, bool splashScreens = true);
        ~GameManager() = default;

        void launchGame();

        void launchServer();

      private:
        void registerPrefabs();

        void registerMenus();

        void initSplashScreens();

        void initSinglePlayer();

        void initMultiPlayer(bool isServer);

        void initEndScene();

        void initAxis();

      public:
        void startLocalMultiPlayer(const std::string &ip, const std::string &port);

        void startCampaign(const std::string &pathMap);

        bool hasDebugMode() const;

        void toggleDebugMode();

        MenuManager &getMenuManager();

        std::shared_ptr<RtypeNetworkManager> &getNetworkManager();

        static GameManager *getInstance() { return instance; }
    };
} // namespace RType
