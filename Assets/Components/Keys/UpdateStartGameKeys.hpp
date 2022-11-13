#pragma once

#include "KapEngine.hpp"
#include "KapEngineEvents.hpp"

namespace RType {
    class UpdateStartGameKeys : public KapEngine::Component {
      public:
        UpdateStartGameKeys(std::shared_ptr<KapEngine::GameObject> go);
        ~UpdateStartGameKeys();

        void checkInputs();

      private:
        KapEngine::Events::Input::Axis _baseAxisVert;
        KapEngine::Events::Input::Axis _baseAxisHor;
        KapEngine::Events::Input::Axis _baseAxisShoot;
        KapEngine::Events::Input::Axis _baseAxisDebug;

        bool setValueSaved(std::string const &name, KapEngine::Events::Key &key);
    };
} // namespace RType
