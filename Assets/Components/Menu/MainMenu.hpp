#pragma once

#include "Menu.hpp"

namespace RType {
    class MainMenu : public Menu {
        public:
        MainMenu(GameManager &manager, KapEngine::SceneManagement::Scene& _scene);
        ~MainMenu() = default;

        void init() override;
    };
}
