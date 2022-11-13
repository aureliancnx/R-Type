#pragma once

#include "KapEngine.hpp"

#include "Animations/ParalaxAnimation.hpp"
#include "Animations/SpriteAnimation.hpp"

namespace RType {
    class Prefabs {
      public:
        static void registerPlayerPrefab(KapEngine::KEngine &engine);

        static void registerBulletPrefab(KapEngine::KEngine &engine);

        static void registerMissilePrefab(KapEngine::KEngine &engine);

        static void registerShipEnemyPrefab(KapEngine::KEngine &engine);

        static void registerGalaxyParalaxPrefab(KapEngine::KEngine &engine);

        static void registerStarsParalaxPrefab(KapEngine::KEngine &engine);

        static void registerBoubouleEnemyPrefab(KapEngine::KEngine &engine);

        static void registerTentaclesBossEnemyPrefab(KapEngine::KEngine &engine);

        static void registerInGameMenuPrefab(KapEngine::KEngine &engine);

        static void registerMissileExplodePrefab(KapEngine::KEngine &engine);

        static void registerBulletExplodePrefab(KapEngine::KEngine &engine);
    };
} // namespace RType
