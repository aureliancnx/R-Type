//
// Created by leq on 12/10/22.
//

#ifndef RTYPE_SETTINGSMENU_HPP
#define RTYPE_SETTINGSMENU_HPP

#include "Menu.hpp"

namespace RType {
    class SettingsMenu : public Menu {
      public:
        explicit SettingsMenu(KapEngine::SceneManagement::Scene &_scene);
        ~SettingsMenu() = default;

        void init() override;

      protected:
      private:
    };
} // namespace RType

#endif // RTYPE_SETTINGSMENU_HPP
