#pragma once

#include "MapScript/Lua.hpp"
#include "MapScript/MapScript.hpp"
#include "Vector2Script.hpp"
#include "RectangleScript.hpp"
#include "SpriteAnimationScript.hpp"
#include "Debug.hpp"
#include <string>
#include <iostream>

namespace RType {
    class MapScript;
}

namespace RType::Script {
    class Enemy {
      public:
        std::string name;
        std::string pathSprite;
        Rectangle *rectangle = nullptr;
        Vector2 *scale = nullptr;
        SpriteAnimation *animation = nullptr;

        Enemy() = default;
        ~Enemy() = default;

        void dump() const;

        static void initScript(lua_State *L, RType::MapScript *mapScript);

      private:
        static int __create(lua_State *L);
        static int __destroy(lua_State *L);
        static int __index(lua_State *L);
        static int __newIndex(lua_State *L);
        static int __dump(lua_State *L);
    };
} // namespace RType::Script
