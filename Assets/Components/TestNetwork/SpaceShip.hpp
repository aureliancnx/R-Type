#pragma once

#include "KapEngine.hpp"

namespace RType {
namespace Component {
    class SpaceShip : public KapEngine::Component {
        private:
        float speed = 5.f;

        public:
        SpaceShip(std::shared_ptr<KapEngine::GameObject> go);
        ~SpaceShip() = default;

        void onStart() override;
        void onUpdate() override;

        private:
        void getUserInput();
    };
}
}
