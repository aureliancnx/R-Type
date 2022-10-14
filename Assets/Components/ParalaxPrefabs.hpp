/*
** EPITECH PROJECT, 2022
** RType
** File description:
** ParalaxPrefabs.hpp
*/

#ifndef RTYPE_PARALAXPREFABS_HPP
#define RTYPE_PARALAXPREFABS_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

#include "Animations/ParalaxAnimation.hpp"

namespace RType {

    class ParalaxPrefabs {
        public:
            static void registerGalaxyParalaxPrefab(KapEngine::KEngine& engine);
            static void registerStarsParalaxPrefab(KapEngine::KEngine& engine);
    };

} // RType

#endif //RTYPE_PARALAXPREFABS_HPP
