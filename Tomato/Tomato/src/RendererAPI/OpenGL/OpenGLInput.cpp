#include "pchTomato.h"
#include "OpenGLInput.h"

#include <GLFW/glfw3.h>

#include "Core/App/App.h"
#include "OpenGLWindow.h"
#include "Event/KeyboardCodes.h"


namespace Tomato
{
	bool OpenGLInput::Keyboard(int key)
	{
		auto window = std::any_cast<GLFWwindow*>(App::GetWindow()->Get());
		bool status;

		switch (key)
		{
		case TOMATO_KEY_SHIFT:
			status = static_cast<bool>(glfwGetKey(window, TOMATO_KEY_LEFT_SHIFT))
				|| static_cast<bool>(glfwGetKey(window, TOMATO_KEY_RIGHT_SHIFT));
			break;
		case TOMATO_KEY_CONTROL:
			status = static_cast<bool>(glfwGetKey(window, TOMATO_KEY_LEFT_CONTROL))
				|| static_cast<bool>(glfwGetKey(window, TOMATO_KEY_RIGHT_CONTROL));
			break;
		case TOMATO_KEY_ALT:
			status = static_cast<bool>(glfwGetKey(window, TOMATO_KEY_LEFT_ALT))
				|| static_cast<bool>(glfwGetKey(window, TOMATO_KEY_RIGHT_ALT));
			break;
		case TOMATO_KEY_SUPER:
			status = static_cast<bool>(glfwGetKey(window, TOMATO_KEY_LEFT_SUPER))
				|| static_cast<bool>(glfwGetKey(window, TOMATO_KEY_RIGHT_SUPER));
			break;
		default:
			status = static_cast<bool>(glfwGetKey(std::any_cast<GLFWwindow*>(App::GetWindow()->Get()), key));
			break;
		}
		
		return status;
	}

	bool OpenGLInput::Mouse(int button)
	{
		return glfwGetMouseButton(std::any_cast<GLFWwindow*>(App::GetWindow()->Get()), button);
	}

	Float2 OpenGLInput::MousePos()
	{
		double px, py;
		Float2 pos;
		glfwGetCursorPos(std::any_cast<GLFWwindow*>(App::GetWindow()->Get()),
			&px, &py);
		pos.x = static_cast<float>(px);
		pos.y = static_cast<float>(py);
		return pos;
	}

	int OpenGLInput::ConvertNumPadKey(int key)
	{
		switch (key)
		{
		case TOMATO_KEY_NUMPAD_0: return TOMATO_KEY_INSERT;
		case TOMATO_KEY_NUMPAD_1: return TOMATO_KEY_END;
		case TOMATO_KEY_NUMPAD_2: return TOMATO_KEY_DOWN;
		case TOMATO_KEY_NUMPAD_3: return TOMATO_KEY_PAGE_DOWN;
		case TOMATO_KEY_NUMPAD_4: return TOMATO_KEY_LEFT;
		case TOMATO_KEY_NUMPAD_6: return TOMATO_KEY_RIGHT;
		case TOMATO_KEY_NUMPAD_7: return TOMATO_KEY_HOME;
		case TOMATO_KEY_NUMPAD_8: return TOMATO_KEY_UP;
		case TOMATO_KEY_NUMPAD_9: return TOMATO_KEY_PAGE_UP;
		case TOMATO_KEY_NUMPAD_DECIMAL: return TOMATO_KEY_DELETE;
		}
		return key;
	}
}