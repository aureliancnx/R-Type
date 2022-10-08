//
// Created by leq on 07/10/22.
//

#ifndef RTYPE_KEYBOARDMENU_HPP
#define RTYPE_KEYBOARDMENU_HPP

#include "Menu.hpp"

namespace RType {
    class KeyboardMenu : public Menu {
    public:
        KeyboardMenu(KapEngine::SceneManagement::Scene& _scene);
        ~KeyboardMenu() = default;

        void init() override;

        void goToMenu(std::string const& menuName) override;
    protected:
    private:
    };
}

#endif //RTYPE_KEYBOARDMENU_HPP
