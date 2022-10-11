#include "ServerManager.hpp"
#include "KapMirror/KapMirror.hpp"
#include "Prefabs.hpp"

using namespace RType;

ServerManager::ServerManager(KapEngine::KEngine* _engine) : engine(_engine) {}

void ServerManager::launchServer() {
    KapEngine::Debug::log("Launch server");

    Prefabs::registerPlayerPrefab(*engine);

    registerAxises();
    initServer();

    engine->getSceneManager()->loadScene("MultiPlayer");
    networkManager->startServer();
}

void ServerManager::initServer() {
    auto scene = engine->getSceneManager()->createScene("MultiPlayer");

    auto networkManagerObject = scene->createGameObject("NetworkManager");
    networkManager = std::make_shared<RtypeNetworkManager>(networkManagerObject, true);
    networkManagerObject->addComponent(networkManager);
}

void ServerManager::registerAxises() {
    KapEngine::Events::Input::Axis _axisV("Vertical");
    KapEngine::Events::Input::Axis _axisH("Horizontal");
    KapEngine::Events::Input::Axis _axisM("Mouseinput");

    // init vertical axis
    _axisV.positiveButton = KapEngine::Events::Key::UP;
    _axisV.negativeButton = KapEngine::Events::Key::DOWN;
    _axisV.invert = true;

    // init horizontal axis
    _axisH.positiveButton = KapEngine::Events::Key::RIGHT;
    _axisH.negativeButton = KapEngine::Events::Key::LEFT;

    // init mouse axis
    _axisM.positiveButton = KapEngine::Events::Key::MOUSE_LEFT;
    _axisM.negativeButton = KapEngine::Events::Key::MOUSE_RIGHT;

    // add axis
    engine->getEventManager().getInput().addAxis(_axisH);
    engine->getEventManager().getInput().addAxis(_axisV);
    engine->getEventManager().getInput().addAxis(_axisM);
}
