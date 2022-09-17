#include "pchTomato.h"
#include "DirectXCodes.h"

#include "Event/KeyboardCodes.h"
#include "Event/MouseCodes.h"


namespace Tomato
{
	std::unordered_map<uint64_t, int> DirectXCodes::s_Data;
	void DirectXCodes::Setup()
	{
		/* Mouse Buttons */
		s_Data[VK_LBUTTON] = TOMATO_MOUSE_BUTTON_LEFT;
		s_Data[VK_RBUTTON] = TOMATO_MOUSE_BUTTON_RIGHT;
		s_Data[VK_MBUTTON] = TOMATO_MOUSE_BUTTON_MIDDLE;
		s_Data[VK_XBUTTON1] = TOMATO_MOUSE_BUTTON_4;
		s_Data[VK_XBUTTON2] = TOMATO_MOUSE_BUTTON_5;

		/* Printable keys */
		s_Data[VK_SPACE] = TOMATO_KEY_SPACE;
		s_Data[VK_OEM_7] = TOMATO_KEY_APOSTROPHE;
		s_Data[VK_OEM_COMMA] = TOMATO_KEY_COMMA;
		s_Data[VK_OEM_MINUS] = TOMATO_KEY_MINUS;
		s_Data[VK_OEM_PERIOD] = TOMATO_KEY_PERIOD;
		s_Data[VK_OEM_2] = TOMATO_KEY_SLASH;
		s_Data[0x30] = TOMATO_KEY_0;
		s_Data[0x31] = TOMATO_KEY_1;
		s_Data[0x32] = TOMATO_KEY_2;
		s_Data[0x33] = TOMATO_KEY_3;
		s_Data[0x34] = TOMATO_KEY_4;
		s_Data[0x35] = TOMATO_KEY_5;
		s_Data[0x36] = TOMATO_KEY_6;
		s_Data[0x37] = TOMATO_KEY_7;
		s_Data[0x38] = TOMATO_KEY_8;
		s_Data[0x39] = TOMATO_KEY_9;
		s_Data[VK_OEM_1] = TOMATO_KEY_SEMICOLON;
		s_Data[VK_OEM_PLUS] = TOMATO_KEY_EQUAL;
		s_Data[0x41] = TOMATO_KEY_A;
		s_Data[0x42] = TOMATO_KEY_B;
		s_Data[0x43] = TOMATO_KEY_C;
		s_Data[0x44] = TOMATO_KEY_D;
		s_Data[0x45] = TOMATO_KEY_E;
		s_Data[0x46] = TOMATO_KEY_F;
		s_Data[0x47] = TOMATO_KEY_G;
		s_Data[0x48] = TOMATO_KEY_H;
		s_Data[0x49] = TOMATO_KEY_I;
		s_Data[0x4A] = TOMATO_KEY_J;
		s_Data[0x4B] = TOMATO_KEY_K;
		s_Data[0x4C] = TOMATO_KEY_L;
		s_Data[0x4D] = TOMATO_KEY_M;
		s_Data[0x4E] = TOMATO_KEY_N;
		s_Data[0x4F] = TOMATO_KEY_O;
		s_Data[0x50] = TOMATO_KEY_P;
		s_Data[0x51] = TOMATO_KEY_Q;
		s_Data[0x52] = TOMATO_KEY_R;
		s_Data[0x53] = TOMATO_KEY_S;
		s_Data[0x54] = TOMATO_KEY_T;
		s_Data[0x55] = TOMATO_KEY_U;
		s_Data[0x56] = TOMATO_KEY_V;
		s_Data[0x57] = TOMATO_KEY_W;
		s_Data[0x58] = TOMATO_KEY_X;
		s_Data[0x59] = TOMATO_KEY_Y;
		s_Data[0x5A] = TOMATO_KEY_Z;
		s_Data[VK_OEM_4] = TOMATO_KEY_LEFT_BRACKET; /* [ */
		s_Data[VK_OEM_5] = TOMATO_KEY_BACKSLASH;
		s_Data[VK_OEM_6] = TOMATO_KEY_RIGHT_BRACKET; /* ] */
		s_Data[VK_OEM_3] = TOMATO_KEY_GRAVE_ACCENT; /* ` */

		/* Function keys */
		s_Data[VK_ESCAPE] = TOMATO_KEY_ESCAPE;
		s_Data[VK_RETURN] = TOMATO_KEY_ENTER;
		s_Data[VK_TAB] = TOMATO_KEY_TAB;
		s_Data[VK_BACK] = TOMATO_KEY_BACKSPACE;
		s_Data[VK_INSERT] = TOMATO_KEY_INSERT;
		s_Data[VK_DELETE] = TOMATO_KEY_DELETE;
		s_Data[VK_RIGHT] = TOMATO_KEY_RIGHT;
		s_Data[VK_LEFT] = TOMATO_KEY_LEFT;
		s_Data[VK_DOWN] = TOMATO_KEY_DOWN;
		s_Data[VK_UP] = TOMATO_KEY_UP;
		s_Data[VK_PRIOR] = TOMATO_KEY_PAGE_UP;
		s_Data[VK_NEXT] = TOMATO_KEY_PAGE_DOWN;
		s_Data[VK_HOME] = TOMATO_KEY_HOME;
		s_Data[VK_END] = TOMATO_KEY_END;
		s_Data[VK_CAPITAL] = TOMATO_KEY_CAPS_LOCK;
		s_Data[VK_SCROLL] = TOMATO_KEY_SCROLL_LOCK;
		s_Data[VK_NUMLOCK] = TOMATO_KEY_NUM_LOCK;
		s_Data[VK_SNAPSHOT] = TOMATO_KEY_PRINT_SCREEN;
		s_Data[VK_PAUSE] = TOMATO_KEY_PAUSE;
		s_Data[VK_F1] = TOMATO_KEY_F1;
		s_Data[VK_F2] = TOMATO_KEY_F2;
		s_Data[VK_F3] = TOMATO_KEY_F3;
		s_Data[VK_F4] = TOMATO_KEY_F4;
		s_Data[VK_F5] = TOMATO_KEY_F5;
		s_Data[VK_F6] = TOMATO_KEY_F6;
		s_Data[VK_F7] = TOMATO_KEY_F7;
		s_Data[VK_F8] = TOMATO_KEY_F8;
		s_Data[VK_F9] = TOMATO_KEY_F9;
		s_Data[VK_F10] = TOMATO_KEY_F10;
		s_Data[VK_F11] = TOMATO_KEY_F11;
		s_Data[VK_F12] = TOMATO_KEY_F12;
		s_Data[VK_F13] = TOMATO_KEY_F13;
		s_Data[VK_F14] = TOMATO_KEY_F14;
		s_Data[VK_F15] = TOMATO_KEY_F15;
		s_Data[VK_F16] = TOMATO_KEY_F16;
		s_Data[VK_F17] = TOMATO_KEY_F17;
		s_Data[VK_F18] = TOMATO_KEY_F18;
		s_Data[VK_F19] = TOMATO_KEY_F19;
		s_Data[VK_F20] = TOMATO_KEY_F20;
		s_Data[VK_F21] = TOMATO_KEY_F21;
		s_Data[VK_F22] = TOMATO_KEY_F22;
		s_Data[VK_F23] = TOMATO_KEY_F23;
		s_Data[VK_F24] = TOMATO_KEY_F24;

		s_Data[VK_NUMPAD0] = TOMATO_KEY_NUMPAD_0;
		s_Data[VK_NUMPAD1] = TOMATO_KEY_NUMPAD_1;
		s_Data[VK_NUMPAD2] = TOMATO_KEY_NUMPAD_2;
		s_Data[VK_NUMPAD3] = TOMATO_KEY_NUMPAD_3;
		s_Data[VK_NUMPAD4] = TOMATO_KEY_NUMPAD_4;
		s_Data[VK_NUMPAD5] = TOMATO_KEY_NUMPAD_5;
		s_Data[VK_NUMPAD6] = TOMATO_KEY_NUMPAD_6;
		s_Data[VK_NUMPAD7] = TOMATO_KEY_NUMPAD_7;
		s_Data[VK_NUMPAD8] = TOMATO_KEY_NUMPAD_8;
		s_Data[VK_NUMPAD9] = TOMATO_KEY_NUMPAD_9;
		s_Data[VK_DECIMAL] = TOMATO_KEY_NUMPAD_DECIMAL;
		s_Data[VK_DIVIDE] = TOMATO_KEY_NUMPAD_DIVIDE;
		s_Data[VK_MULTIPLY] = TOMATO_KEY_NUMPAD_MULTIPLY;
		s_Data[VK_SUBTRACT] = TOMATO_KEY_NUMPAD_SUBTRACT;
		s_Data[VK_ADD] = TOMATO_KEY_NUMPAD_ADD;
		s_Data[VK_SEPARATOR] = TOMATO_KEY_NUMPAD_ENTER;
		s_Data[VK_LSHIFT] = TOMATO_KEY_LEFT_SHIFT;
		s_Data[VK_LCONTROL] = TOMATO_KEY_LEFT_CONTROL;
		s_Data[VK_LMENU] = TOMATO_KEY_LEFT_ALT;
		s_Data[VK_LWIN] = TOMATO_KEY_LEFT_SUPER;
		s_Data[VK_RSHIFT] = TOMATO_KEY_RIGHT_SHIFT;
		s_Data[VK_RCONTROL] = TOMATO_KEY_RIGHT_CONTROL;
		s_Data[VK_RMENU] = TOMATO_KEY_RIGHT_ALT;
		s_Data[VK_RWIN] = TOMATO_KEY_RIGHT_SUPER;
		s_Data[VK_SHIFT] = TOMATO_KEY_SHIFT;
		s_Data[VK_CONTROL] = TOMATO_KEY_CONTROL;
		s_Data[VK_MENU] = TOMATO_KEY_ALT;
		s_Data[VK_APPS] = TOMATO_KEY_MENU;
	}

	int DirectXCodes::Cast(uint64_t code)
	{
		if (s_Data.find(code) == s_Data.end())
		{
			TOMATO_PRINT("Undefined keyboard key or mouse button code '{0}' in DirectX RendererAPI", code);
			return TOMATO_KEY_UNKNOWN;
		}
		return s_Data[code];
	}
}
