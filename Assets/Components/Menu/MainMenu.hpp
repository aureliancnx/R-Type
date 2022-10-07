#pragma once

#include "Menu.hpp"

namespace RType {
    class MainMenu : public Menu {
        public:
        MainMenu(KapEngine::SceneManagement::Scene& _scene);
        ~MainMenu() = default;

        void init() override;
        void goToMenu(std::string const& name) override;
    };
}
