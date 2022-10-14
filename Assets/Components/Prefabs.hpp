#pragma once

#include "KapEngine.hpp"

namespace RType {
    class Prefabs {
        public:
        static void registerPlayerPrefab(KapEngine::KEngine& engine);

        static void registerBulletPrefab(KapEngine::KEngine& engine);

        static void registerShipEnemyPrefab(KapEngine::KEngine& engine);

        static void registerBoubouleEnemyPrefab(KapEngine::KEngine& engine);

        static void registerTentaclesBossEnemyPrefab(KapEngine::KEngine& engine);
    };
}
