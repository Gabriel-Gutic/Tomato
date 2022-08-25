#include "pchTomato.h"
#include "Input.h"

#include <GLFW/glfw3.h>

#include "Core/App/App.h"
#include "Renderer/Renderer.h"


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

	Float2 Input::MousePos()
	{
		Double px, py;
		Float2 pos;
		glfwGetCursorPos((GLFWwindow*)App::GetWindow()->Get(),
			&px, &py);
		pos.x = static_cast<Float>(px);
		pos.y = static_cast<Float>(py);
		return pos;
	}

	Float3 Input::MouseWorldCoords()
	{
		auto& vp = Renderer::GetViewProjection();
		Float2 pos = MousePos();

		Float win_width = App::GetWindow()->GetWidth();
		Float win_height = App::GetWindow()->GetHeight();
		Float4 coords;
		coords.x = 2.0 * (pos.x / win_width) - 1.0f;
		coords.y = 1.0f - 2.0 * (pos.y / win_height);
		coords.z = 1.0f;
		coords.w = 1.0f;

		coords = Math::Inverse(vp) * coords;
		return 1.0f / coords.w * coords.xyz;
	}

	double Input::GetMouseX()
	{
		Float2 f2 = MousePos();
		return f2.x;
	}

	double Input::GetMouseY()
	{
		Float2 f2 = MousePos();
		return f2.y;
	}
}


