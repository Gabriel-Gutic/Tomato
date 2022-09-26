#include "pchTomato.h"
#include "DirectXInput.h"

#include "Tomato/Core/App/App.h"

#include "DirectXCodes.h"


namespace Tomato
{
#ifdef TOMATO_PLATFORM_WINDOWS
	bool DirectXInput::Keyboard(int key)
	{
		int directXKey = DirectXCodes::CastBack(key);
		return static_cast<bool>((GetKeyState(directXKey) >> 8) & 0x01);
	}

	bool DirectXInput::Mouse(int button)
	{
		int directXButton = DirectXCodes::CastBack(button);
		return static_cast<bool>((GetKeyState(directXButton) >> 8) & 0x01);
	}

	Float2 DirectXInput::MousePos()
	{
		POINT point = { 0, 0 };
		bool success = static_cast<bool>(GetCursorPos(&point));
		if (!success)
			return Float2();
		auto window = App::GetWindow();
		return Float2(static_cast<float>(point.x) - window->GetX(), static_cast<float>(point.y) - window->GetY());
	}
#else
	bool DirectXInput::Keyboard(int key)
	{
		return false;
	}

	bool DirectXInput::Mouse(int button)
	{
		return false;
	}

	Float2 DirectXInput::MousePos()
	{
		return Float2();
	}
#endif // TOMATO_PLATFORM_WINDOWS
}