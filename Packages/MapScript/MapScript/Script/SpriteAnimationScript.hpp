#pragma once

#include "MapScript/Lua.hpp"
#include "RectangleScript.hpp"

namespace RType::Script {
    class SpriteAnimation {
      public:
        float duration = 0;
        Rectangle* rectangle{};
        int nbFrames = 0;

        SpriteAnimation() = default;
        ~SpriteAnimation() = default;

        static void initScript(lua_State* L);
    };
}
