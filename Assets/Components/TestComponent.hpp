/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TestComponent
*/

#ifndef TESTCOMPONENT_HPP_
#define TESTCOMPONENT_HPP_

#include "Component.hpp"
#include "Vectors.hpp"

namespace KapEngine {
    class Component;

    namespace Tools {
        class Vector2;
    }

}

namespace RType {

    namespace Component {

        class TestComponent : public KapEngine::Component {
            public:
                TestComponent(std::shared_ptr<KapEngine::GameObject> go);
                ~TestComponent();

                void onUpdate() override;

                void onDestroy() override;

                void onGameQuit() override;

            protected:
            private:
                KapEngine::Tools::Vector2 _lastInputs;
        };

    }

}

#endif /* !TESTCOMPONENT_HPP_ */
