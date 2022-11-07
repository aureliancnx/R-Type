#pragma once

#include "MapScript/Lua.hpp"

namespace RType::Script {
    class Math {
      public:
        Math() = default;
        ~Math() = default;

        static void initScript(lua_State* L);

      private:
        static int __rand(lua_State* L);
    };
} // namespace RType::Script
