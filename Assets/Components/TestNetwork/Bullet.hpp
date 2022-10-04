#pragma once

#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
    class Bullet : public KapMirror::Experimental::NetworkComponent {
        private:
        float speed = 2.f;

        public:
        Bullet(std::shared_ptr<KapEngine::GameObject> go);
        ~Bullet() = default;

        void onStart() override;
        void onUpdate() override;
    };
}
