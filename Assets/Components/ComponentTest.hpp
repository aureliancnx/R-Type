#ifndef COMPONENTTEST_HPP_
#define COMPONENTTEST_HPP_

#include "Component.hpp"
#include "GameObject.hpp"

namespace KapEngine {
    class Component;
    class GameObject;
}

#include <iostream>

namespace MyGame {

    class ComponentTest : public KapEngine::Component {
        public:
            ComponentTest(std::shared_ptr<KapEngine::GameObject> &go, int threadId);
            ~ComponentTest();

            void onStart() override;
            void onUpdate() override {
                std::cout << "Thread fixedUpdate: " << std::to_string(_thread) << std::endl;
            }

        protected:
        private:
            int _thread;
    };

}

#endif /* !COMPONENTTEST_HPP_ */
