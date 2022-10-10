#pragma once

#include "KapEngine.hpp"

namespace RType {
    class ServerManager {
        private:
        KapEngine::KapEngine& engine;

        public:
        ServerManager(KapEngine::KapEngine& _engine);
        ~ServerManager() = default;

        void launchServer();
    };
}
