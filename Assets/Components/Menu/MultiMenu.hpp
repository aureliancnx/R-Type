/*
** EPITECH PROJECT, 2022
** RType
** File description:
** MultiMenu
*/

#ifndef MULTIMENU_HPP_
#define MULTIMENU_HPP_

#include "Menu.hpp"

namespace RType {
    class MultiMenu : public Menu {
        public:
        MultiMenu(KapEngine::SceneManagement::Scene& _scene);
        ~MultiMenu() = default;

        void init() override;

        protected:
        void goToMenu(std::string const& menuName) override;
    };

}

#endif /* !MULTIMENU_HPP_ */
