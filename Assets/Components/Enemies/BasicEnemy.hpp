#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
    class BasicEnemy : public KapMirror::NetworkComponent {
        public:
        enum Type {
            BOUBOULE = 1,
            SHIP = 2,
            TENTACULE = 3,
            TEST = 4
        };

        private:
        Type type = BOUBOULE;
        int life = 20;

        long long lastShootTime = 0;

        public:
        BasicEnemy(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~BasicEnemy() = default;

        void setType(Type _type);

        void setLife(int _life);

        void onFixedUpdate() override;

        void onStartClient() override;

        void onTriggerEnter(std::shared_ptr<KapEngine::GameObject> other) override;

        void customPayloadSerialize(KapMirror::NetworkWriter& writer) override;

        void customPayloadDeserialize(KapMirror::NetworkReader& reader) override;

        private:
        void shoot();

        void setSkinId(Type type);
    };
}
