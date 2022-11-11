#include "UiText.hpp"
#include "NetStatViewer.hpp"
#include "Messages.hpp"
#include "GameManager.hpp"

using namespace RType;

NetStatViewer::NetStatViewer(std::shared_ptr<KapEngine::GameObject> _gameObject) : KapEngine::Component(_gameObject, "NetStatViewer") {}

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
        textReceivedPackets->setActive(false);
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
        textSentPackets->setActive(false);
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
        textReceivedPacketsPerSec->setActive(false);
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
        textSentPacketsPerSec->setActive(false);
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
        textReceivedBytes->setActive(false);
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
        textSentBytes->setActive(false);
    }
}

void NetStatViewer::onFixedUpdate() {
    int updateRate = 30;
    if (KapMirror::NetworkTime::localTime() - lastRefreshTime < 1000 / updateRate) {
        return;
    }
    bool active = GameManager::getInstance()->hasDebugMode();
    lastRefreshTime = KapMirror::NetworkTime::localTime();

    auto& networkStatistics = getGameObject().getComponent<KapMirror::Experimental::NetworkStatistics>();

    // Update texts
    {
        auto& text = textReceivedPackets->getComponent<KapEngine::UI::Text>();
        text.setText("Packets received: " + std::to_string(networkStatistics.clientIntervalReceivedPackets));
        textReceivedPackets->setActive(active);
    }
    {
        auto& text = textSentPackets->getComponent<KapEngine::UI::Text>();
        text.setText("Packets sent: " + std::to_string(networkStatistics.clientIntervalSentPackets));
        textSentPackets->setActive(active);
    }
    {
        auto& text = textReceivedPacketsPerSec->getComponent<KapEngine::UI::Text>();
        text.setText("Packet/s received: " + std::to_string(networkStatistics.clientReceivedPacketsPerSecond));
        textReceivedPacketsPerSec->setActive(active);
    }
    {
        auto& text = textSentPacketsPerSec->getComponent<KapEngine::UI::Text>();
        text.setText("Packet/s sent: " + std::to_string(networkStatistics.clientSentPacketsPerSecond));
        textSentPacketsPerSec->setActive(active);
    }
    {
        auto& text = textReceivedBytes->getComponent<KapEngine::UI::Text>();
        text.setText("Bytes received: " + std::to_string(networkStatistics.clientIntervalReceivedBytes));
        textReceivedBytes->setActive(active);
    }
    {
        auto& text = textSentBytes->getComponent<KapEngine::UI::Text>();
        text.setText("Bytes sent: " + std::to_string(networkStatistics.clientIntervalSentBytes));
        textSentBytes->setActive(active);
    }
}
