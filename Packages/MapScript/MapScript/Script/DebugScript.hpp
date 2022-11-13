#pragma once

#include "MapScript/Lua.hpp"

namespace RType::Script {
    class Debug {
      public:
        Debug() = default;
        ~Debug() = default;

        static void initScript(lua_State *L);

      private:
        static int __log(lua_State *L);
        static int __logWarning(lua_State *L);
        static int __logError(lua_State *L);
    };
} // namespace RType::Script
