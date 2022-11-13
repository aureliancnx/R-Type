#pragma once

#include "Menu.hpp"
#include "GameManager.hpp"

namespace RType {
    class MultiMenu : public Menu {
      private:
        GameManager &gameManager;

      public:
        MultiMenu(KapEngine::SceneManagement::Scene &_scene, GameManager &_gameManager);
        ~MultiMenu() = default;

        void init() override;
    };
} // namespace RType
