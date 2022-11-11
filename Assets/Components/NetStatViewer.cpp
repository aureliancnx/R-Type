#include "UiText.hpp"
#include "NetStatViewer.hpp"
#include "Messages.hpp"

using namespace RType;

NetStatViewer::NetStatViewer(std::shared_ptr<KapEngine::GameObject> _gameObject, std::shared_ptr<KapMirror::Experimental::NetworkStatistics> _statObject)
    : KapEngine::Component(_gameObject, "NetStatViewer") {
    statObject = _statObject;
}

void NetStatViewer::onAwake() {
    auto canvas = KapEngine::UI::UiFactory::createCanvas(getGameObject().getScene(), "Canvas NetStatViewer");
    {
        textReceivedPackets = KapEngine::UI::UiFactory::createText(getGameObject().getScene(), "Packets received");
        auto &text = textReceivedPackets->getComponent<KapEngine::UI::Text>();
        auto &transform = textReceivedPackets->getComponent<KapEngine::Transform>().getTransform();

        text.setText("Packets received: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(50, 150, 0));
        transform.setParent(canvas);
    }
    {
        textSentPackets = KapEngine::UI::UiFactory::createText(getGameObject().getScene(), "Packets Sent");
        auto &text = textSentPackets->getComponent<KapEngine::UI::Text>();
        auto &transform = textSentPackets->getComponent<KapEngine::Transform>().getTransform();

        text.setText("Packets sent: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(50, 150, 0));
        transform.setParent(canvas);
    }
    {
        textReceivedPacketsPerSec = KapEngine::UI::UiFactory::createText(getGameObject().getScene(), "Packets received per second");
        auto &text = textReceivedPacketsPerSec->getComponent<KapEngine::UI::Text>();
        auto &transform = textReceivedPacketsPerSec->getComponent<KapEngine::Transform>().getTransform();

        text.setText("Packet/s received: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(50, 150, 0));
        transform.setParent(canvas);
    }
    {
        textSentPacketsPerSec = KapEngine::UI::UiFactory::createText(getGameObject().getScene(), "Packets sent per second");
        auto &text = textSentPacketsPerSec->getComponent<KapEngine::UI::Text>();
        auto &transform = textSentPacketsPerSec->getComponent<KapEngine::Transform>().getTransform();

        text.setText("Packet/s sent: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(50, 150, 0));
        transform.setParent(canvas);
    }
}

void NetStatViewer::onFixedUpdate() {
    int updateRate = 30;
    if (KapMirror::NetworkTime::localTime() - lastRefreshTime > 1000 / updateRate) {
        lastRefreshTime = KapMirror::NetworkTime::localTime();
        std::cout << "NetStatViewer: fixed Update!" << std::endl;

        {
            auto &text = textReceivedPackets->getComponent<KapEngine::UI::Text>();
            text.setText("Packets received: " + std::to_string(statObject->clientIntervalReceivedPackets));
        }
        // TODO
    }
}