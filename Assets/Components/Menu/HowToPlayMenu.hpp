/*
** EPITECH PROJECT, 2022
** RType
** File description:
** HowToPlayMenu
*/

#ifndef RTYPE_HOWTOPLAYMENU_HPP
#define RTYPE_HOWTOPLAYMENU_HPP

#include "Menu.hpp"
#include "Keys/ChangeKey.hpp"

namespace RType {
    class HowToPlayMenu : public Menu {
      public:
        explicit HowToPlayMenu(KapEngine::SceneManagement::Scene &_scene);
        ~HowToPlayMenu() = default;

        void init() override;

      protected:
      private:
        void initFightAnimation();
        void initKeyboardKeyDisplay();

        std::shared_ptr<KapEngine::GameObject> _goSettings;
        std::shared_ptr<KapEngine::GameObject> _goInputs;
        std::shared_ptr<ChangeKey> _chgKey;
    };
} // namespace RType

#endif // RTYPE_HOWTOPLAYMENU_HPP
