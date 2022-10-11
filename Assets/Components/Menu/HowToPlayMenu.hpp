//
// Created by leq on 11/10/22.
//

#ifndef RTYPE_HOWTOPLAYMENU_HPP
#define RTYPE_HOWTOPLAYMENU_HPP

#include "Menu.hpp"

namespace RType {
    class HowToPlayMenu : public Menu {
    public:
        HowToPlayMenu(KapEngine::SceneManagement::Scene& _scene);
        ~HowToPlayMenu() = default;

        void init() override;

        void goToMenu(std::string const& menuName) override;
    protected:
    private:
    };
}

#endif //RTYPE_HOWTOPLAYMENU_HPP
