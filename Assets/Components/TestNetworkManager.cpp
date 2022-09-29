#include "TestNetworkManager.hpp"
#include "KapEngine.hpp"
#include "Debug.hpp"

using namespace RType::Component;

TestNetworkManager::TestNetworkManager(std::shared_ptr<KapEngine::GameObject> go, bool _isServer) : KapMirror::NetworkManager(go) {
    isServer = _isServer;
}

void TestNetworkManager::onStart() {
    KapEngine::Debug::log("TestNetworkManager::onStart");
    if (isServer) {
        KapEngine::Debug::log("TestNetworkManager::onStart: Starting server");
        startServer();
    } else {
        KapEngine::Debug::log("TestNetworkManager::onStart: Starting client");
        startClient();
    }
}

void TestNetworkManager::onStartServer() {
    KapEngine::Debug::log("TestNetworkManager::onStartServer");
}

void TestNetworkManager::onStopServer() {
    KapEngine::Debug::log("TestNetworkManager::onStopServer");
}

void TestNetworkManager::onServerClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KapEngine::Debug::log("TestNetworkManager::onServerClientConnected");
}

void TestNetworkManager::onServerClientDisconnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KapEngine::Debug::log("TestNetworkManager::onServerClientDisconnected");
}

void TestNetworkManager::onStartClient() {
    KapEngine::Debug::log("TestNetworkManager::onStartClient");
}

void TestNetworkManager::onStopClient() {
    KapEngine::Debug::log("TestNetworkManager::onStopClient");
}

void TestNetworkManager::onClientConnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KapEngine::Debug::log("TestNetworkManager::onClientConnected");
}

void TestNetworkManager::onClientDisconnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KapEngine::Debug::log("TestNetworkManager::onClientDisconnected");
}
