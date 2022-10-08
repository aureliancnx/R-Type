#pragma once

#include "Menu.hpp"

namespace RType {
    class SoloMenu : public Menu {
        public:
        SoloMenu(KapEngine::SceneManagement::Scene& _scene);
        ~SoloMenu() = default;

        void init() override;

        protected:
        void goToMenu(std::string const& menuName) override;
    };
}
