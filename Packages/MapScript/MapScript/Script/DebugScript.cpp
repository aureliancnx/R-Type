#include "DebugScript.hpp"
#include "Debug.hpp"

using namespace RType::Script;

void Debug::initScript(lua_State* L) {
    lua_newtable(L);
    int debugTableIdx = lua_gettop(L);
    lua_pushvalue(L, debugTableIdx);
    lua_setglobal(L, "Debug");

    lua_pushcfunction(L, __log);
    lua_setfield(L, -2, "Log");

    lua_pushcfunction(L, __logWarning);
    lua_setfield(L, -2, "LogWarning");

    lua_pushcfunction(L, __logError);
    lua_setfield(L, -2, "LogError");

    lua_pushstring(L, "__index");
    lua_pushvalue(L, debugTableIdx);
    lua_settable(L, -3);
}

int Debug::__log(lua_State* L) {
    std::string message(lua_tostring(L, 1));
    KapEngine::Debug::log("[MapScript] " + message);
    return 0;
}

int Debug::__logWarning(lua_State* L) {
    std::string message(lua_tostring(L, 1));
    KapEngine::Debug::warning("[MapScript] " + message);
    return 0;
}

int Debug::__logError(lua_State* L) {
    std::string message(lua_tostring(L, 1));
    KapEngine::Debug::error("[MapScript] " + message);
    return 0;
}
