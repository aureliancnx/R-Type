#include "UiText.hpp"
#include "NetStatViewer.hpp"
#include "Messages.hpp"

using namespace RType;

NetStatViewer::NetStatViewer(std::shared_ptr<KapEngine::GameObject> _gameObject)
    : KapEngine::Component(_gameObject, "NetStatViewer") {
}

void NetStatViewer::onAwake() {
    auto canvas = KapEngine::UI::UiFactory::createCanvas(getGameObject().getScene(), "Canvas NetStatViewer");
    // Received packets from the beginning
    {
        textReceivedPackets = KapEngine::UI::UiFactory::createText(getGameObject().getScene(), "Packets received");
        auto& text = textReceivedPackets->getComponent<KapEngine::UI::Text>();
        auto& transform = textReceivedPackets->getComponent<KapEngine::Transform>();

        text.setText("Packets received: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 30, 0));
        transform.setParent(canvas);
    }
    // Sent packets from the beginning
    {
        textSentPackets = KapEngine::UI::UiFactory::createText(getGameObject().getScene(), "Packets Sent");
        auto& text = textSentPackets->getComponent<KapEngine::UI::Text>();
        auto& transform = textSentPackets->getComponent<KapEngine::Transform>();

        text.setText("Packets sent: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 45, 0));
        transform.setParent(canvas);
    }
    // Packet per second received
    {
        textReceivedPacketsPerSec = KapEngine::UI::UiFactory::createText(getGameObject().getScene(), "Packets received per second");
        auto& text = textReceivedPacketsPerSec->getComponent<KapEngine::UI::Text>();
        auto& transform = textReceivedPacketsPerSec->getComponent<KapEngine::Transform>();

        text.setText("Packet/s received: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 60, 0));
        transform.setParent(canvas);
    }
    // Packet per second sent
    {
        textSentPacketsPerSec = KapEngine::UI::UiFactory::createText(getGameObject().getScene(), "Packets sent per second");
        auto& text = textSentPacketsPerSec->getComponent<KapEngine::UI::Text>();
        auto& transform = textSentPacketsPerSec->getComponent<KapEngine::Transform>();

        text.setText("Packet/s sent: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 75, 0));
        transform.setParent(canvas);
    }
    // Bytes received
    {
        textReceivedBytes = KapEngine::UI::UiFactory::createText(getGameObject().getScene(), "Received bytes");
        auto& text = textReceivedBytes->getComponent<KapEngine::UI::Text>();
        auto& transform = textReceivedBytes->getComponent<KapEngine::Transform>();

        text.setText("Bytes received: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 90, 0));
        transform.setParent(canvas);
    }
    // Bytes sent
    {
        textSentBytes = KapEngine::UI::UiFactory::createText(getGameObject().getScene(), "Sent bytes");
        auto& text = textSentBytes->getComponent<KapEngine::UI::Text>();
        auto& transform = textSentBytes->getComponent<KapEngine::Transform>();

        text.setText("Bytes sent: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 105, 0));
        transform.setParent(canvas);
    }
}

void NetStatViewer::onFixedUpdate() {
    int updateRate = 30;
    if (KapMirror::NetworkTime::localTime() - lastRefreshTime < 1000 / updateRate) {
        return;
    }
    lastRefreshTime = KapMirror::NetworkTime::localTime();
    // std::cout << "NetStatViewer: fixed Update!" << std::endl;

    auto& networkStatistics = getGameObject().getComponent<KapMirror::Experimental::NetworkStatistics>();

    // Update texts
    {
        auto& text = textReceivedPackets->getComponent<KapEngine::UI::Text>();
        text.setText("Packets received: " + std::to_string(networkStatistics.clientIntervalReceivedPackets));
    }
    {
        auto& text = textSentPackets->getComponent<KapEngine::UI::Text>();
        text.setText("Packets sent: " + std::to_string(networkStatistics.clientIntervalSentPackets));
    }
    {
        auto& text = textReceivedPacketsPerSec->getComponent<KapEngine::UI::Text>();
        text.setText("Packet/s received: " + std::to_string(networkStatistics.clientReceivedPacketsPerSecond));
    }
    {
        auto& text = textSentPacketsPerSec->getComponent<KapEngine::UI::Text>();
        text.setText("Packet/s sent: " + std::to_string(networkStatistics.clientSentPacketsPerSecond));
    }
    {
        auto& text = textReceivedBytes->getComponent<KapEngine::UI::Text>();
        text.setText("Bytes received: " + std::to_string(networkStatistics.clientIntervalReceivedBytes));
    }
    {
        auto& text = textSentBytes->getComponent<KapEngine::UI::Text>();
        text.setText("Bytes sent: " + std::to_string(networkStatistics.clientIntervalSentBytes));
    }
}
