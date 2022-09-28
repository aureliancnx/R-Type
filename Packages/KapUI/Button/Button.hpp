/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "Component.hpp"

namespace KapEngine {
    class Component;
}

namespace KapEngine {

    namespace KapUI {

        class Button : public Component {
            public:
                Button(std::shared_ptr<GameObject> go);
                ~Button() {}

                void onAwake() override;

                void onMouseEnter() override;
                void onMouseStay() override;
                void onMouseExit() override;

            protected:
            private:
                bool _in = false;
        };

    }

}

#endif /* !BUTTON_HPP_ */
