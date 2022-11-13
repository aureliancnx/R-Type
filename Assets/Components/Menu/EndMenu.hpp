//
// Created by leq on 03/11/22.
//

#ifndef RTYPE_ENDMENU_HPP
#define RTYPE_ENDMENU_HPP

#include "Menu.hpp"
#include "GameManager.hpp"

namespace RType {
    class EndMenu : public Menu {
      public:
        EndMenu(KapEngine::SceneManagement::Scene &_scene, GameManager &_gameManager);
        ~EndMenu() = default;

        void init() override;

      protected:
      private:
        GameManager &gameManager;
    };
} // namespace RType

#endif // RTYPE_ENDMENU_HPP
