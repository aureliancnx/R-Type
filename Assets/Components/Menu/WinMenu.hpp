//
// Created by leq on 03/11/22.
//

#ifndef RTYPE_WINMENU_HPP
#define RTYPE_WINMENU_HPP

#include "Menu.hpp"

namespace RType
{
    class WinMenu : public Menu
    {
    public:
        explicit WinMenu(KapEngine::SceneManagement::Scene &_scene);
        ~WinMenu() = default;

        void init() override;

    protected:
    private:
    };
} // namespace RType

#endif //RTYPE_WINMENU_HPP
