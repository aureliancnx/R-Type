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
    class MapScript {
        private:
        std::string name = "";
        std::string author = "";
        std::string description = "";
        std::vector<Script::Enemy*> newEnemies;

        public:
        MapScript() = default;
        ~MapScript() = default;

        void loadScript(const std::string &scriptPath);

        std::string getName() const { return name; }

        std::string getAuthor() const { return author; }

        std::string getDescription() const { return description; }

        void __setMapName(const std::string& name);
        void __setMapAuthor(const std::string& author);
        void __setMapDescription(const std::string& description);
        void __registerNewEnemy(Script::Enemy* enemy);

      private:
        void executeScript(const std::string &script);

        void initScript(lua_State* L);

        void destroyEnemies();
    };
} // namespace RType
