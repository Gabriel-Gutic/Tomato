#include "pchTomato.h"
#include "KeyboardEvent.h"

#include "KeyboardCodes.h"


namespace Tomato
{
    std::unordered_map<int, std::string> KeyboardEvent::s_KeyNames = {
        { TOMATO_KEY_UNKNOWN,           "Unknown"},
        { TOMATO_KEY_SPACE,             "Space"},
        { TOMATO_KEY_APOSTROPHE,        "'"},
        { TOMATO_KEY_COMMA,             ","},
        { TOMATO_KEY_MINUS,             "-"},
        { TOMATO_KEY_PERIOD,            "."},
        { TOMATO_KEY_SLASH,             "/"},
        { TOMATO_KEY_0,                 "0"},
        { TOMATO_KEY_1,                 "1"},
        { TOMATO_KEY_2,                 "2"},
        { TOMATO_KEY_3,                 "3"},
        { TOMATO_KEY_4,                 "4"},
        { TOMATO_KEY_5,                 "5"},
        { TOMATO_KEY_6,                 "6"},
        { TOMATO_KEY_7,                 "7"},
        { TOMATO_KEY_8,                 "8"},
        { TOMATO_KEY_9,                 "9"},
        { TOMATO_KEY_SEMICOLON,         ";"},
        { TOMATO_KEY_EQUAL,             "="},
        { TOMATO_KEY_A,                 "A"},
        { TOMATO_KEY_B,                 "B"},
        { TOMATO_KEY_C,                 "C"},
        { TOMATO_KEY_D,                 "D"},
        { TOMATO_KEY_E,                 "E"},
        { TOMATO_KEY_F,                 "F"},
        { TOMATO_KEY_G,                 "G"},
        { TOMATO_KEY_H,                 "H"},
        { TOMATO_KEY_I,                 "I"},
        { TOMATO_KEY_J,                 "J"},
        { TOMATO_KEY_K,                 "K"},
        { TOMATO_KEY_L,                 "L"},
        { TOMATO_KEY_M,                 "M"},
        { TOMATO_KEY_N,                 "N"},
        { TOMATO_KEY_O,                 "O"},
        { TOMATO_KEY_P,                 "P"},
        { TOMATO_KEY_Q,                 "Q"},
        { TOMATO_KEY_R,                 "R"},
        { TOMATO_KEY_S,                 "S"},
        { TOMATO_KEY_T,                 "T"},
        { TOMATO_KEY_U,                 "U"},
        { TOMATO_KEY_V,                 "V"},
        { TOMATO_KEY_W,                 "W"},
        { TOMATO_KEY_X,                 "X"},
        { TOMATO_KEY_Y,                 "Y"},
        { TOMATO_KEY_Z,                 "Z"},
        { TOMATO_KEY_LEFT_BRACKET,      "["},
        { TOMATO_KEY_BACKSLASH,         "\\"},
        { TOMATO_KEY_RIGHT_BRACKET,     "]"},
        { TOMATO_KEY_GRAVE_ACCENT,      "`"},
        { TOMATO_KEY_WORLD_1,           "Non-US #1"},
        { TOMATO_KEY_WORLD_2,           "Non-US #2"},
        { TOMATO_KEY_ESCAPE,            "Escape"},
        { TOMATO_KEY_ENTER,             "Enter"},
        { TOMATO_KEY_TAB,               "Tab"},
        { TOMATO_KEY_BACKSPACE,         "Backspace"},
        { TOMATO_KEY_INSERT,            "Insert"},
        { TOMATO_KEY_DELETE,            "Delete"},
        { TOMATO_KEY_RIGHT,             "Right Arrow"},
        { TOMATO_KEY_LEFT,              "Left Arrow"},
        { TOMATO_KEY_DOWN,              "Down Arrow"},
        { TOMATO_KEY_UP,                "Up Arrow"},
        { TOMATO_KEY_PAGE_UP,           "PgUp"},
        { TOMATO_KEY_PAGE_DOWN,         "PgDn"},
        { TOMATO_KEY_HOME,              "Home"},
        { TOMATO_KEY_END,               "End"},
        { TOMATO_KEY_CAPS_LOCK,         "CapsLock"},
        { TOMATO_KEY_SCROLL_LOCK,       "ScrollLock"},
        { TOMATO_KEY_NUM_LOCK,          "NumLock"},
        { TOMATO_KEY_PRINT_SCREEN,      "PrtSc"},
        { TOMATO_KEY_PAUSE,             "Pause"},
        { TOMATO_KEY_F1,                "F1"},
        { TOMATO_KEY_F2,                "F2"},
        { TOMATO_KEY_F3,                "F3"},
        { TOMATO_KEY_F4,                "F4"},
        { TOMATO_KEY_F5,                "F5"},
        { TOMATO_KEY_F6,                "F6"},
        { TOMATO_KEY_F7,                "F7"},
        { TOMATO_KEY_F8,                "F8"},
        { TOMATO_KEY_F9,                "F9"},
        { TOMATO_KEY_F10,               "F10"},
        { TOMATO_KEY_F11,               "F11"},
        { TOMATO_KEY_F12,               "F12"},
        { TOMATO_KEY_F13,               "F13"},
        { TOMATO_KEY_F14,               "F14"},
        { TOMATO_KEY_F15,               "F15"},
        { TOMATO_KEY_F16,               "F16"},
        { TOMATO_KEY_F17,               "F17"},
        { TOMATO_KEY_F18,               "F18"},
        { TOMATO_KEY_F19,               "F19"},
        { TOMATO_KEY_F20,               "F20"},
        { TOMATO_KEY_F21,               "F21"},
        { TOMATO_KEY_F22,               "F22"},
        { TOMATO_KEY_F23,               "F23"},
        { TOMATO_KEY_F24,               "F24"},
        { TOMATO_KEY_F25,               "F25"},
        { TOMATO_KEY_NUMPAD_0,          "Numpad 0"},
        { TOMATO_KEY_NUMPAD_1,          "Numpad 1"},
        { TOMATO_KEY_NUMPAD_2,          "Numpad 2"},
        { TOMATO_KEY_NUMPAD_3,          "Numpad 3"},
        { TOMATO_KEY_NUMPAD_4,          "Numpad 4"},
        { TOMATO_KEY_NUMPAD_5,          "Numpad 5"},
        { TOMATO_KEY_NUMPAD_6,          "Numpad 6"},
        { TOMATO_KEY_NUMPAD_7,          "Numpad 7"},
        { TOMATO_KEY_NUMPAD_8,          "Numpad 8"},
        { TOMATO_KEY_NUMPAD_9,          "Numpad 9"},
        { TOMATO_KEY_NUMPAD_DECIMAL,    "Numpad ." },
        { TOMATO_KEY_NUMPAD_DIVIDE,     "Numpad /" },
        { TOMATO_KEY_NUMPAD_MULTIPLY,   "Numpad *" },
        { TOMATO_KEY_NUMPAD_SUBTRACT,   "Numpad -" },
        { TOMATO_KEY_NUMPAD_ADD,        "Numpad +" },
        { TOMATO_KEY_NUMPAD_ENTER,      "Numpad Enter" },
        { TOMATO_KEY_NUMPAD_EQUAL,      "Numpad =" },
        { TOMATO_KEY_LEFT_SHIFT,        "Left Shift" },
        { TOMATO_KEY_RIGHT_SHIFT,       "Right Shift" },
        { TOMATO_KEY_SHIFT,             "Shift"},
        { TOMATO_KEY_LEFT_CONTROL,      "Left Control" },
        { TOMATO_KEY_RIGHT_CONTROL,     "Right Control" },
        { TOMATO_KEY_CONTROL,           "Control" },
        { TOMATO_KEY_LEFT_ALT,          "Left Alt" },
        { TOMATO_KEY_RIGHT_ALT,         "Right Alt" },
        { TOMATO_KEY_ALT,               "Alt" },
        { TOMATO_KEY_LEFT_SUPER,        "Left Super" },
        { TOMATO_KEY_RIGHT_SUPER,       "Right Super" },
        { TOMATO_KEY_SUPER,             "Super" },
        { TOMATO_KEY_MENU,              "Menu"},
    };
    bool operator==(const KeyboardEvent::Code& code, int scancode)
    {
        bool result;
        switch (scancode)
        {
        case TOMATO_KEY_SHIFT:
            result = (code.Value == TOMATO_KEY_LEFT_SHIFT) || (code.Value == TOMATO_KEY_RIGHT_SHIFT);
            break;
        case TOMATO_KEY_CONTROL:
            result = (code.Value == TOMATO_KEY_LEFT_CONTROL) || (code.Value == TOMATO_KEY_RIGHT_CONTROL);
            break;
        case TOMATO_KEY_ALT:
            result = (code.Value == TOMATO_KEY_LEFT_ALT) || (code.Value == TOMATO_KEY_RIGHT_ALT);
            break;
        case TOMATO_KEY_SUPER:
            result = (code.Value == TOMATO_KEY_LEFT_SUPER) || (code.Value == TOMATO_KEY_RIGHT_SUPER);
            break;
        default:
            result = (code.Value == scancode);
            break;
        }

        return result;
    }

    bool operator==(int scancode, const KeyboardEvent::Code& code)
    {
        return code == scancode;
    }

    bool operator!=(const KeyboardEvent::Code& code, int scancode)
    {
        return !(code == scancode); 
    }

    bool operator!=(int scancode, const KeyboardEvent::Code& code)
    {
        return code != scancode;
    }

    KeyboardEvent::Code::Code(int value)
        :Value(value)
    {
    }

    std::string KeyboardEvent::ToString() const
    {
        std::stringstream ss;
        ss << this->GetName() << ": ";
        if (s_KeyNames.find(m_Key.Value) == s_KeyNames.end())
            ss << m_Key.Value;
        else ss << s_KeyNames[m_Key.Value];
        return ss.str();
    }

    std::string CharEvent::ToString() const
    {
        std::stringstream ss;
        ss << this->GetName() << ": " << (char)m_Char;
        return ss.str();
    }
}


