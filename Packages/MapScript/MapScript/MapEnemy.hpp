#pragma once

#include "Debug.hpp"
#include <string>
#include <iostream>

namespace RType {
    class MapEnemy {
      public:
        std::string name = "";
        std::string sprite = "";
        int spawnTime = 0;
        int startPositionY = 0;

        MapEnemy() = default;
        MapEnemy(std::string _name, std::string _sprite) : name(_name), sprite(_sprite) {}
        ~MapEnemy() = default;

        void Dump() {
            KapEngine::Debug::log("Enemy: name = '" + name + "', sprite = '" + sprite + "', spawnTime = " + std::to_string(spawnTime) +
                                  ", startPositionY = " + std::to_string(startPositionY));
        }
    };
} // namespace RType
