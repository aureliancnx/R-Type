#include "UiText.hpp"
#include "NetStatViewer.hpp"
#include "Messages.hpp"

using namespace RType;

NetStatViewer::NetStatViewer(std::shared_ptr<KapEngine::GameObject> _gameObject, std::shared_ptr<KapMirror::Experimental::NetworkStatistics> _statObject)
    : KapEngine::Component(_gameObject, "NetStatViewer") {
    statObject = _statObject;
}

void NetStatViewer::onAwake() {
    {
        auto canvas = KapEngine::UI::UiFactory::createCanvas(getGameObject().getScene(), "Canvas NetStatViewer");

        textReceivedPackets = KapEngine::UI::UiFactory::createText(getGameObject().getScene(), "Test test");
        auto &text = textReceivedPackets->getComponent<KapEngine::UI::Text>();
        auto &transform = textReceivedPackets->getComponent<KapEngine::Transform>().getTransform();

        text.setText("Coucou");
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

        auto &text = textReceivedPackets->getComponent<KapEngine::UI::Text>();
        text.setText("Ouais bien: " + std::to_string(statObject->clientIntervalReceivedPackets));
        // TODO
    }
}
