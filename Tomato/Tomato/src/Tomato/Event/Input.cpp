#include "pchTomato.h"
#include "Input.h"

#include <GLFW/glfw3.h>

#include "Core/App/App.h"


namespace Tomato
{
	bool Input::Keyboard(int key)
	{
		int status = glfwGetKey((GLFWwindow*)App::GetWindow()->Get(), key);
		return status;
	}

	bool Input::Mouse(int button)
	{
		int status = glfwGetMouseButton((GLFWwindow*)App::GetWindow()->Get(), button);
		return status;
	}

	std::pair<double, double> Input::MousePos()
	{
		std::pair<double, double> pos;
		glfwGetCursorPos((GLFWwindow*)App::GetWindow()->Get(),
			&pos.first, &pos.second);
		return pos;
	}

	double Input::GetMouseX()
	{
		auto [x, y] = MousePos();
		return x;
	}

	double Input::GetMouseY()
	{
		auto [x, y] = MousePos();
		return y;
	}
}


