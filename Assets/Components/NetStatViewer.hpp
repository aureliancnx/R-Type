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
        std::shared_ptr<KapMirror::Experimental::NetworkStatistics> statObject;

        std::shared_ptr<KapEngine::GameObject> textReceivedPackets;
        std::shared_ptr<KapEngine::GameObject> textSentPackets;
        std::shared_ptr<KapEngine::GameObject> textReceivedPacketsPerSec;
        std::shared_ptr<KapEngine::GameObject> textSentPacketsPerSec;
        std::shared_ptr<KapEngine::GameObject> textReceivedBytes;
        std::shared_ptr<KapEngine::GameObject> textSentBytes;

      public:
        explicit NetStatViewer(std::shared_ptr<KapEngine::GameObject> _gameObject, std::shared_ptr<KapMirror::Experimental::NetworkStatistics> _statObject);
        ~NetStatViewer() = default;

        void onAwake() override;
        void onFixedUpdate() override;
    };
} // namespace RType
