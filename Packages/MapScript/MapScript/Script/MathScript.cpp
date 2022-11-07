#include "MathScript.hpp"
#include <cstdlib>
#include <ctime>

using namespace RType::Script;

void Math::initScript(lua_State* L) {
    std::srand(std::time(nullptr));

    lua_newtable(L);
    int debugTableIdx = lua_gettop(L);
    lua_pushvalue(L, debugTableIdx);
    lua_setglobal(L, "Math");

    lua_pushcfunction(L, __random);
    lua_setfield(L, -2, "Random");

    lua_pushstring(L, "__index");
    lua_pushvalue(L, debugTableIdx);
    lua_settable(L, -3);
}

int Math::__random(lua_State* L) {
    int min = (int)lua_tonumber(L, 1);
    int max = (int)lua_tonumber(L, 2);
    lua_pushnumber(L, std::rand() % (max - min) + min);
    return 1;
}
