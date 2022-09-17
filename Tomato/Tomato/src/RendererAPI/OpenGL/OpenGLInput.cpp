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
		auto window = static_cast<GLFWwindow*>(std::dynamic_pointer_cast<OpenGLWindow>(App::GetWindow())->Get());
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
			status = static_cast<bool>(glfwGetKey((GLFWwindow*)std::dynamic_pointer_cast<OpenGLWindow>(App::GetWindow())->Get(), key));
			break;
		}
		
		return status;
	}

	bool OpenGLInput::Mouse(int button)
	{
		return glfwGetMouseButton((GLFWwindow*)std::dynamic_pointer_cast<OpenGLWindow>(App::GetWindow())->Get(), button);
	}

	Float2 OpenGLInput::MousePos()
	{
		double px, py;
		Float2 pos;
		glfwGetCursorPos((GLFWwindow*)std::dynamic_pointer_cast<OpenGLWindow>(App::GetWindow())->Get(),
			&px, &py);
		pos.x = static_cast<float>(px);
		pos.y = static_cast<float>(py);
		return pos;
	}
}