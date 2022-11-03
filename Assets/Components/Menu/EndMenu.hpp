//
// Created by leq on 03/11/22.
//

#ifndef RTYPE_ENDMENU_HPP
#define RTYPE_ENDMENU_HPP

#include "Menu.hpp"

namespace RType
{
    class EndMenu : public Menu
    {
    public:
        EndMenu(KapEngine::SceneManagement::Scene &_scene);
        ~EndMenu() = default;

        void init() override;

    protected:
    private:
    };
} // namespace RType

#endif //RTYPE_ENDMENU_HPP
