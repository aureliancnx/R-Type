#pragma once

#include "Menu.hpp"
#include "GameManager.hpp"

namespace RType {
    class SoloMenu : public Menu {
      private:
        GameManager &gameManager;

      public:
        SoloMenu(KapEngine::SceneManagement::Scene &_scene, GameManager &_gameManager);
        ~SoloMenu() = default;

        void init() override;
    };
} // namespace RType
