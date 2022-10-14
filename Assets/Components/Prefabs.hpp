#pragma once

#include "KapEngine.hpp"

#include "Animations/ParalaxAnimation.hpp"

namespace RType {
    class Prefabs {
        public:
        static void registerPlayerPrefab(KapEngine::KEngine& engine);

        static void registerBulletPrefab(KapEngine::KEngine& engine);

        static void registerShipEnemyPrefab(KapEngine::KEngine& engine);

        static void registerGalaxyParalaxPrefab(KapEngine::KEngine& engine);

        static void registerStarsParalaxPrefab(KapEngine::KEngine& engine);
    };
}
