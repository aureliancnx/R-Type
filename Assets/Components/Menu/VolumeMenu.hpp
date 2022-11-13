//
// Created by leq on 12/10/22.
//

#ifndef RTYPE_VOLUMEMENU_HPP
#define RTYPE_VOLUMEMENU_HPP

#include "Menu.hpp"

namespace RType {
    class VolumeMenu : public Menu {
      public:
        explicit VolumeMenu(KapEngine::SceneManagement::Scene &_scene);
        ~VolumeMenu() = default;

        void init() override;

      protected:
      private:
    };
} // namespace RType

#endif // RTYPE_VOLUMEMENU_HPP
