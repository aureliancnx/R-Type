#pragma once

#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
namespace Component {
    class SpaceShip : public KapMirror::Experimental::NetworkComponent {
        private:
        float speed = 5.f;

        public:
        SpaceShip(std::shared_ptr<KapEngine::GameObject> go);
        ~SpaceShip() = default;

        void onStart() override;
        void onUpdate() override;

        protected:
        void onStartServer() override;

        void onStartClient() override;

        private:
        void getUserInput();
    };
}
}
