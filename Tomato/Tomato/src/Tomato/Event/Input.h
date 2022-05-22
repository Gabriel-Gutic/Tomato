#pragma once


namespace Tomato
{
	class Input
	{
	public:
		static bool Keyboard(int key);
		static bool Mouse(int button);
		static std::pair<double, double> MousePos();
		static double GetMouseX();
		static double GetMouseY();
	};
}
