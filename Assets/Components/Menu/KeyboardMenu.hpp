#pragma once

#include "Menu.hpp"
#include "Keys/ChangeKey.hpp"

namespace RType {
    class KeyboardMenu : public Menu {
      private:
        std::shared_ptr<KapEngine::GameObject> _goSettings;
        std::shared_ptr<KapEngine::GameObject> _goInputs;
        std::shared_ptr<ChangeKey> _chgKey;

      public:
        KeyboardMenu(KapEngine::SceneManagement::Scene &_scene);
        ~KeyboardMenu() = default;

        void init() override;
    };
} // namespace RType
