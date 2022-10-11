#pragma once

#include "KapEngine.hpp"
#include "RtypeNetworkManager.hpp"

namespace RType {
    class ServerManager {
        private:
        KapEngine::KEngine* engine;

        std::shared_ptr<RtypeNetworkManager> networkManager;

        public:
        ServerManager(KapEngine::KEngine* _engine);
        ~ServerManager() = default;

        void launchServer();

        private:
        void initServer();

        void registerAxises();
    };
}
