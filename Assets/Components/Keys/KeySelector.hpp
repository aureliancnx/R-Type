#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineEvents.hpp"

namespace RType {
    class KeySelector : public KapEngine::Component {
      private:
        KapEngine::Events::Key _selected;
        bool _check = false;

      public:
        KeySelector(std::shared_ptr<KapEngine::GameObject> go);
        ~KeySelector() = default;

        void onUpdate() override;

        bool keySelected(KapEngine::Events::Key &key);

        void selectKey();
    };
} // namespace RType
