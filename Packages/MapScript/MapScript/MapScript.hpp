#pragma once

#include "Debug.hpp"
#include "Lua.hpp"
#include "Script/EnemyScript.hpp"
#include "LuaException.hpp"
#include <vector>
#include <iostream>
#include <cstring>
#include <assert.h>

namespace RType::Script {
    class Enemy;
}

namespace RType {
    struct SpawnEnemy {
        std::string name;
        int spawnTime;
        int startPositionY;
        int startPositionX;
        int enemyHp;
    };

    class MapScript {
      private:
        std::string name;
        std::string author;
        std::string description;
        std::vector<Script::Enemy*> newEnemies;
        std::vector<SpawnEnemy> spawnEnemies;

      public:
        MapScript() = default;
        ~MapScript() = default;

        void loadScript(const std::string& scriptPath);

        std::string getName() const { return name; }

        std::string getAuthor() const { return author; }

        std::string getDescription() const { return description; }

        std::vector<SpawnEnemy> getSpawnedEnemies() const { return spawnEnemies; }

        void _setMapName(const std::string& name);
        void _setMapAuthor(const std::string& author);
        void _setMapDescription(const std::string& description);
        void _registerNewEnemy(Script::Enemy* enemy);
        void _registerSpawnEnemy(const std::string& name, int spawnTime, int startPositionY, int startPositionX, int enemyHp);

      private:
        void executeScript(const std::string& script);

        void verifScript();

        void checkNewEnemy(Script::Enemy* enemy);

        void initScript(lua_State* L);

        void destroyEnemies();
    };
} // namespace RType
