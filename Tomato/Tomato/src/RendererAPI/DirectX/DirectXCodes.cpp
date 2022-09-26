#include "pchTomato.h"
#include "DirectXCodes.h"

#ifdef TOMATO_PLATFORM_WINDOWS

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

	int DirectXCodes::Cast(uint64_t directXCode)
	{
		if (s_Data.find(directXCode) == s_Data.end())
		{
			TOMATO_PRINT("Undefined keyboard key or mouse button code '{0}' in DirectX RendererAPI", directXCode);
			return TOMATO_KEY_UNKNOWN;
		}
		return s_Data[directXCode];
	}

	uint64_t DirectXCodes::CastBack(int tomatoCode)
	{
		switch (tomatoCode)
		{
		case TOMATO_MOUSE_BUTTON_LEFT: return VK_LBUTTON;
		case TOMATO_MOUSE_BUTTON_RIGHT: return VK_RBUTTON;
		case TOMATO_MOUSE_BUTTON_MIDDLE: return VK_MBUTTON;
		case TOMATO_MOUSE_BUTTON_4: return VK_XBUTTON1;
		case TOMATO_MOUSE_BUTTON_5: return VK_XBUTTON2;
		case TOMATO_KEY_SPACE: return VK_SPACE;
		case TOMATO_KEY_APOSTROPHE: return VK_OEM_7;
		case TOMATO_KEY_COMMA: return VK_OEM_COMMA;
		case TOMATO_KEY_MINUS: return VK_OEM_MINUS;
		case TOMATO_KEY_PERIOD: return VK_OEM_PERIOD;
		case TOMATO_KEY_SLASH: return VK_OEM_2;
		case TOMATO_KEY_0: return 0x30;
		case TOMATO_KEY_1: return 0x31;
		case TOMATO_KEY_2: return 0x32;
		case TOMATO_KEY_3: return 0x33;
		case TOMATO_KEY_4: return 0x34;
		case TOMATO_KEY_5: return 0x35;
		case TOMATO_KEY_6: return 0x36;
		case TOMATO_KEY_7: return 0x37;
		case TOMATO_KEY_8: return 0x38;
		case TOMATO_KEY_9: return 0x39;
		case TOMATO_KEY_SEMICOLON: return VK_OEM_1;
		case TOMATO_KEY_EQUAL: return VK_OEM_PLUS;
		case TOMATO_KEY_A: return 0x41;
		case TOMATO_KEY_B: return 0x42;
		case TOMATO_KEY_C: return 0x43;
		case TOMATO_KEY_D: return 0x44;
		case TOMATO_KEY_E: return 0x45;
		case TOMATO_KEY_F: return 0x46;
		case TOMATO_KEY_G: return 0x47;
		case TOMATO_KEY_H: return 0x48;
		case TOMATO_KEY_I: return 0x49;
		case TOMATO_KEY_J: return 0x4A;
		case TOMATO_KEY_K: return 0x4B;
		case TOMATO_KEY_L: return 0x4C;
		case TOMATO_KEY_M: return 0x4D;
		case TOMATO_KEY_N: return 0x4E;
		case TOMATO_KEY_O: return 0x4F;
		case TOMATO_KEY_P: return 0x50;
		case TOMATO_KEY_Q: return 0x51;
		case TOMATO_KEY_R: return 0x52;
		case TOMATO_KEY_S: return 0x53;
		case TOMATO_KEY_T: return 0x54;
		case TOMATO_KEY_U: return 0x55;
		case TOMATO_KEY_V: return 0x56;
		case TOMATO_KEY_W: return 0x57;
		case TOMATO_KEY_X: return 0x58;
		case TOMATO_KEY_Y: return 0x59;
		case TOMATO_KEY_Z: return 0x5A;
		case TOMATO_KEY_LEFT_BRACKET: return VK_OEM_4;
		case TOMATO_KEY_BACKSLASH: return VK_OEM_5;
		case TOMATO_KEY_RIGHT_BRACKET: return VK_OEM_6;
		case TOMATO_KEY_GRAVE_ACCENT: return VK_OEM_3;
		case TOMATO_KEY_ESCAPE: return VK_ESCAPE;
		case TOMATO_KEY_ENTER: return VK_RETURN;
		case TOMATO_KEY_TAB: return VK_TAB;
		case TOMATO_KEY_BACKSPACE: return VK_BACK;
		case TOMATO_KEY_INSERT: return VK_INSERT;
		case TOMATO_KEY_DELETE: return VK_DELETE;
		case TOMATO_KEY_RIGHT: return VK_RIGHT;
		case TOMATO_KEY_LEFT: return VK_LEFT;
		case TOMATO_KEY_DOWN: return VK_DOWN;
		case TOMATO_KEY_UP: return VK_UP;
		case TOMATO_KEY_PAGE_UP: return VK_PRIOR;
		case TOMATO_KEY_PAGE_DOWN: return VK_NEXT;
		case TOMATO_KEY_HOME: return VK_HOME;
		case TOMATO_KEY_END: return VK_END;
		case TOMATO_KEY_CAPS_LOCK: return VK_CAPITAL;
		case TOMATO_KEY_SCROLL_LOCK: return VK_SCROLL;
		case TOMATO_KEY_NUM_LOCK: return VK_NUMLOCK;
		case TOMATO_KEY_PRINT_SCREEN: return VK_SNAPSHOT;
		case TOMATO_KEY_PAUSE: return VK_PAUSE;
		case TOMATO_KEY_F1: return VK_F1;
		case TOMATO_KEY_F2: return VK_F2;
		case TOMATO_KEY_F3: return VK_F3;
		case TOMATO_KEY_F4: return VK_F4;
		case TOMATO_KEY_F5: return VK_F5;
		case TOMATO_KEY_F6: return VK_F6;
		case TOMATO_KEY_F7: return VK_F7;
		case TOMATO_KEY_F8: return VK_F8;
		case TOMATO_KEY_F9: return VK_F9;
		case TOMATO_KEY_F10: return VK_F10;
		case TOMATO_KEY_F11: return VK_F11;
		case TOMATO_KEY_F12: return VK_F12;
		case TOMATO_KEY_F13: return VK_F13;
		case TOMATO_KEY_F14: return VK_F14;
		case TOMATO_KEY_F15: return VK_F15;
		case TOMATO_KEY_F16: return VK_F16;
		case TOMATO_KEY_F17: return VK_F17;
		case TOMATO_KEY_F18: return VK_F18;
		case TOMATO_KEY_F19: return VK_F19;
		case TOMATO_KEY_F20: return VK_F20;
		case TOMATO_KEY_F21: return VK_F21;
		case TOMATO_KEY_F22: return VK_F22;
		case TOMATO_KEY_F23: return VK_F23;
		case TOMATO_KEY_F24: return VK_F24;
		case TOMATO_KEY_NUMPAD_0: return VK_NUMPAD0;
		case TOMATO_KEY_NUMPAD_1: return VK_NUMPAD1;
		case TOMATO_KEY_NUMPAD_2: return VK_NUMPAD2;
		case TOMATO_KEY_NUMPAD_3: return VK_NUMPAD3;
		case TOMATO_KEY_NUMPAD_4: return VK_NUMPAD4;
		case TOMATO_KEY_NUMPAD_5: return VK_NUMPAD5;
		case TOMATO_KEY_NUMPAD_6: return VK_NUMPAD6;
		case TOMATO_KEY_NUMPAD_7: return VK_NUMPAD7;
		case TOMATO_KEY_NUMPAD_8: return VK_NUMPAD8;
		case TOMATO_KEY_NUMPAD_9: return VK_NUMPAD9;
		case TOMATO_KEY_NUMPAD_DECIMAL: return VK_DECIMAL;
		case TOMATO_KEY_NUMPAD_DIVIDE: return VK_DIVIDE;
		case TOMATO_KEY_NUMPAD_MULTIPLY: return VK_MULTIPLY;
		case TOMATO_KEY_NUMPAD_SUBTRACT: return VK_SUBTRACT;
		case TOMATO_KEY_NUMPAD_ADD: return VK_ADD;
		case TOMATO_KEY_NUMPAD_ENTER: return VK_SEPARATOR;
		case TOMATO_KEY_LEFT_SHIFT: return VK_LSHIFT;
		case TOMATO_KEY_LEFT_CONTROL: return VK_LCONTROL;
		case TOMATO_KEY_LEFT_ALT: return VK_LMENU;
		case TOMATO_KEY_LEFT_SUPER: return VK_LWIN;
		case TOMATO_KEY_RIGHT_SHIFT: return VK_RSHIFT;
		case TOMATO_KEY_RIGHT_CONTROL: return VK_RCONTROL;
		case TOMATO_KEY_RIGHT_ALT: return VK_RMENU;
		case TOMATO_KEY_RIGHT_SUPER: return VK_RWIN;
		case TOMATO_KEY_SHIFT: return VK_SHIFT;
		case TOMATO_KEY_CONTROL: return VK_CONTROL;
		case TOMATO_KEY_ALT: return VK_MENU;
		case TOMATO_KEY_MENU: return VK_APPS;
		}
		return 0;
	}
}

#endif // TOMATO_PLATFORM_WINDOWS