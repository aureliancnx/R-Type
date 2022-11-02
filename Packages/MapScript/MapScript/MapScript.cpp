#include "MapScript.hpp"
#include "Script/DebugScript.hpp"
#include "Script/Vector2Script.hpp"
#include "Script/RectangleScript.hpp"
#include <fstream>

using namespace RType;

void MapScript::loadScript(const std::string& scriptPath) {
    std::ifstream ifs(scriptPath);
    if (!ifs.is_open()) {
        throw LuaException("Can't open file '" + scriptPath + "'");
    }

    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    executeScript(content);
}

void MapScript::executeScript(const std::string& script) {
    lua_State* L = luaL_newstate();

    // Load Lua scripts
    Script::Debug::initScript(L);
    Script::Vector2::initScript(L);
    Script::Rectangle::initScript(L);
    Script::Enemy::initScript(L, this);
    initScript(L);

    int doResult = luaL_dostring(L, script.c_str());
    if (doResult != LUA_OK) {
        std::string error = lua_tostring(L, -1);
        lua_pop(L, 1);
        lua_close(L);
        throw LuaException("Something went wrong during execution: " + error);
    }

    lua_close(L);

    if (name.empty()) {
        throw LuaException("Map name is empty");
    }

    destroyEnemies();
}

void MapScript::initScript(lua_State* L) {
    auto setMapName = [](lua_State* L) -> int {
        MapScript* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        std::string mapName = lua_tostring(L, 1);
        manager->__setMapName(mapName);
        return 0;
    };

    auto setMapAuthor = [](lua_State* L) -> int {
        MapScript* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        std::string mapAuthor = lua_tostring(L, 1);
        manager->__setMapAuthor(mapAuthor);
        return 0;
    };

    auto setMapDescription = [](lua_State* L) -> int {
        MapScript* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        std::string mapDescription = lua_tostring(L, 1);
        manager->__setMapDescription(mapDescription);
        return 0;
    };

    auto spawnMapEnemy = [](lua_State* L) -> int {
        MapScript* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        std::string enemyName = lua_tostring(L, 1);
        int spawnTime = (int)lua_tonumber(L, 2);
        int startPositionY = (int)lua_tonumber(L, 3);
        int enemyHp = (int)lua_tonumber(L, 4);
        return 0;
    };

    lua_newtable(L);
    int mapTableIdx = lua_gettop(L);
    lua_pushvalue(L, mapTableIdx);
    lua_setglobal(L, "Map");

    lua_pushlightuserdata(L, this);
    lua_pushcclosure(L, setMapName, 1);
    lua_setfield(L, -2, "SetName");

    lua_pushlightuserdata(L, this);
    lua_pushcclosure(L, setMapAuthor, 1);
    lua_setfield(L, -2, "SetAuthor");

    lua_pushlightuserdata(L, this);
    lua_pushcclosure(L, setMapDescription, 1);
    lua_setfield(L, -2, "SetDescription");

    lua_pushlightuserdata(L, this);
    lua_pushcclosure(L, spawnMapEnemy, 1);
    lua_setfield(L, -2, "SpawnEnemy");

    lua_pushstring(L, "__index");
    lua_pushvalue(L, mapTableIdx);
    lua_settable(L, -3);
}

void MapScript::__setMapName(const std::string& name) {
    KapEngine::Debug::log("Map name: " + name);
    this->name = name;
}

void MapScript::__setMapAuthor(const std::string& author) {
    KapEngine::Debug::log("Map author: " + author);
    this->author = author;
}

void MapScript::__setMapDescription(const std::string& description) {
    KapEngine::Debug::log("Map description: " + description);
    this->description = description;
}

void MapScript::__registerNewEnemy(Script::Enemy* enemy) {
    newEnemies.push_back(enemy);
}

void MapScript::destroyEnemies() {
    for (auto enemy : newEnemies) {
        enemy->~Enemy();
    }
}
