/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RaylibGraphical
*/

#ifndef RAYLIBGRAPHICAL_HPP_
#define RAYLIBGRAPHICAL_HPP_

#include <memory>

#include "GraphicalLib.hpp"
#include "Encapsulation/RaylibEncapsulation.hpp"

namespace KapEngine {
    class KapEngine;

    namespace Graphical {
        class GraphicalLibManager;
        class GraphicalLib;
    }

}

namespace KapEngine {

    namespace Graphical {

        class RaylibGraphical : public GraphicalLib {
            public:
                RaylibGraphical(GraphicalLibManager &manager);
                ~RaylibGraphical();

                void clearCache() override;
                void stopDisplay() override;
                void startDisplay() override;

                void clear() override;
                void display() override;
                void getEvents() override {}

                float getJoystikValue(int gamepadId, int joystickId) override {}

            protected:
            private:
                std::unique_ptr<RaylibEncapsulation> raylib;
        };

    }
}


#endif /* !RAYLIBGRAPHICAL_HPP_ */
