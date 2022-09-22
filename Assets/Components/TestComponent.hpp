/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TestComponent
*/

#ifndef TESTCOMPONENT_HPP_
#define TESTCOMPONENT_HPP_

#include "Component.hpp"

namespace KapEngine {
    class Component;
}

namespace RType {

    namespace Component {

        class TestComponent : public KapEngine::Component {
            public:
                TestComponent(std::shared_ptr<KapEngine::GameObject> go);
                ~TestComponent();

                void onUpdate() override;

            protected:
            private:
        };

    }

}

#endif /* !TESTCOMPONENT_HPP_ */
