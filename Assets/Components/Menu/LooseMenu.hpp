//
// Created by leq on 03/11/22.
//

#ifndef RTYPE_LOOSEMENU_HPP
#define RTYPE_LOOSEMENU_HPP

#include "Menu.hpp"

namespace RType
{
    class LooseMenu : public Menu
    {
      public:
        explicit LooseMenu(KapEngine::SceneManagement::Scene &_scene);
        ~LooseMenu() = default;

        void init() override;

      protected:
      private:
    };
} // namespace RType

#endif // RTYPE_LOOSEMENU_HPP
