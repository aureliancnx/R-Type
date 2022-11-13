#pragma once

#include "MapScript/Lua.hpp"
#include "RectangleScript.hpp"

namespace RType::Script {
    class SpriteAnimation {
      public:
        float duration = 0;
        bool loop = true;
        Rectangle *rectangle = nullptr;
        int nbFrames = 0;

        SpriteAnimation() = default;
        ~SpriteAnimation() = default;

        static void initScript(lua_State *L);

      private:
        static int __create(lua_State *L);
        static int __destroy(lua_State *L);
        static int __index(lua_State *L);
        static int __newIndex(lua_State *L);
    };
} // namespace RType::Script
