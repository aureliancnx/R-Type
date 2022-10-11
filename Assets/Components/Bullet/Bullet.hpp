#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

namespace RType {
    class Bullet : public KapEngine::Component {
        public:
        Bullet(std::shared_ptr<KapEngine::GameObject> gameObject);
        ~Bullet() = default;

        void onFixedUpdate() override;
    };
}
