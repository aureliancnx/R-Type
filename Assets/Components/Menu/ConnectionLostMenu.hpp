#ifndef RTYPE_CONNECTIONLOST_HPP
#define RTYPE_CONNECTIONLOST_HPP

#include "Menu.hpp"
#include "GameManager.hpp"

namespace RType {
    class ConnectionLostMenu : public Menu {
      public:
        ConnectionLostMenu(KapEngine::SceneManagement::Scene &_scene, GameManager &_gameManager);
        ~ConnectionLostMenu() = default;

        void init() override;

      protected:
      private:
        GameManager &gameManager;
    };
} // namespace RType

#endif // RTYPE_ENDMENU_HPP
