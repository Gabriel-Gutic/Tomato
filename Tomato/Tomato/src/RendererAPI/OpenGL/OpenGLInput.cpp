#include "pchTomato.h"
#include "OpenGLInput.h"

#include <GLFW/glfw3.h>

#include "Core/App/App.h"
#include "OpenGLWindow.h"


namespace Tomato
{
	bool OpenGLInput::Keyboard(int key)
	{
		return glfwGetKey((GLFWwindow*)std::dynamic_pointer_cast<OpenGLWindow>(App::GetWindow())->Get(), key);
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