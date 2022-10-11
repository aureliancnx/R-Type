#include "ServerManager.hpp"
#include "KapMirror/KapMirror.hpp"
#include "Prefabs.hpp"

using namespace RType;

ServerManager::ServerManager(KapEngine::KEngine* _engine) : engine(_engine) {}

void ServerManager::launchServer() {
    KapEngine::Debug::log("Launch server");

    Prefabs::registerPlayerPrefab(*engine);

    initServer();

    engine->getSceneManager()->loadScene("Server");

    auto& scene = engine->getSceneManager()->getScene("Server");
    auto networkManager = scene.findFirstGameObject("NetworkManager");
    auto networkManagerComp = networkManager->getComponent<RtypeNetworkManager>();
    networkManagerComp.startServer();
}

void ServerManager::initServer() {
    auto scene = engine->getSceneManager()->createScene("Server");

    auto networkManager = scene->createGameObject("NetworkManager");
    auto networkManagerComp = std::make_shared<RtypeNetworkManager>(networkManager, true);
    networkManager->addComponent(networkManagerComp);
}
