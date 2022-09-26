#pragma once


namespace Tomato
{

	class DirectXInput
	{
	private:
		DirectXInput() = delete;
	public:
		static bool Keyboard(int key);
		static bool Mouse(int button);
		static Float2 MousePos();
	};
}