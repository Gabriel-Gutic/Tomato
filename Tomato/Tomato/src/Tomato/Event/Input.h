#pragma once


namespace Tomato
{
	class Input
	{
	public:
		static bool Keyboard(int key);
		static bool Mouse(int button);
		static Float2 MousePos();
		static Float3 MouseWorldCoords();
		static double GetMouseX();
		static double GetMouseY();
	};
}
