#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapMirror/KapMirror.hpp"

#include "GameMenuManager.hpp"

namespace RType {
    class NetStatViewer : public KapEngine::Component {
      private:
        unsigned int ping;

        long long lastRefreshTime = 0;
        bool lastShown;

        std::shared_ptr<KapEngine::GameObject> textReceivedPackets;
        std::shared_ptr<KapEngine::GameObject> textSentPackets;
        std::shared_ptr<KapEngine::GameObject> textReceivedPacketsPerSec;
        std::shared_ptr<KapEngine::GameObject> textSentPacketsPerSec;
        std::shared_ptr<KapEngine::GameObject> textReceivedBytes;
        std::shared_ptr<KapEngine::GameObject> textSentBytes;
        std::shared_ptr<KapEngine::GameObject> textReceivedBytesPerSecond;
        std::shared_ptr<KapEngine::GameObject> textSentBytesPerSecond;
        std::shared_ptr<KapEngine::GameObject> textPing;

        // Updaters
        void updatePacketCounts();
        void updateByteCounts();
        void updatePing();

        // Utils
        std::string convertBytes(long bytes);
        KapEngine::Tools::Color getPingColor();

      public:
        explicit NetStatViewer(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~NetStatViewer() = default;

        void onAwake() override;
        void onFixedUpdate() override;

        unsigned int getPing() const;
        void setPing(unsigned int ping);
    };
} // namespace RType
