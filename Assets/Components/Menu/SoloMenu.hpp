/*
** EPITECH PROJECT, 2022
** RType
** File description:
** SoloMenu
*/

#ifndef SOLOMENU_HPP_
#define SOLOMENU_HPP_

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

#endif /* !SOLOMENU_HPP_ */
