//
// Created by leq on 12/10/22.
//

#ifndef RTYPE_HOWTOPLAYMENU_HPP
#define RTYPE_HOWTOPLAYMENU_HPP

#include "Menu.hpp"

namespace RType {
    class HowToPlayMenu : public Menu {
      public:
        explicit HowToPlayMenu(KapEngine::SceneManagement::Scene& _scene);
        ~HowToPlayMenu() = default;

        void init() override;

      protected:
      private:
        void initKeyboardKeyDisplay();
        void initKeyboardKeyBackground();
        void initKeyboardActions();
        void initKeyboardInput();
    };
} // namespace RType

#endif // RTYPE_HOWTOPLAYMENU_HPP
