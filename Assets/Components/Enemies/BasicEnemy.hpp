#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
    class BasicEnemy : public KapMirror::NetworkComponent {
        public:
        enum Type {
            SHIP = 1,
            SHIP_2 = 2,
            SHIP_3 = 3,
            SHIP_4 = 4,
            SHIP_5 = 5
        };

        private:
        Type type = SHIP;
        int life = 20;

        long long lastShootTime = 0;

        public:
        BasicEnemy(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~BasicEnemy() = default;

        void setType(Type _type);

        void setLife(int _life);

        void onFixedUpdate() override;

        void onStartClient() override;

        void customPayloadSerialize(KapMirror::NetworkWriter& writer) override;

        void customPayloadDeserialize(KapMirror::NetworkReader& reader) override;

        private:
        void shoot();

        void initSkin();
    };
}
