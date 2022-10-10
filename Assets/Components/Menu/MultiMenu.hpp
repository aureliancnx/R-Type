#pragma once

#include "Menu.hpp"

namespace RType {
    class MultiMenu : public Menu {
        public:
        MultiMenu(KapEngine::SceneManagement::Scene& _scene);
        ~MultiMenu() = default;

        void init() override;
    };
}
