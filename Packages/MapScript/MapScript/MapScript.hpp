#pragma once

#include "Debug.hpp"
#include "Lua.hpp"
#include "MapEnemy.hpp"
#include "LuaException.hpp"
#include <vector>
#include <iostream>
#include <cstring>
#include <assert.h>

namespace RType
{
    class MapScript
    {
      private:
        std::vector<MapEnemy *> enemies;

      public:
        MapScript() = default;
        ~MapScript() = default;

        void loadScript(const std::string &scriptPath);

        void __registerEnemy(MapEnemy *enemy);

      private:
        void executeScript(const std::string &script);

        void destroyEnemies();

        void showEnemies();
    };
} // namespace RType
