/*
** EPITECH PROJECT, 2022
** RType
** File description:
** KeyboardMenu
*/

#ifndef KEYBOARDMENU_HPP_
#define KEYBOARDMENU_HPP_

#include "Menu.hpp"

#include "Keys/ChangeKey.hpp"

namespace RType {

    class KeyboardMenu : public Menu {
        public:
            KeyboardMenu(KapEngine::SceneManagement::Scene &_scene);
            ~KeyboardMenu();

            void init() override;
            void goToMenu(std::string const& name) override;

        protected:
        private:
            std::shared_ptr<KapEngine::GameObject> _goSettings;
            std::shared_ptr<KapEngine::GameObject> _goInputs;
            std::shared_ptr<ChangeKey> _chgKey;
    };

}

#endif /* !KEYBOARDMENU_HPP_ */
