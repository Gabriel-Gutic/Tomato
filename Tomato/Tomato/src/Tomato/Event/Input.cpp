#include "pchTomato.h"
#include "Input.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLInput.h"
#include "RendererAPI/DirectX/DirectXInput.h"


namespace Tomato
{
	bool Input::Keyboard(int key)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return OpenGLInput::Keyboard(key);
		case RendererAPI::Type::DirectX:
			return DirectXInput::Keyboard(key);
		}
		return false;
	}

	bool Input::Mouse(int button)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return OpenGLInput::Mouse(button);
		case RendererAPI::Type::DirectX:
			return DirectXInput::Mouse(button);
		}
		return false;
	}

	Float2 Input::MousePos()
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return OpenGLInput::MousePos();
		case RendererAPI::Type::DirectX:
			return DirectXInput::MousePos();
		}
		return Float2();
	}

	Float3 Input::MouseWorldCoords()
	{
		//auto& vp = Renderer::GetViewProjection();
		//Float2 pos = MousePos();
		//
		//float win_width = App::GetWindow()->GetWidth();
		//float win_height = App::GetWindow()->GetHeight();
		//Float4 coords;
		//coords.x = 2.0 * (pos.x / win_width) - 1.0f;
		//coords.y = 1.0f - 2.0 * (pos.y / win_height);
		//coords.z = 1.0f;
		//coords.w = 1.0f;
		//
		//coords = Math::Inverse(vp) * coords;
		//return 1.0f / coords.w * coords.xyz;
		return {};
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


