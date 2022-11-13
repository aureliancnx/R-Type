//
// Created by leq on 13/10/22.
//

#ifndef RTYPE_SETTINGPLAYERMENU_HPP
#define RTYPE_SETTINGPLAYERMENU_HPP

#include "Menu.hpp"

namespace RType {
    class SettingPlayerMenu : public Menu {
      public:
        explicit SettingPlayerMenu(KapEngine::SceneManagement::Scene &_scene);
        ~SettingPlayerMenu() = default;

        void init() override;

      protected:
      private:
        std::shared_ptr<KapEngine::GameObject> player;
    };
} // namespace RType

#endif // RTYPE_SETTINGPLAYERMENU_HPP
