#include "SpriteAnimationScript.hpp"
#include "Debug.hpp"

using namespace RType::Script;

void SpriteAnimation::initScript(lua_State* L) {
    lua_newtable(L);
    int spriteAnimationTableIdx = lua_gettop(L);
    lua_pushvalue(L, spriteAnimationTableIdx);
    lua_setglobal(L, "SpriteAnimation");

    lua_pushcfunction(L, __create);
    lua_setfield(L, -2, "new");

    luaL_newmetatable(L, "SpriteAnimationMetaTable");
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

int SpriteAnimation::__create(lua_State* L) {
    void* ptr = lua_newuserdata(L, sizeof(Script::SpriteAnimation));
    new (ptr) Script::SpriteAnimation();
    luaL_getmetatable(L, "SpriteAnimationMetaTable");
    lua_setmetatable(L, -2);

    lua_newtable(L);
    lua_setuservalue(L, 1);
    return 1;
}

int SpriteAnimation::__destroy(lua_State* L) {
    auto* spriteAnimation = (SpriteAnimation*) lua_touserdata(L, -1);
    spriteAnimation->~SpriteAnimation();
    return 0;
}

int SpriteAnimation::__index(lua_State* L) {
    auto* spriteAnimation = (SpriteAnimation*) lua_touserdata(L, -2);
    std::string index(lua_tostring(L, -1));
    if (index == "duration") {
        lua_pushnumber(L, spriteAnimation->duration);
        return 1;
    } else if (index == "loop") {
        lua_pushboolean(L, spriteAnimation->loop);
        return 1;
    } else if (index == "rectangle") {
        lua_pushlightuserdata(L, spriteAnimation->rectangle);
        return 1;
    } else if (index == "nbFrames") {
        lua_pushnumber(L, spriteAnimation->nbFrames);
        return 1;
    }

    lua_getuservalue(L, 1);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1)) {
        lua_getglobal(L, "SpriteAnimation");
        lua_pushstring(L, index.c_str());
        lua_rawget(L, -2);
    }
    return 1;
}

int SpriteAnimation::__newIndex(lua_State* L) {
    auto* spriteAnimation = (SpriteAnimation*) lua_touserdata(L, -3);
    std::string index(lua_tostring(L, -2));
    if (index == "duration") {
        spriteAnimation->duration = lua_tonumber(L, -1);
    } else if (index == "loop") {
        spriteAnimation->loop = lua_toboolean(L, -1);
    } else if (index == "rectangle") {
        spriteAnimation->rectangle = (Rectangle*) lua_touserdata(L, -1);
    } else if (index == "nbFrames") {
        spriteAnimation->nbFrames = lua_tonumber(L, -1);
    } else {
        lua_getuservalue(L, 1);
        lua_pushvalue(L, 2);
        lua_pushvalue(L, 3);
        lua_settable(L, -3);
    }

    lua_getuservalue(L, 1); // 1
    lua_pushvalue(L, 2);    // 2
    lua_pushvalue(L, 3);    // 3
    lua_settable(L, -3);    // 1[2] = 3
    return 0;
}
