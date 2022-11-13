#pragma once

#include <exception>
#include <string>

namespace RType {
    class LuaException : public std::exception {
        std::string _message;

      public:
        LuaException(std::string const &message) : _message(message) {}
        ~LuaException() = default;

        char const *what() const noexcept { return _message.c_str(); }
    };
} // namespace RType
