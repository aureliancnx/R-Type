#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
    class PlayerSkin : public KapMirror::NetworkComponent {
      private:
        int skinId = 1;

      public:
        explicit PlayerSkin(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~PlayerSkin() = default;

        void setSkinId(int _skinId);

        int getSkinId() const;

        void onStart() override;

        void serialize(KapMirror::NetworkWriter &writer) override;

        void deserialize(KapMirror::NetworkReader &reader) override;

        void onObjectUpdate() override;
    };
} // namespace RType
