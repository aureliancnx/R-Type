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

    lua_pushcfunction(L, __rand);
    lua_setfield(L, -2, "Rand");

    lua_pushstring(L, "__index");
    lua_pushvalue(L, debugTableIdx);
    lua_settable(L, -3);
}

int Math::__rand(lua_State* L) {
    int min = lua_tointeger(L, 1);
    int max = lua_tointeger(L, 2);
    lua_pushinteger(L, std::rand() % (max - min) + min);
    return 1;
}
