#include "ServerManager.hpp"
#include "KapMirror/KapMirror.hpp"
#include "Prefabs.hpp"

using namespace RType;

ServerManager::ServerManager(KapEngine::KEngine* _engine) : engine(_engine) {
    isStarted = false;
}

void ServerManager::start() {
    if (isStarted) {
        KapEngine::Debug::error("Server already started!");
    }

    engine->getSceneManager()->loadScene("MultiPlayer");
    networkManager->startServer();
}
