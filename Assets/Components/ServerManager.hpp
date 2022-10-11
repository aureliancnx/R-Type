#pragma once

#include "KapEngine.hpp"
#include "RtypeNetworkManager.hpp"

namespace RType {
    class ServerManager {
        private:
        KapEngine::KEngine* engine;

        public:
        ServerManager(KapEngine::KEngine* _engine);
        ~ServerManager() = default;

        void launchServer();

        private:
        void initServer();
    };
}
