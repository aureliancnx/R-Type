#include "MapScript.hpp"
#include "Script/DebugScript.hpp"
#include "Script/Vector2Script.hpp"
#include "Script/RectangleScript.hpp"
#include "Script/MathScript.hpp"
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
    Script::Math::initScript(L);
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
        auto* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        std::string mapName = lua_tostring(L, 1);
        manager->_setMapName(mapName);
        return 0;
    };

    auto setMapAuthor = [](lua_State* L) -> int {
        auto* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        std::string mapAuthor = lua_tostring(L, 1);
        manager->_setMapAuthor(mapAuthor);
        return 0;
    };

    auto setMapDescription = [](lua_State* L) -> int {
        auto* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        std::string mapDescription = lua_tostring(L, 1);
        manager->_setMapDescription(mapDescription);
        return 0;
    };

    auto spawnMapEnemy = [](lua_State* L) -> int {
        auto* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        std::string enemyName = lua_tostring(L, 1);
        int spawnTime = (int)lua_tonumber(L, 2);
        int startPositionY = (int)lua_tonumber(L, 3);
        int startPositionX = (int)lua_tonumber(L, 4);
        int enemyHp = (int)lua_tonumber(L, 5);

        manager->_registerSpawnEnemy(enemyName, spawnTime, startPositionY, startPositionX, enemyHp);
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

    verifScript();
}

void MapScript::verifScript() {
    if (name.empty()) {
        throw LuaException("Map name is not set or empty");
    }
    if (author.empty()) {
        throw LuaException("Map author is not set or empty");
    }
    if (description.empty()) {
        throw LuaException("Map description is not set or empty");
    }

    for (auto& enemy : newEnemies) {
        checkNewEnemy(enemy);
    }
}

void MapScript::checkNewEnemy(Script::Enemy* enemy) {
    if (enemy->name.empty()) {
        throw LuaException("Enemy name is not set or empty");
    }
    if (enemy->pathSprite.empty()) {
        throw LuaException("Enemy sprite path is not set or empty");
    }
    if (enemy->rectangle->w <= 0) {
        throw LuaException("Enemy width is not set or empty");
    }
    if (enemy->rectangle->h <= 0) {
        throw LuaException("Enemy height is not set or empty");
    }
}

void MapScript::_setMapName(const std::string& _name) {
    KapEngine::Debug::log("Map name: " + _name);
    name = _name;
}

void MapScript::_setMapAuthor(const std::string& _author) {
    KapEngine::Debug::log("Map author: " + _author);
    author = _author;
}

void MapScript::_setMapDescription(const std::string& _description) {
    KapEngine::Debug::log("Map description: " + _description);
    description = _description;
}

void MapScript::_registerNewEnemy(Script::Enemy* enemy) {
    newEnemies.push_back(enemy);
}

void MapScript::_registerSpawnEnemy(const std::string& _name, int spawnTime, int startPositionY, int startPositionX, int enemyHp) {
    // Check values
    if (_name.empty()) {
        throw LuaException("Enemy name is empty");
    }
    if (spawnTime < 0) {
        throw LuaException("Spawn time can't be negative");
    }
    if (startPositionY < 0) {
        throw LuaException("Start position Y can't be negative");
    }
    if (startPositionX < 0) {
        throw LuaException("Start position X can't be negative");
    }
    if (enemyHp < 0) {
        throw LuaException("Enemy HP can't be negative");
    }
    if (enemyHp == 0) {
        throw LuaException("Enemy HP can't be 0");
    }
    if (startPositionX == 0) {
        startPositionX = 1280 + 100; // Constant
    }
    spawnEnemies.push_back({_name, spawnTime, startPositionY, startPositionX, enemyHp});
}

void MapScript::destroyEnemies() {
    for (auto enemy : newEnemies) {
        enemy->~Enemy();
    }
}
