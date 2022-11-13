#pragma once

#include "MapScript/Lua.hpp"

namespace RType::Script {
    class Math {
      public:
        Math() = default;
        ~Math() = default;

        static void initScript(lua_State *L);

      private:
        static int __abs(lua_State *L);
        static int __floor(lua_State *L);
        static int __mod(lua_State *L);
        static int __random(lua_State *L);
        static int __sin(lua_State *L);
        static int __cos(lua_State *L);
        static int __tan(lua_State *L);
    };
} // namespace RType::Script
