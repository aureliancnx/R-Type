//
// Created by leq on 12/11/22.
//

#ifndef RTYPE_CONVERTENUM_HPP
#define RTYPE_CONVERTENUM_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineEvents.hpp"
#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"

using namespace KapEngine;

namespace RType {

    class ConvertEnum : public Component {
      public:
        ConvertEnum(std::shared_ptr<GameObject> go);
        ~ConvertEnum();

        typedef enum {
            KEY_NULL = 0, // Key: NULL, used for no key pressed
            // Alphanumeric keys
            KEY_APOSTROPHE = 39, // Key: '
            KEY_COMMA = 44,      // Key: ,
            KEY_MINUS = 45,      // Key: -
            KEY_SLASH = 47,      // Key: /
            KEY_ZERO = 48,       // Key: 0
            KEY_ONE = 49,        // Key: 1
            KEY_TWO = 50,        // Key: 2
            KEY_THREE = 51,      // Key: 3
            KEY_FOUR = 52,       // Key: 4
            KEY_FIVE = 53,       // Key: 5
            KEY_SIX = 54,        // Key: 6
            KEY_SEVEN = 55,      // Key: 7
            KEY_EIGHT = 56,      // Key: 8
            KEY_NINE = 57,       // Key: 9
            KEY_SEMICOLON = 59,  // Key: ;
            KEY_EQUAL = 61,      // Key: =
            KEY_A = 65,          // Key: A | a
            KEY_B = 66,          // Key: B | b
            KEY_C = 67,          // Key: C | c
            KEY_D = 68,          // Key: D | d
            KEY_E = 69,          // Key: E | e
            KEY_F = 70,          // Key: F | f
            KEY_G = 71,          // Key: G | g
            KEY_H = 72,          // Key: H | h
            KEY_I = 73,          // Key: I | i
            KEY_J = 74,          // Key: J | j
            KEY_K = 75,          // Key: K | k
            KEY_L = 76,          // Key: L | l
            KEY_M = 77,          // Key: M | m
            KEY_N = 78,          // Key: N | n
            KEY_O = 79,          // Key: O | o
            KEY_P = 80,          // Key: P | p
            KEY_Q = 81,          // Key: Q | q
            KEY_R = 82,          // Key: R | r
            KEY_S = 83,          // Key: S | s
            KEY_T = 84,          // Key: T | t
            KEY_U = 85,          // Key: U | u
            KEY_V = 86,          // Key: V | v
            KEY_W = 87,          // Key: W | w
            KEY_X = 88,          // Key: X | x
            KEY_Y = 89,          // Key: Y | y
            KEY_Z = 90,          // Key: Z | z
            // Function keys
            KEY_SPACE = 32,      // Key: Space
            KEY_ESCAPE = 256,    // Key: Esc
            KEY_ENTER = 257,     // Key: Enter
            KEY_TAB = 258,       // Key: Tab
            KEY_BACKSPACE = 259, // Key: Backspace
            KEY_INSERT = 260,    // Key: Ins
            KEY_DELETE = 261,    // Key: Del
            KEY_RIGHT = 262,     // Key: Cursor right
            KEY_LEFT = 263,      // Key: Cursor left
            KEY_DOWN = 264,      // Key: Cursor down
            KEY_UP = 265,        // Key: Cursor up
            KEY_F1 = 290,        // Key: F1
            KEY_F2 = 291,        // Key: F2
            KEY_F3 = 292,        // Key: F3
            KEY_F4 = 293,        // Key: F4
            KEY_F5 = 294,        // Key: F5
            KEY_F6 = 295,        // Key: F6
            KEY_F7 = 296,        // Key: F7
            KEY_F8 = 297,        // Key: F8
            KEY_F9 = 298,        // Key: F9
            KEY_F10 = 299,       // Key: F10
            KEY_F11 = 300,       // Key: F11
            KEY_F12 = 301,       // Key: F12
        } KeyboardKey;

        static std::string KeyToString(int e) noexcept {
            switch (e) {
                case KEY_NULL:
                    return "NULL";
                case KEY_APOSTROPHE:
                    return "'";
                case KEY_COMMA:
                    return ",";
                case KEY_MINUS:
                    return "-";
                case KEY_SLASH:
                    return "/";
                case KEY_ZERO:
                    return "0";
                case KEY_ONE:
                    return "1";
                case KEY_TWO:
                    return "2";
                case KEY_THREE:
                    return "3";
                case KEY_FOUR:
                    return "4";
                case KEY_FIVE:
                    return "5";
                case KEY_SIX:
                    return "6";
                case KEY_SEVEN:
                    return "7";
                case KEY_EIGHT:
                    return "8";
                case KEY_NINE:
                    return "9";
                case KEY_SEMICOLON:
                    return ";";
                case KEY_EQUAL:
                    return "=";
                case KEY_A:
                    return "A";
                case KEY_B:
                    return "B";
                case KEY_C:
                    return "C";
                case KEY_D:
                    return "D";
                case KEY_E:
                    return "E";
                case KEY_F:
                    return "F";
                case KEY_G:
                    return "G";
                case KEY_H:
                    return "H";
                case KEY_I:
                    return "I";
                case KEY_J:
                    return "J";
                case KEY_K:
                    return "K";
                case KEY_L:
                    return "L";
                case KEY_M:
                    return "M";
                case KEY_N:
                    return "N";
                case KEY_O:
                    return "O";
                case KEY_P:
                    return "P";
                case KEY_Q:
                    return "Q";
                case KEY_R:
                    return "R";
                case KEY_S:
                    return "S";
                case KEY_T:
                    return "T";
                case KEY_U:
                    return "U";
                case KEY_V:
                    return "V";
                case KEY_W:
                    return "W";
                case KEY_X:
                    return "X";
                case KEY_Y:
                    return "Y";
                case KEY_Z:
                    return "Z";
                case KEY_SPACE:
                    return "SPACE";
                case KEY_ESCAPE:
                    return "Esc";
                case KEY_ENTER:
                    return "Enter";
                case KEY_TAB:
                    return "Tab";
                case KEY_BACKSPACE:
                    return "Backspace";
                case KEY_INSERT:
                    return "Ins";
                case KEY_DELETE:
                    return "Delete";
                case KEY_RIGHT:
                    return "Cursor Right";
                case KEY_LEFT:
                    return "Cursor Left";
                case KEY_DOWN:
                    return "Cursor Down";
                case KEY_UP:
                    return "Cursor Up";
                case KEY_F1:
                    return "F1";
                case KEY_F2:
                    return "F2";
                case KEY_F3:
                    return "F3";
                case KEY_F4:
                    return "F4";
                case KEY_F5:
                    return "F5";
                case KEY_F6:
                    return "F6";
                case KEY_F7:
                    return "F7";
                case KEY_F8:
                    return "F8";
                case KEY_F9:
                    return "F9";
                case KEY_F10:
                    return "F10";
                case KEY_F11:
                    return "F11";
                case KEY_F12:
                    return "F12";
                default:
                    throw KapEngine::Errors::Error("Unimplemented item");
            }
        }

        void onAwake() override;
        void onUpdate() override;
        void setTextKey();

      protected:
      private:
        std::shared_ptr<KapEngine::GameObject> _buttonKeyBoard;
    };

} // namespace RType

#endif // RTYPE_CONVERTENUM_HPP
