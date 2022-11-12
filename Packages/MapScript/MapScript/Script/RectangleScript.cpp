#include "RectangleScript.hpp"
#include "Debug.hpp"

using namespace RType::Script;

void Rectangle::dump() const {
    KapEngine::Debug::log("Rectangle: x = " + std::to_string(x) + ", y = " + std::to_string(y) + ", w = " + std::to_string(w) +
                          ", h = " + std::to_string(h));
}

void Rectangle::initScript(lua_State* L) {
    lua_newtable(L);
    int tableIdx = lua_gettop(L);
    lua_pushvalue(L, tableIdx);
    lua_setglobal(L, "Rectangle");

    lua_pushcfunction(L, __create);
    lua_setfield(L, -2, "new");

    lua_pushcfunction(L, __dump);
    lua_setfield(L, -2, "Dump");

    luaL_newmetatable(L, "RectangleMetaTable");
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

int Rectangle::__create(lua_State* L) {
    auto x = (float) lua_tonumber(L, 1);
    auto y = (float) lua_tonumber(L, 2);
    auto w = (float) lua_tonumber(L, 3);
    auto h = (float) lua_tonumber(L, 4);
    lua_pop(L, 4);

    void* ptr = lua_newuserdata(L, sizeof(Rectangle));
    new (ptr) Rectangle();
    luaL_getmetatable(L, "RectangleMetaTable");
    lua_setmetatable(L, -2);

    lua_newtable(L);
    lua_setuservalue(L, 1);

    auto* rect = (Rectangle*) ptr;
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    return 1;
}

int Rectangle::__destroy(lua_State* L) {
    auto* rect = (Rectangle*) lua_touserdata(L, -1);
    rect->~Rectangle();
    return 0;
}

int Rectangle::__index(lua_State* L) {
    auto* rect = (Rectangle*) lua_touserdata(L, -2);
    std::string index(lua_tostring(L, -1));
    if (index == "x") {
        lua_pushnumber(L, rect->x);
        return 1;
    }
    if (index == "y") {
        lua_pushnumber(L, rect->y);
        return 1;
    }
    if (index == "w") {
        lua_pushnumber(L, rect->w);
        return 1;
    }
    if (index == "h") {
        lua_pushnumber(L, rect->h);
        return 1;
    }

    lua_getuservalue(L, 1);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1)) {
        lua_getglobal(L, "Rectangle");
        lua_pushstring(L, index.c_str());
        lua_rawget(L, -2);
    }
    return 1;
}

int Rectangle::__newIndex(lua_State* L) {
    auto* rect = (Rectangle*) lua_touserdata(L, -3);
    std::string index(lua_tostring(L, -2));
    if (index == "x") {
        rect->x = (float) lua_tonumber(L, -1);
        return 0;
    }
    if (index == "y") {
        rect->y = (float) lua_tonumber(L, -1);
        return 0;
    }
    if (index == "w") {
        rect->w = (float) lua_tonumber(L, -1);
        return 0;
    }
    if (index == "h") {
        rect->h = (float) lua_tonumber(L, -1);
        return 0;
    }

    lua_getuservalue(L, 1); // 1
    lua_pushvalue(L, 2);    // 2
    lua_pushvalue(L, 3);    // 3
    lua_settable(L, -3);    // 1[2] = 3
    return 0;
}

int Rectangle::__dump(lua_State* L) {
    auto* rect = (Rectangle*) lua_touserdata(L, -1);
    rect->dump();
    return 0;
}
