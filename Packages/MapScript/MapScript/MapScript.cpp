#include "MapScript.hpp"
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

    auto CreateEnemy = [](lua_State* L) -> int {
        MapScript* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        void* ptr = lua_newuserdata(L, sizeof(MapEnemy));
        new (ptr) MapEnemy();
        luaL_getmetatable(L, "EnemyMetaTable");
        lua_setmetatable(L, -2);

        lua_newtable(L);
        lua_setuservalue(L, 1);

        manager->__registerEnemy((MapEnemy*)ptr);
        return 1;
    };

    auto DestroyEnemy = [](lua_State* L) -> int {
        MapScript* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        MapEnemy* enemy = (MapEnemy*)lua_touserdata(L, -1);
        //enemy->~MapEnemy();
        return 0;
    };

    auto DumpEnemy = [](lua_State* L) -> int {
        MapEnemy* enemy = (MapEnemy*)lua_touserdata(L, -1);
        enemy->Dump();
        return 0;
    };

    auto EnemyIndex = [](lua_State* L) -> int {
        assert(lua_isuserdata(L, -2));  //1
        assert(lua_isstring(L, -1));    //2

        MapEnemy* enemy = (MapEnemy*)lua_touserdata(L, -2);
        std::string index = lua_tostring(L, -1);
        if (index == "name") {
            lua_pushstring(L, enemy->name.c_str());
            return 1;
        }
        if (index == "sprite") {
            lua_pushstring(L, enemy->sprite.c_str());
            return 1;
        }
        if (index == "spawnTime") {
            lua_pushnumber(L, enemy->spawnTime);
            return 1;
        }
        if (index == "startPositionY") {
            lua_pushnumber(L, enemy->startPositionY);
            return 1;
        }

        lua_getuservalue(L, 1);
        lua_pushvalue(L, 2);
        lua_gettable(L, -2);
        if (lua_isnil(L, -1)) {
            lua_getglobal(L, "Enemy");
            lua_pushstring(L, index.c_str());
            lua_rawget(L, -2);
        }
        return 1;
    };

    auto EnemyNewIndex = [](lua_State* L) -> int {
        assert(lua_isuserdata(L, -3));  //1
        assert(lua_isstring(L, -2));    //2
                                        // -1 - value we want to set    //3

        MapEnemy* enemy = (MapEnemy*)lua_touserdata(L, -3);
        std::string index = lua_tostring(L, -2);
        if (index == "name") {
            std::string name = lua_tostring(L, -1);
            enemy->name = name;
            return 0;
        }
        if (index == "sprite") {
            std::string sprite = lua_tostring(L, -1);
            enemy->sprite = sprite;
            return 0;
        }
        if (index == "spawnTime") {
            enemy->spawnTime = (int)lua_tonumber(L, -1);
            return 0;
        }
        if (index == "startPositionY") {
            enemy->startPositionY = (int)lua_tonumber(L, -1);
            return 0;
        }

        lua_getuservalue(L, 1); //1
        lua_pushvalue(L, 2);    //2
        lua_pushvalue(L, 3);    //3
        lua_settable(L, -3);    //1[2] = 3
        return 0;
    };

    auto DebugLog = [](lua_State* L) -> int {
        std::string message = lua_tostring(L, 1);
        KapEngine::Debug::log(message);
        return 0;
    };

    auto DebugWarning = [](lua_State* L) -> int {
        std::string message = lua_tostring(L, 1);
        KapEngine::Debug::warning(message);
        return 0;
    };

    auto DebugError = [](lua_State* L) -> int {
        std::string message = lua_tostring(L, 1);
        KapEngine::Debug::error(message);
        return 0;
    };

    lua_newtable(L);
    int debugTableIdx = lua_gettop(L);
    lua_pushvalue(L, debugTableIdx);
    lua_setglobal(L, "Debug");

    lua_pushcfunction(L, DebugLog);
    lua_setfield(L, -2, "Log");

    lua_pushcfunction(L, DebugWarning);
    lua_setfield(L, -2, "LogWarning");

    lua_pushcfunction(L, DebugError);
    lua_setfield(L, -2, "LogError");

    lua_pushstring(L, "__index");
    lua_pushvalue(L, debugTableIdx);
    lua_settable(L, -3);

    lua_newtable(L);
    int enemyTableIdx = lua_gettop(L);
    lua_pushvalue(L, enemyTableIdx);
    lua_setglobal(L, "Enemy");

    lua_pushlightuserdata(L, this);
    lua_pushcclosure(L, CreateEnemy, 1);
    lua_setfield(L, -2, "new");
    lua_pushcfunction(L, DumpEnemy);
    lua_setfield(L, -2, "Dump");

    luaL_newmetatable(L, "EnemyMetaTable");
    lua_pushstring(L, "__gc");
    lua_pushlightuserdata(L, this);
    lua_pushcclosure(L, DestroyEnemy, 1);
    lua_settable(L, -3);

    lua_pushstring(L, "__index");
    lua_pushcfunction(L, EnemyIndex);
    lua_settable(L, -3);

    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, EnemyNewIndex);
    lua_settable(L, -3);

    int doResult = luaL_dostring(L, script.c_str());
    if (doResult != LUA_OK) {
        std::string error = lua_tostring(L, -1);
        throw LuaException("Something went wrong during execution: " + error);
    }

    lua_close(L);
    showEnemies();
    destroyEnemies();
}

void MapScript::__registerEnemy(MapEnemy* enemy) {
    KapEngine::Debug::log("Register enemy");
    enemies.push_back(enemy);
}

void MapScript::showEnemies() {
    KapEngine::Debug::log("Enemies:");
    for (auto enemy : enemies) {
        enemy->Dump();
    }
}

void MapScript::destroyEnemies() {
    for (auto enemy : enemies) {
        enemy->~MapEnemy();
    }
}
