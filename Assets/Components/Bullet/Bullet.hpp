#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
    class Bullet : public KapMirror::NetworkComponent {
        public:
        enum Direction {
            LEFT,
            RIGHT
        };

        private:
        Direction direction;
        float speed = 10.f;
        float initialX;

        public:
        Bullet(std::shared_ptr<KapEngine::GameObject> gameObject);
        ~Bullet() = default;

        void setDirection(Direction _direction);

        Direction getDirection() const;

        void onStart() override;

        void onUpdate() override;

        void customPayloadSerialize(KapMirror::NetworkWriter& writer) override;

        void customPayloadDeserialize(KapMirror::NetworkReader& reader) override;
    };
}
