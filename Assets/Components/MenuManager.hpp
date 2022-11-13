#pragma once

#include "Menu/Menu.hpp"
#include "Dictionary.hpp"

namespace RType {
    class MenuManager {
      private:
        KapEngine::Dictionary<std::string, std::shared_ptr<Menu>> menus;

      public:
        MenuManager() = default;
        ~MenuManager() = default;

        void registerMenu(const std::string &name, const std::shared_ptr<Menu> &menu) {
            menus[name] = menu;
            menu->__initCanvas(name);
            menu->init();
        }

        void showMenu(const std::string &name) {
            std::shared_ptr<Menu> menu;
            if (menus.tryGetValue(name, menu)) {
                menu->show();
            } else {
                throw KapEngine::Errors::Error("Menu " + name + " not found");
            }
        }

        void hideMenu(const std::string &name) {
            std::shared_ptr<Menu> menu;
            if (menus.tryGetValue(name, menu)) {
                menu->hide();
            } else {
                throw KapEngine::Errors::Error("Menu " + name + " not found");
            }
        }
    };
} // namespace RType
