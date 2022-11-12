#include "EnemyScript.hpp"

using namespace RType::Script;

void Enemy::dump() const { KapEngine::Debug::log("Enemy: name = '" + name + "', pathSprite = '" + pathSprite + "'"); }

void Enemy::initScript(lua_State* L, MapScript* mapScript) {
    lua_newtable(L);
    int enemyTableIdx = lua_gettop(L);
    lua_pushvalue(L, enemyTableIdx);
    lua_setglobal(L, "Enemy");

    lua_pushlightuserdata(L, mapScript);
    lua_pushcclosure(L, __create, 1);
    lua_setfield(L, -2, "new");

    lua_pushcfunction(L, __dump);
    lua_setfield(L, -2, "Dump");

    luaL_newmetatable(L, "EnemyMetaTable");
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, __destroy);
    lua_settable(L, -3);

    lua_pushstring(L, "__index");
    lua_pushcfunction(L, __index);
    lua_settable(L, -3);

    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, __newIndex);
    lua_settable(L, -3);
}

int Enemy::__create(lua_State* L) {
    auto* manager = (MapScript*) lua_touserdata(L, lua_upvalueindex(1));

    void* ptr = lua_newuserdata(L, sizeof(Script::Enemy));
    new (ptr) Script::Enemy();
    luaL_getmetatable(L, "EnemyMetaTable");
    lua_setmetatable(L, -2);

    lua_newtable(L);
    lua_setuservalue(L, 1);

    manager->_registerNewEnemy((Enemy*) ptr);
    return 1;
}

int Enemy::__destroy(lua_State* L) {
    auto* enemy = (Enemy*) lua_touserdata(L, -1);
    enemy->~Enemy();
    return 0;
}

int Enemy::__index(lua_State* L) {
    auto* enemy = (Enemy*) lua_touserdata(L, -2);
    std::string index(lua_tostring(L, -1));
    if (index == "name") {
        lua_pushstring(L, enemy->name.c_str());
        return 1;
    }
    if (index == "pathSprite") {
        lua_pushstring(L, enemy->pathSprite.c_str());
        return 1;
    }
    if (index == "rectangle") {
        lua_pushlightuserdata(L, enemy->rectangle);
        return 1;
    }
    if (index == "scale") {
        lua_pushlightuserdata(L, enemy->scale);
        return 1;
    }
    if (index == "animation") {
        lua_pushlightuserdata(L, enemy->animation);
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
}

int Enemy::__newIndex(lua_State* L) {
    auto* enemy = (Enemy*) lua_touserdata(L, -3);
    std::string index(lua_tostring(L, -2));
    if (index == "name") {
        std::string name(lua_tostring(L, -1));
        enemy->name = name;
        return 0;
    }
    if (index == "pathSprite") {
        std::string pathSprite(lua_tostring(L, -1));
        enemy->pathSprite = pathSprite;
        return 0;
    }
    if (index == "rectangle") {
        void* ptr = lua_touserdata(L, -1);
        enemy->rectangle = (Rectangle*) ptr;
        return 0;
    }
    if (index == "scale") {
        void* ptr = lua_touserdata(L, -1);
        enemy->scale = (Vector2*) ptr;
        return 0;
    }
    if (index == "animation") {
        void* ptr = lua_touserdata(L, -1);
        enemy->animation = (SpriteAnimation*) ptr;
        return 0;
    }

    lua_getuservalue(L, 1); // 1
    lua_pushvalue(L, 2);    // 2
    lua_pushvalue(L, 3);    // 3
    lua_settable(L, -3);    // 1[2] = 3
    return 0;
}

int Enemy::__dump(lua_State* L) {
    auto* enemy = (Enemy*) lua_touserdata(L, -1);
    enemy->dump();
    return 0;
}
