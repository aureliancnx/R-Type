#include "SpriteAnimationScript.hpp"

using namespace RType::Script;

void SpriteAnimation::initScript(lua_State* L) {
    lua_newtable(L);
    int spriteAnimationTableIdx = lua_gettop(L);
    lua_pushvalue(L, spriteAnimationTableIdx);
    lua_setglobal(L, "SpriteAnimation");
}
