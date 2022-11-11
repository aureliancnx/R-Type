#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapMirror/KapMirror.hpp"

#include "GameMenuManager.hpp"

namespace RType {
    class NetStatViewer : public KapEngine::Component {
      private:
        long long lastRefreshTime = 0;

        std::shared_ptr<KapEngine::GameObject> textReceivedPackets;
        std::shared_ptr<KapEngine::GameObject> textSentPackets;
        std::shared_ptr<KapEngine::GameObject> textReceivedPacketsPerSec;
        std::shared_ptr<KapEngine::GameObject> textSentPacketsPerSec;
        std::shared_ptr<KapEngine::GameObject> textReceivedBytes;
        std::shared_ptr<KapEngine::GameObject> textSentBytes;
        std::shared_ptr<KapEngine::GameObject> textReceivedBytesPerSecond;
        std::shared_ptr<KapEngine::GameObject> textSentBytesPerSecond;

        std::string convertBytes(long bytes);

      public:
        explicit NetStatViewer(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~NetStatViewer() = default;

        void onAwake() override;
        void onFixedUpdate() override;
    };
} // namespace RType
