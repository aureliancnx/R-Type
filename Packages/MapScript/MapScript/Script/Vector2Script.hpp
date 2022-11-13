#pragma once

#include "MapScript/Lua.hpp"

namespace RType::Script {
    class Vector2 {
      public:
        float x = 0;
        float y = 0;

        Vector2() = default;
        ~Vector2() = default;

        void dump() const;

        static void initScript(lua_State *L);
        static int __create(lua_State *L);
        static int __destroy(lua_State *L);
        static int __index(lua_State *L);
        static int __newIndex(lua_State *L);
        static int __dump(lua_State *L);
    };
} // namespace RType::Script
