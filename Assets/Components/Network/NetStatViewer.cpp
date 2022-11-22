#include "UiText.hpp"
#include "NetStatViewer.hpp"
#include "Messages.hpp"
#include "GameManager.hpp"
#include <sstream>
#include <iomanip>

using namespace RType;

NetStatViewer::NetStatViewer(std::shared_ptr<KapEngine::GameObject> _gameObject) : KapEngine::Component(_gameObject, "NetStatViewer") {}

void NetStatViewer::onAwake() {
    auto canvas = KapEngine::UI::UiFactory::createCanvas(getScene(), "Canvas NetStatViewer");
    // Received packets from the beginning
    {
        textReceivedPackets = KapEngine::UI::UiFactory::createText(getScene(), "Packets received");
        auto &text = textReceivedPackets->getComponent<KapEngine::UI::Text>();
        auto &transform = textReceivedPackets->getComponent<KapEngine::Transform>();

        text.setText("Packets received: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 30, 0));
        transform.setParent(canvas);
        textReceivedPackets->setActive(false);
    }
    // Sent packets from the beginning
    {
        textSentPackets = KapEngine::UI::UiFactory::createText(getScene(), "Packets Sent");
        auto &text = textSentPackets->getComponent<KapEngine::UI::Text>();
        auto &transform = textSentPackets->getComponent<KapEngine::Transform>();

        text.setText("Packets sent: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 45, 0));
        transform.setParent(canvas);
        textSentPackets->setActive(false);
    }
    // Packet per second received
    {
        textReceivedPacketsPerSec = KapEngine::UI::UiFactory::createText(getScene(), "Packets received per second");
        auto &text = textReceivedPacketsPerSec->getComponent<KapEngine::UI::Text>();
        auto &transform = textReceivedPacketsPerSec->getComponent<KapEngine::Transform>();

        text.setText("Packet/s received: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 60, 0));
        transform.setParent(canvas);
        textReceivedPacketsPerSec->setActive(false);
    }
    // Packet per second sent
    {
        textSentPacketsPerSec = KapEngine::UI::UiFactory::createText(getScene(), "Packets sent per second");
        auto &text = textSentPacketsPerSec->getComponent<KapEngine::UI::Text>();
        auto &transform = textSentPacketsPerSec->getComponent<KapEngine::Transform>();

        text.setText("Packet/s sent: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 75, 0));
        transform.setParent(canvas);
        textSentPacketsPerSec->setActive(false);
    }
    // Bytes received
    {
        textReceivedBytes = KapEngine::UI::UiFactory::createText(getScene(), "Received bytes");
        auto &text = textReceivedBytes->getComponent<KapEngine::UI::Text>();
        auto &transform = textReceivedBytes->getComponent<KapEngine::Transform>();

        text.setText("Bytes received: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 90, 0));
        transform.setParent(canvas);
        textReceivedBytes->setActive(false);
    }
    // Bytes sent
    {
        textSentBytes = KapEngine::UI::UiFactory::createText(getScene(), "Sent bytes");
        auto &text = textSentBytes->getComponent<KapEngine::UI::Text>();
        auto &transform = textSentBytes->getComponent<KapEngine::Transform>();

        text.setText("Bytes sent: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 105, 0));
        transform.setParent(canvas);
        textSentBytes->setActive(false);
    }
    // Byte/s received
    {
        textReceivedBytesPerSecond = KapEngine::UI::UiFactory::createText(getScene(), "Received bytes per second");
        auto &text = textReceivedBytesPerSecond->getComponent<KapEngine::UI::Text>();
        auto &transform = textReceivedBytesPerSecond->getComponent<KapEngine::Transform>();

        text.setText("Byte/s received: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 120, 0));
        transform.setParent(canvas);
        textReceivedBytesPerSecond->setActive(false);
    }
    // Bytes sent
    {
        textSentBytesPerSecond = KapEngine::UI::UiFactory::createText(getScene(), "Sent bytes per second");
        auto &text = textSentBytesPerSecond->getComponent<KapEngine::UI::Text>();
        auto &transform = textSentBytesPerSecond->getComponent<KapEngine::Transform>();

        text.setText("Byte/s sent: 0");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 135, 0));
        transform.setParent(canvas);
        textSentBytesPerSecond->setActive(false);
    }
    // Ping
    {
        textPing = KapEngine::UI::UiFactory::createText(getScene(), "Ping");
        auto &text = textPing->getComponent<KapEngine::UI::Text>();
        auto &transform = textPing->getComponent<KapEngine::Transform>();

        text.setText("Ping: ?");
        transform.setScale(KapEngine::Tools::Vector3(150, 35, 0));
        transform.setPosition(KapEngine::Tools::Vector3(10, 150, 0));
        transform.setParent(canvas);
        textPing->setActive(false);
    }
}

void NetStatViewer::onFixedUpdate() {
    if (KapMirror::NetworkTime::localTime() - lastRefreshTime < 500) {
        return;
    }
    bool active = GameManager::getInstance()->hasDebugMode();
    lastRefreshTime = KapMirror::NetworkTime::localTime();

    // Activate texts only in debug mode
    textReceivedPackets->setActive(active);
    textSentPackets->setActive(active);
    textReceivedPacketsPerSec->setActive(active);
    textSentPacketsPerSec->setActive(active);
    textReceivedBytes->setActive(active);
    textSentBytes->setActive(active);
    textReceivedBytesPerSecond->setActive(active);
    textSentBytesPerSecond->setActive(active);
    textPing->setActive(active);

    // Don't update texts if debug mode is not active
    if (!active) {
        lastShown = false;
        return;
    }

    // Update texts
    auto &networkStatistics = getGameObject().getComponent<KapMirror::Experimental::NetworkStatistics>();

    if (!lastShown) {
        lastShown = true;
        networkStatistics.reset();
    }

    updatePacketCounts();
    updateByteCounts();
    updatePing();
}

void NetStatViewer::updatePacketCounts() {
    // Update texts
    auto &networkStatistics = getGameObject().getComponent<KapMirror::Experimental::NetworkStatistics>();

    {
        auto &text = textReceivedPackets->getComponent<KapEngine::UI::Text>();
        text.setText("Packets received: " + std::to_string(networkStatistics.clientTotalReceivedPackets));
    }
    {
        auto &text = textSentPackets->getComponent<KapEngine::UI::Text>();
        text.setText("Packets sent: " + std::to_string(networkStatistics.clientTotalSentPackets));
    }
    {
        auto &text = textReceivedPacketsPerSec->getComponent<KapEngine::UI::Text>();
        text.setText("Packet/s received: " + std::to_string(networkStatistics.clientReceivedPacketsPerSecond));
    }
    {
        auto &text = textSentPacketsPerSec->getComponent<KapEngine::UI::Text>();
        text.setText("Packet/s sent: " + std::to_string(networkStatistics.clientSentPacketsPerSecond));
    }
}

void NetStatViewer::updateByteCounts() {
    // Update texts
    auto &networkStatistics = getGameObject().getComponent<KapMirror::Experimental::NetworkStatistics>();

    {
        auto &text = textReceivedBytes->getComponent<KapEngine::UI::Text>();
        text.setText("Bytes received: " + convertBytes(networkStatistics.clientReceivedBytesTotal));
    }
    {
        auto &text = textSentBytes->getComponent<KapEngine::UI::Text>();
        text.setText("Bytes sent: " + convertBytes(networkStatistics.clientSentBytesTotal));
    }
    {
        auto &text = textReceivedBytesPerSecond->getComponent<KapEngine::UI::Text>();
        text.setText("Byte/s received: " + convertBytes(networkStatistics.clientReceivedBytesPerSecond));
    }
    {
        auto &text = textSentBytesPerSecond->getComponent<KapEngine::UI::Text>();
        text.setText("Byte/s sent: " + convertBytes(networkStatistics.clientSentBytesPerSecond));
    }
}

void NetStatViewer::updatePing() {
    {
        auto &text = textPing->getComponent<KapEngine::UI::Text>();
        text.setText("Ping: " + std::to_string(ping) + " ms");

        KapEngine::Tools::Color color;
        // Thanks FlatUIColors
        text.setTextColor(getPingColor());
    }
}

KapEngine::Tools::Color NetStatViewer::getPingColor() {
    if (ping < 30) {
        return KapEngine::Tools::Color(0, 184, 148);
    } else if (ping < 30) {
        return KapEngine::Tools::Color(85, 239, 196);
    } else if (ping < 70) {
        return KapEngine::Tools::Color(116, 185, 255);
    } else if (ping < 100) {
        return KapEngine::Tools::Color(255, 234, 167);
    } else if (ping < 150) {
        return KapEngine::Tools::Color(253, 203, 110);
    }
    return KapEngine::Tools::Color(214, 48, 49);
}

std::string NetStatViewer::convertBytes(long bytes) {
    long gb = 1073741824, mb = 1048576, kb = 1024;

    if (bytes < 0) {
        return "0 B";
    }
    if (bytes < kb) {
        return std::to_string(bytes) + " B";
    }

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    if (bytes >= gb) {
        ss << (float) bytes / (float) gb << " GB";
    }
    if (bytes >= mb) {
        ss << (float) bytes / (float) mb << " MB";
    }
    if (bytes >= kb) {
        ss << (float) bytes / (float) kb << " KB";
    }
    return ss.str();
}

unsigned int NetStatViewer::getPing() const { return ping; }

void NetStatViewer::setPing(unsigned int _ping) { ping = _ping; }