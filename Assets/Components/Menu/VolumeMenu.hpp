//
// Created by leq on 07/10/22.
//

#ifndef RTYPE_VOLUMEMENU_HPP
#define RTYPE_VOLUMEMENU_HPP

#include "Menu.hpp"

namespace RType {
    class VolumeMenu : public Menu {
    public:
        VolumeMenu(KapEngine::SceneManagement::Scene& _scene);
        ~VolumeMenu() = default;

        void init() override;

        void goToMenu(std::string const& menuName) override;
    protected:
    private:
    };
}


#endif //RTYPE_VOLUMEMENU_HPP
