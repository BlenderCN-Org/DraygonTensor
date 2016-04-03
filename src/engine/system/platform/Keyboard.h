#pragma once

#include <string>

namespace ds_platform
{
class Keyboard
{
public:
    enum class State
    {
        Key_Pressed,
        Key_Released
    };

    enum class Key
    {
        Key_First = 0x0,

        Key_Backspace = '\b',
        Key_Tab = '\t',
        Key_Return = '\r',
        Key_Escape = '\033',
        Key_Space = ' ',
        Key_Exclamation = '!',
        Key_DblQuote = '\"',
        Key_Hash = '#',
        Key_Dollar = '$',
        Key_Percent = '%',
        Key_Ampersand = '&',
        Key_Quote = '\'',
        Key_LeftParen = '(',
        Key_RightParen = ')',
        Key_Asterisk = '*',
        Key_Plus = '+',
        Key_Comma = ',',
        Key_Minus = '-',
        Key_Period = '.',
        Key_Slash = '/',
        Key_0 = '0',
        Key_1 = '1',
        Key_2 = '2',
        Key_3 = '3',
        Key_4 = '4',
        Key_5 = '5',
        Key_6 = '6',
        Key_7 = '7',
        Key_8 = '8',
        Key_9 = '9',
        Key_Colon = ':',
        Key_SemiColon = ';',
        Key_Less = '<',
        Key_Greater = '>',
        Key_Question = '?',
        Key_At = '@',
        Key_LeftBracket = '[',
        Key_RightBracket = ']',
        Caret = '^',
        Key_UnderScore = '_',
        Key_BackQuote = '`',
        Key_a = 'a',
        Key_b = 'b',
        Key_c = 'c',
        Key_d = 'd',
        Key_e = 'e',
        Key_f = 'f',
        Key_g = 'g',
        Key_h = 'h',
        Key_i = 'i',
        Key_j = 'j',
        Key_k = 'k',
        Key_l = 'l',
        Key_m = 'm',
        Key_n = 'n',
        Key_o = 'o',
        Key_p = 'p',
        Key_q = 'q',
        Key_r = 'r',
        Key_s = 's',
        Key_t = 't',
        Key_u = 'u',
        Key_v = 'v',
        Key_w = 'w',
        Key_x = 'x',
        Key_y = 'y',
        Key_z = 'z',
        Key_Delete = '\177',
        Key_CapsLock = 0x40000039,
        Key_F1 = 0x4000003A,
        Key_F2 = 0x4000003B,
        Key_F3 = 0x4000003C,
        Key_F4 = 0x4000003D,
        Key_F5 = 0x4000003E,
        Key_F6 = 0x4000003F,
        Key_F7 = 0x40000040,
        Key_F8 = 0x40000041,
        Key_F9 = 0x40000042,
        Key_F10 = 0x40000043,
        Key_F11 = 0x40000044,
        Key_F12 = 0x40000045,
        Key_PrintScreen = 0x40000046,
        Key_ScrollLock = 0x40000047,
        Key_Pause = 0x40000048,
        Key_Insert = 0x40000049,
        Key_Home = 0x4000004A,
        Key_PageUp = 0x4000004B,
        Key_End = 0x4000004D,
        Key_PageDown = 0x4000004E,
        Key_RightArrow = 0x4000004F,
        Key_LeftArrow = 0x40000050,
        Key_DownArrow = 0x40000051,
        Key_UpArrow = 0x40000052,
        Key_LCtrl = 0x400000E0,
        Key_LShift = 0x400000E1,
        Key_LAlt = 0x400000E2,
        Key_RCtrl = 0x400000E4,
        Key_RShift = 0x400000E5,
        Key_RAlt = 0x400000E6,

        Key_Last = ~0x0,
    };

    /**
     * Get a string representing the given key.
     *
     * @param   key  Key, key to get string for.
     * @return       std::string, string representing key.
     */
    static std::string PrintKey(Key key);
};
}
