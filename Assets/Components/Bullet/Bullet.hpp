#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
    class Bullet : public KapMirror::NetworkComponent {
      public:
        enum Direction { LEFT = 0, RIGHT };

      private:
        Direction direction;
        float speed = 2.f;
        float initialX;
        KapEngine::KEngine &engine;

      public:
        explicit Bullet(std::shared_ptr<KapEngine::GameObject> gameObject);
        ~Bullet() = default;

        void setDirection(Direction _direction);

        Direction getDirection() const;

        void onStart() override;

        void onUpdate() override;

        void serialize(KapMirror::NetworkWriter& writer) override;

        void deserialize(KapMirror::NetworkReader& reader) override;
    };
} // namespace RType
