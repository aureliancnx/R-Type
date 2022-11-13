#ifndef RTYPE_CONNECTIONLOST_HPP
#define RTYPE_CONNECTIONLOST_HPP

#include "Menu.hpp"
#include "GameManager.hpp"

namespace RType {
    class ConnectionLost : public Menu {
      public:
        ConnectionLost(KapEngine::SceneManagement::Scene &_scene, GameManager &_gameManager);
        ~ConnectionLost() = default;

        void init() override;

      protected:
      private:
        GameManager &gameManager;
    };
} // namespace RType

#endif // RTYPE_ENDMENU_HPP
