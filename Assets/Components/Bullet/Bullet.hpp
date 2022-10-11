#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

namespace RType {
    class Bullet : public KapEngine::Component {
        private:
        float speed = 10.f;
        float initialX;

        public:
        Bullet(std::shared_ptr<KapEngine::GameObject> gameObject);
        ~Bullet() = default;

        void onStart() override;

        void onUpdate() override;
    };
}
