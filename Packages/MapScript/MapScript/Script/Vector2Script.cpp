#include "Vector2Script.hpp"
#include "Debug.hpp"

using namespace RType::Script;

void Vector2::dump() const { KapEngine::Debug::log("Vector2: x = " + std::to_string(x) + ", y = " + std::to_string(y)); }

void Vector2::initScript(lua_State* L) {
    lua_newtable(L);
    int vector2TableIdx = lua_gettop(L);
    lua_pushvalue(L, vector2TableIdx);
    lua_setglobal(L, "Vector2");

    lua_pushcfunction(L, __create);
    lua_setfield(L, -2, "new");

    lua_pushcfunction(L, __dump);
    lua_setfield(L, -2, "Dump");

    luaL_newmetatable(L, "Vector2MetaTable");
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

int Vector2::__create(lua_State* L) {
    auto x = (float) lua_tonumber(L, 1);
    auto y = (float) lua_tonumber(L, 2);
    lua_pop(L, 2);

    void* ptr = lua_newuserdata(L, sizeof(Vector2));
    new (ptr) Vector2();
    luaL_getmetatable(L, "Vector2MetaTable");
    lua_setmetatable(L, -2);

    lua_newtable(L);
    lua_setuservalue(L, 1);

    auto* vector2 = (Vector2*) ptr;
    vector2->x = x;
    vector2->y = y;
    return 1;
}

int Vector2::__destroy(lua_State* L) {
    auto* vector2 = (Vector2*) lua_touserdata(L, -1);
    vector2->~Vector2();
    return 0;
}

int Vector2::__index(lua_State* L) {
    auto* vector2 = (Vector2*) lua_touserdata(L, -2);
    std::string index(lua_tostring(L, -1));
    if (index == "x") {
        lua_pushnumber(L, vector2->x);
        return 1;
    }
    if (index == "y") {
        lua_pushnumber(L, vector2->y);
        return 1;
    }

    lua_getuservalue(L, 1);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1)) {
        lua_getglobal(L, "Vector2");
        lua_pushstring(L, index.c_str());
        lua_rawget(L, -2);
    }
    return 1;
}

int Vector2::__newIndex(lua_State* L) {
    auto* vector2 = (Vector2*) lua_touserdata(L, -3);
    std::string index(lua_tostring(L, -2));
    if (index == "x") {
        vector2->x = (float) lua_tonumber(L, -1);
        return 0;
    }
    if (index == "y") {
        vector2->y = (float) lua_tonumber(L, -1);
        return 0;
    }

    lua_getuservalue(L, 1); // 1
    lua_pushvalue(L, 2);    // 2
    lua_pushvalue(L, 3);    // 3
    lua_settable(L, -3);    // 1[2] = 3
    return 0;
}

int Vector2::__dump(lua_State* L) {
    auto* vector2 = (Vector2*) lua_touserdata(L, -1);
    vector2->dump();
    return 0;
}
