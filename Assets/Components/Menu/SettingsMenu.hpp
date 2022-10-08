//
// Created by leq on 07/10/22.
//

#ifndef RTYPE_SETTINGSMENU_HPP
#define RTYPE_SETTINGSMENU_HPP

#include "Menu.hpp"

namespace RType {
    class SettingsMenu : public Menu {
    public:
        SettingsMenu(KapEngine::SceneManagement::Scene& _scene);
        ~SettingsMenu() = default;

        void init() override;

        void goToMenu(std::string const& menuName) override;
    protected:
    private:
    };
}

#endif //RTYPE_SETTINGSMENU_HPP
