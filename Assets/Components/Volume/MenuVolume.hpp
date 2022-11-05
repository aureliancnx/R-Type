#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

namespace RType {
    class MenuVolume : public KapEngine::Component {
      private:
        std::vector<std::string> _type;
        std::shared_ptr<KapEngine::GameObject> _txt;
        int lastValue;

      public:
        MenuVolume(std::shared_ptr<KapEngine::GameObject> go);
        ~MenuVolume();

        void onUpdate() override;

        void onAwake() override;

      private:
        void foundText();
    };
} // namespace RType
