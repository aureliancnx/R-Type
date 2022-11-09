#include "MathScript.hpp"
#include <cstdlib>
#include <ctime>
#include <valarray>

using namespace RType::Script;

void Math::initScript(lua_State* L) {
    std::srand(std::time(nullptr));

    lua_newtable(L);
    int debugTableIdx = lua_gettop(L);
    lua_pushvalue(L, debugTableIdx);
    lua_setglobal(L, "Math");

    lua_pushcfunction(L, __abs);
    lua_setfield(L, debugTableIdx, "Abs");

    lua_pushcfunction(L, __random);
    lua_setfield(L, -2, "Random");

    lua_pushcfunction(L, __sin);
    lua_setfield(L, -2, "Sin");

    lua_pushcfunction(L, __cos);
    lua_setfield(L, -2, "Cos");

    lua_pushcfunction(L, __tan);
    lua_setfield(L, -2, "Tan");

    lua_pushstring(L, "__index");
    lua_pushvalue(L, debugTableIdx);
    lua_settable(L, -3);
}

int Math::__abs(lua_State* L) {
    auto value = (float)lua_tonumber(L, 1);
    lua_pushnumber(L, std::abs(value));
    return 1;
}

int Math::__random(lua_State* L) {
    auto min = (int)lua_tonumber(L, 1);
    auto max = (int)lua_tonumber(L, 2);
    lua_pushnumber(L, std::rand() % (max - min) + min);
    return 1;
}

int Math::__sin(lua_State* L) {
    auto angle = (float)lua_tonumber(L, 1);
    lua_pushnumber(L, std::sin(angle));
    return 1;
}

int Math::__cos(lua_State* L) {
    auto angle = (float)lua_tonumber(L, 1);
    lua_pushnumber(L, std::cos(angle));
    return 1;
}

int Math::__tan(lua_State* L) {
    auto angle = (float)lua_tonumber(L, 1);
    lua_pushnumber(L, std::tan(angle));
    return 1;
}
