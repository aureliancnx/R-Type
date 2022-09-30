#include "TestNetworkManager.hpp"
#include "KapEngine.hpp"
#include "Debug.hpp"

using namespace RType::Component;

struct ChatMessage : public KapMirror::NetworkMessage {
    std::string message;

    void serialize(KapMirror::NetworkWriter& writer) override {
        writer.writeString(message);
    }

    void deserialize(KapMirror::NetworkReader& reader) override {
        message = reader.readString();
    }
};

TestNetworkManager::TestNetworkManager(std::shared_ptr<KapEngine::GameObject> go, bool _isServer) : KapMirror::NetworkManager(go) {
    isServer = _isServer;
}

void TestNetworkManager::onStart() {
    KapEngine::Debug::log("TestNetworkManager::onStart");
    if (isServer) {
        KapEngine::Debug::log("TestNetworkManager::onStart: Starting server");

        getServer()->registerHandler<ChatMessage>([this](std::shared_ptr<KapMirror::NetworkConnection> connection, ChatMessage& message) {
            KapEngine::Debug::log("TestNetworkManager: Received message from client: " + message.message);
        });
        getClient()->registerHandler<ChatMessage>([this](std::shared_ptr<KapMirror::NetworkConnection> connection, ChatMessage& message) {
            KapEngine::Debug::log("TestNetworkManager: Received message from server: " + message.message);
        });

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

    KapEngine::Debug::log("TestNetworkManager::onClientConnected: Sending message to server");
    ChatMessage message;
    message.message = "Goddess Ilias";
    connection->send(message);
}

void TestNetworkManager::onClientDisconnected(std::shared_ptr<KapMirror::NetworkConnection> connection) {
    KapEngine::Debug::log("TestNetworkManager::onClientDisconnected");
}
